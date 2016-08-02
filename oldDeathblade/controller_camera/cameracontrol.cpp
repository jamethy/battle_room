#include "controller_camera/cameracontrol.h"

CameraControl::CameraControl(TempSettings *gamesettings){

	if (gamesettings == NULL){
		std::cerr << "A null pointer was passed into camera control\n";
		return;
	}

    name = "camera";

	planeZs.push_back(0);
    planeZs.push_back(10);
	planeZs.push_back(1);

    zoomin_speed = 0.05;
    zoomout_speed = 0.075;
	zoom_friction = 0.3;
    momentum_on = true;
    sidebuffer = 0.5;
    pan_speed = 0.25;

    dx = 0; dy = 0; dz = 0;
    mouse_control = false;

    fieldofview_w = 75*3.14156/180.0;
    tanfov_w = tan(fieldofview_w/2.0);
    pixelratio.push_back(1000);
    pixelratio.push_back(500);
    pixelratio.push_back(1);
    xtracking = NULL;
    ytracking = NULL;

	game_settings = gamesettings;
	gamesettings->addToList(this);
	update_settings();


}

CameraControl::~CameraControl(){
}

void CameraControl::update_settings(){

    camyaw = 0;
    tanfov_w = tan(fieldofview_w/2.0);
	fieldofview_h = 2*atan(game_settings->window_height*tanfov_w/game_settings->window_width);
    tanfov_h = tan(fieldofview_h/2.0);

	camx = game_settings->mapx + game_settings->mapw/2.0;
    camy = game_settings->mapy + game_settings->maph/2.0;

    calculate_camera_bounds();

	camz = max_z;


    pixelratio[db::Floor] = game_settings->window_width/(2.0*(camz - planeZs[db::Floor])*tanfov_w);
    pixelratio[db::Player] = game_settings->window_width/(2.0*(camz - planeZs[db::Player])*tanfov_w);
    pixelratio[db::Gui] = 1;
	
}

void CameraControl::adjust_zoom(int input, double mouse_x, double mouse_y){

    double oldpr = pixelratio[db::Player];

    if (input < 0){
        dz += zoomout_speed*(max_z - camz - input);
    }
    else if (input > 0){
        dz += zoomin_speed*(min_z - camz - input);
    }
    camz += dz;


    if (momentum_on){
        dz -= dz*zoom_friction;
        if (dz*dz < 0.01) dz = 0;
    }
    else {
        dz = 0;
    }

    if (camz > max_z) camz = max_z;
	if (camz < min_z) camz = min_z;

    pixelratio[db::Floor] = game_settings->window_width/(2.0*(camz - planeZs[db::Floor])*tanfov_w);
    pixelratio[db::Player] = game_settings->window_width/(2.0*(camz - planeZs[db::Player])*tanfov_w);

    if(input >= 0 && pixelratio[db::Player] != oldpr){
        camx = mouse_x - (oldpr/pixelratio[db::Player])*(mouse_x - camx);
        camy = mouse_y - (oldpr/pixelratio[db::Player])*(mouse_y - camy);
    }


    camx += dx;
    camy += dy;

    checkcamxy();

	return;
}

void CameraControl::pan_leftright(int xdirection){
    stop_tracking();
    dx = xdirection*pan_speed;
}

void CameraControl::pan_updown(int ydirection){
    stop_tracking();
    dy = ydirection*pan_speed;
}

void CameraControl::rotate_view(double delta_theta)
{
    camyaw += delta_theta;
    calculate_camera_bounds();
}

void CameraControl::mousecontrol_move(int mouse_x, int mouse_y, int relative_x, int relative_y, bool rotating){
    if(rotating){
        double theta1 = atan2(mouse_y-relative_y-game_settings->window_height/2.0, mouse_x-relative_x-game_settings->window_width/2.0);
        double theta2 = atan2(mouse_y-game_settings->window_height/2.0, mouse_x-game_settings->window_width/2.0);
        rotate_view(theta1-theta2);
    }
    else{
        stop_tracking();
        double dx = wfrompixel(relative_x, db::Player);
        double dy = hfrompixel(relative_y, db::Player);
        camx = camx - (dx*cos(camyaw) - dy*sin(camyaw));
        camy = camy - (dx*sin(camyaw) + dy*cos(camyaw));
        checkcamxy();
    }
}

SDL_Rect CameraControl::calculate_display_destination(  double x,
                                                        double y,
                                                        double w,
                                                        double h,
                                                        db::ZPlane zplane){

    SDL_Rect dst;
    dst.w = pixelfromw(w,zplane);
    dst.h = pixelfromh(h,zplane);
    dst.x = pixelfromx(x,y,zplane) - dst.w/2;
    dst.y = pixelfromy(x,y,zplane) - dst.h/2;
    return dst;
}

void CameraControl::track_object(double* objectx, double* objecty){
    xtracking = objectx;
    ytracking = objecty;
    tracking_on = true;
}

void CameraControl::stop_tracking(){
    xtracking = NULL;
    ytracking = NULL;
    tracking_on = false;
}

double CameraControl::xfrompixel(int pixelX, int pixelY, db::ZPlane z){
    double dx = (pixelX - game_settings->window_width/2.0)/pixelratio[z];
    double dy = (pixelY - game_settings->window_height/2.0)/pixelratio[z];
    return dx*cos(camyaw) - dy*sin(camyaw) + camx;
}

double CameraControl::yfrompixel(int pixelX, int pixelY, db::ZPlane z){
    double dx = (pixelX - game_settings->window_width/2.0)/pixelratio[z];
    double dy = (pixelY - game_settings->window_height/2.0)/pixelratio[z];
    return dx*sin(camyaw) + dy*cos(camyaw) + camy;
}

double CameraControl::wfrompixel(int pixelW, db::ZPlane z){
	return pixelW/pixelratio[z];
}

double CameraControl::hfrompixel(int pixelH, db::ZPlane z){
	return pixelH/pixelratio[z];
}

int CameraControl::pixelfromx(double x, double y, db::ZPlane z){
    double dx = (x-camx)*cos(-camyaw) - (y-camy)*sin(-camyaw);
    return dx*pixelratio[z] + game_settings->window_width/2.0;
}

int CameraControl::pixelfromy(double x, double y, db::ZPlane z){
    double dy = (x-camx)*sin(-camyaw) + (y-camy)*cos(-camyaw);
    return dy*pixelratio[z] + game_settings->window_height/2.0;
}

int CameraControl::pixelfromw(double w, db::ZPlane z){
	return w*pixelratio[z];
}

int CameraControl::pixelfromh(double h, db::ZPlane z){
	return h*pixelratio[z];
}

void CameraControl::checkcamxy(){

    if(tracking_on){
        if (xtracking != NULL) camx = *xtracking;
        if (ytracking != NULL) camy = *ytracking;
    }
    else{

        double minx = -(camz-planeZs[db::Player])*tanfov_w + (camx-game_settings->mapmidx)*cos(-camyaw) - (camy-game_settings->mapmidy)*sin(-camyaw);
        double miny = -(camz-planeZs[db::Player])*tanfov_h + (camx-game_settings->mapmidx)*sin(-camyaw) + (camy-game_settings->mapmidy)*cos(-camyaw);
        double maxx =  (camz-planeZs[db::Player])*tanfov_w + (camx-game_settings->mapmidx)*cos(-camyaw) - (camy-game_settings->mapmidy)*sin(-camyaw);
        double maxy =  (camz-planeZs[db::Player])*tanfov_h + (camx-game_settings->mapmidx)*sin(-camyaw) + (camy-game_settings->mapmidy)*cos(-camyaw);


        if (camx < game_settings->mapx)
            camx = game_settings->mapx;
        else if (camx > game_settings->mapx+game_settings->mapw)
            camx = game_settings->mapx+game_settings->mapw;
        else if (maxx > maxview_w){
            camx -= (maxx-maxview_w)*cos(-camyaw);
            camy -= -(maxx-maxview_w)*sin(-camyaw);
        }
        else if (minx < minview_w){
            camx -= (minx-minview_w)*cos(-camyaw);
            camy -= -(minx-minview_w)*sin(-camyaw);
        }

        if (camy < game_settings->mapy)
            camy = game_settings->mapy;
        else if (camy > game_settings->mapy+game_settings->maph)
            camy = game_settings->mapy+game_settings->maph;
        else if (maxy > maxview_h){
            camx -= (maxy-maxview_h)*sin(-camyaw);
            camy -= (maxy-maxview_h)*cos(-camyaw);
        }
        else if (miny < minview_h){
            camx -= (miny-minview_h)*sin(-camyaw);
            camy -= (miny-minview_h)*cos(-camyaw);
        }
    }
}

void CameraControl::calculate_camera_bounds()
{

    // create map min/max with origin at center
    double mapmin_x = game_settings->mapx - sidebuffer - game_settings->mapw/2;
    double mapmax_x = game_settings->mapx + sidebuffer + game_settings->mapw/2;
    double mapmin_y = game_settings->mapy - sidebuffer - game_settings->maph/2;
    double mapmax_y = game_settings->mapy + sidebuffer + game_settings->maph/2;

    // find horizontal
    minview_w = mapmin_x*cos(-camyaw) - mapmin_y*sin(-camyaw);
    maxview_w = minview_w;

    double p = mapmin_x*cos(-camyaw) - mapmax_y*sin(-camyaw);
    if (p < minview_w) minview_w = p;
    else if (p > maxview_w) maxview_w = p;

    p = mapmax_x*cos(-camyaw) - mapmax_y*sin(-camyaw);
    if (p < minview_w) minview_w = p;
    else if (p > maxview_w) maxview_w = p;

    p = mapmax_x*cos(-camyaw) - mapmin_y*sin(-camyaw);
    if (p < minview_w) minview_w = p;
    else if (p > maxview_w) maxview_w = p;

    // find vertical
    minview_h = mapmin_x*sin(-camyaw) + mapmin_y*cos(-camyaw);
    maxview_h = minview_h;

    p = mapmin_x*sin(-camyaw) + mapmax_y*cos(-camyaw);
    if (p < minview_h) minview_h = p;
    else if (p > maxview_h) maxview_h = p;

    p = mapmax_x*sin(-camyaw) + mapmax_y*cos(-camyaw);
    if (p < minview_h) minview_h = p;
    else if (p > maxview_h) maxview_h = p;

    p = mapmax_x*sin(-camyaw) + mapmin_y*cos(-camyaw);
    if (p < minview_h) minview_h = p;
    else if (p > maxview_h) maxview_h = p;

    // change to be ratio of screen
    double w = maxview_w - minview_w;
    double h = maxview_h - minview_h;
    double R = game_settings->window_width/(1.0*game_settings->window_height);
    if (R*h > w){
        double midx = (maxview_w + minview_w)/2;
        minview_w = midx - R*h/2;
        maxview_w = midx + R*h/2;
    }
    else{
        double midy = (maxview_h + minview_h)/2;
        minview_h = midy - w/R/2;
        maxview_h = midy + w/R/2;
    }

    double zw = (maxview_w - minview_w)/2/tanfov_w;
    double zh = (maxview_h - minview_h)/2/tanfov_h;

    max_z = (zw > zh) ? zw : zh;
    max_z += planeZs[db::Player];
    min_z = 1.5 + planeZs[db::Player];

}

std::string CameraControl::parse_arguments(std::vector<std::string> args){

    if (args[0].compare(name) != 0) return "";
    std::stringstream returnstring;

    if (args[1].compare("help") == 0){
        returnstring << "Possilble camera commands are:\n";
        returnstring << "   camera help\n";
        returnstring << "   camera camx <double>\n";
        returnstring << "   camera camy <double>\n";
        returnstring << "   camera camz <double>\n";
        returnstring << "   camera camyaw <double>\n";
        returnstring << "   camera zoomin_speed <double>\n";
        returnstring << "   camera zoomout_speed <double>\n";
        returnstring << "   camera zoom_friction <double>\n";
        returnstring << "   camera momentum_on <true/false>\n";
        returnstring << "   camera sidebuffer <double>\n";
        returnstring << "   camera pan_speed <double>\n";
        returnstring << "   camera fieldofvew <double>\n";
        returnstring << "   camera planeZs <Floor/Player> <double>\n";
        returnstring << "   camera <command> ?\n\n";
        returnstring << "   camera <command> help\n\n";
    }
    else if (args[1].compare("camx") == 0){
        if (args[2].compare("help") == 0){
            returnstring << "   camera camx <double>\n";
            returnstring << "      Sets the new camera x position. It is bounded by map width and field of view.\n\n";
        }
        else if (args[2].compare("?") == 0){
            returnstring << "   camera camx " << camx << std::endl;
        }
        else{
            camx = atof(args[2].c_str());
            checkcamxy();
            returnstring << "camx set to " << camx << std::endl;
        }
    }
    else if (args[1].compare("camy") == 0){
        if (args[2].compare("help") == 0){
            returnstring << "   camera camy <double>\n";
            returnstring << "      Sets the new camera y position. It is bounded by map height and field of view.\n\n";
        }
        else if (args[2].compare("?") == 0){
            returnstring << "   camera camy " << camy << std::endl;
        }
        else{
            camy = atof(args[2].c_str());
            checkcamxy();
            returnstring << "camy set to " << camy << std::endl;
        }
    }
    else if (args[1].compare("camz") == 0){
        if (args[2].compare("help") == 0){
            returnstring << "   camera camz <double>\n";
            returnstring << "      Sets the new camera z position. It is bounded by map size and field of view (a pyramid structure above the field.\n\n";
        }
        else if (args[2].compare("?") == 0){
            returnstring << "   camera camz " << camz << std::endl;
        }
        else{
            camz = atof(args[2].c_str());
            returnstring << "camz set to " << camz << std::endl;
        }
    }
    else if (args[1].compare("camyaw") == 0){
        if (args[2].compare("help") == 0){
            returnstring << "   camera camyaw <double>\n";
            returnstring << "      Sets the new camera yaw. This is representative of the rotation of the map. (in degrees)\n\n";
        }
        else if (args[2].compare("?") == 0){
            returnstring << "   camera camyaw " << camyaw*180/3.14159265359 << std::endl;
        }
        else{
            camyaw = 0;
            rotate_view(atof(args[2].c_str())*3.14159265359/180);
            returnstring << "camyaw set to " << camyaw*180/3.14159265359 << std::endl;
        }
    }
    else if (args[1].compare("zoomin_speed") == 0){
        if (args[2].compare("help") == 0){
            returnstring << "   camera zoomin_speed <double>\n";
            returnstring << "      Sets the multiplier for the speed of zooming in. Default is 0.05.\n";
        }
        else if (args[2].compare("?") == 0){
            returnstring << "   camera zoomin_speed " << zoomin_speed << std::endl;
        }
        else{
            zoomin_speed = atof(args[2].c_str());
            returnstring << "zoomin_speed set to " << zoomin_speed << std::endl;
        }
    }
    else if (args[1].compare("zoomout_speed") == 0){
        if (args[2].compare("help") == 0){
            returnstring << "   camera zoomout_speed <double>\n";
            returnstring << "      Sets the multiplier for the speed of zooming out. Default is 0.075.\n";
        }
        else if (args[2].compare("?") == 0){
            returnstring << "   camera zoomout_speed " << zoomout_speed << std::endl;
        }
        else{
            zoomout_speed = atof(args[2].c_str());
            returnstring << "zoomout_speed set to " << zoomout_speed << std::endl;
        }
    }
    else if (args[1].compare("zoom_friction") == 0){
        if (args[2].compare("help") == 0){
            returnstring << "   camera zoom_friction <double>\n";
            returnstring << "      Sets the multiplier for the friction in momentum zooming. Default is 0.3.\n";
        }
        else if (args[2].compare("?") == 0){
            returnstring << "   camera zoom_friction " << zoom_friction << std::endl;
        }
        else{
            zoom_friction = atof(args[2].c_str());
            returnstring << "zoom_friction set to " << zoom_friction << std::endl;
        }
    }
    else if (args[1].compare("momentum_on") == 0){
        if (args[2].compare("help") == 0){
            returnstring << "   camera momentum_on <true/false\n";
            returnstring << "      Turns momentum effect of zooming on/off.\n";
        }
        else if (args[2].compare("?") == 0){
            returnstring << "   camera momentum_on " << (momentum_on ? "true" : "false") << std::endl;
        }
        else{
            if (args[2].compare("true") == 0){
                momentum_on = true;
                returnstring << "momentum_on set to true\n";
            }
            else if (args[2].compare("false") == 0){
                momentum_on = false;
                returnstring << "momentum_on set to false\n";
            }
        }
    }
    else if (args[1].compare("sidebuffer") == 0){
        if (args[2].compare("help") == 0){
            returnstring << "   camera x_sidebuffer <double>\n";
            returnstring << "      Sets the amount of in-game space the camera can see past the map. Default is 0.5.\n";
        }
        else if (args[2].compare("?") == 0){
            returnstring << "   camera sidebuffer " << sidebuffer << std::endl;
        }
        else{
            sidebuffer = atof(args[2].c_str());
            returnstring << "sidebuffer set to " << sidebuffer << std::endl;
        }
    }
    else if (args[1].compare("pan_speed") == 0){
        if (args[2].compare("help") == 0){
            returnstring << "   camera pan_speed <double>\n";
            returnstring << "      Sets speed of panning by user input. Default is 0.25.\n";
        }
        else if (args[2].compare("?") == 0){
            returnstring << "   camera pan_speed " << pan_speed << std::endl;
        }
        else{
            pan_speed = atof(args[2].c_str());
            returnstring << "pan_speed set to " << pan_speed << std::endl;
        }
    }
    else if (args[1].compare("fieldofview") == 0){
        if (args[2].compare("help") == 0){
            returnstring << "   camera fieldofvew <double>\n";
            returnstring << "      Sets the horizontal field of view of the camera (in degrees). Default is 75 degrees.\n";
        }
        else if (args[2].compare("?") == 0){
            returnstring << "   camera fieldofview " << (int)(fieldofview_w*180/3.14156) << std::endl;
        }
        else{
            fieldofview_w = atof(args[2].c_str());
            returnstring << "fieldofview set to " << fieldofview_w << std::endl;
            fieldofview_w = fieldofview_w*3.14156/180.0;
            update_settings();
        }
    }
    else if (args[1].compare("planeZs") == 0){
        if (args[2].compare("help") == 0){
            returnstring << "   camera planeZs <Floor/Player> <double>\n";
            returnstring << "      Sets the z value for the entire plane of Foor/Player. This is used in calculations for zoom. Defaults are 0/0.2.\n";
        }
        else{
            if (args.size() < 4) return "Not enough arguments";
            if (args[2].compare("Floor") == 0){
                if(args[3].compare("?") == 0){
                    returnstring << "camera planeZs[Floor] " << planeZs[db::Floor] << std::endl;
                }
                else{
                    planeZs[db::Floor] = atof(args[3].c_str());
                    update_settings();
                    returnstring << "planeZs[Floor] set to " << planeZs[db::Floor] << std::endl;
                }
            }
            else if (args[2].compare("Player") == 0){
                if(args[3].compare("?") == 0){
                    returnstring << "camera planeZs[Player] " << planeZs[db::Player] << std::endl;
                }
                else{
                    planeZs[db::Player] = atof(args[3].c_str());
                    update_settings();
                    returnstring << "planeZs[Player] set to " << planeZs[db::Player] << std::endl;
                }
            }
        }
    }
    else {
        returnstring << "camera command not parsed correctly. Try:\n";
        returnstring << "   camera help\n";
        returnstring << "   camera <command> help\n\n";
    }

    return returnstring.str();
}

