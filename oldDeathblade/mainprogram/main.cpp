
#include "controller_camera/cameracontrol.h"
#include "gameobjects/objectcontroller.h"
#include "developer_console/developer_console.h"
#include "gameobjects/basicwall.h"
#include "gameobjects/texturewall.h"
#include "gameobjects/star.h"
#include "players/player.h"
#include "ui_objects/boundclass.h"
#include "res_path.h"

#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL.h"

#include <iostream>
#include <cmath>

const int SCREEN_FPS = 600;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;
void draw_fps(SDL_Renderer* renderer, TTF_Font* font, double fps);

int main(){


    TempSettings gamesettings;

    gamesettings.mapw = 10;
    gamesettings.maph = 6;
    gamesettings.mapx = 0;
    gamesettings.mapy = 0;
    gamesettings.mapmidx = gamesettings.mapw/2.0;
    gamesettings.mapmidy = gamesettings.maph/2.0;
    gamesettings.window_width = 1300;
    gamesettings.window_height = 800;

    // initialize window, renderer, textures
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
        std::cerr << "SDL_Init error: " << SDL_GetError() << std::endl;
        return 1;
    }

    if (TTF_Init() != 0){
        std::cerr << "TTF_Init error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("deathblade_floating", 0, 0, gamesettings.window_width, gamesettings.window_height, SDL_WINDOW_SHOWN);
    if (window == nullptr){
        std::cerr << "SDL_CreateWindow error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr){
        std::cerr << "SDL_CreateRenderer error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    std::string resource_path = getResourcePath("");
    std::string charfile = resource_path + "initialcharacter.png";
    std::string bgfile = resource_path + "initialbackgroundtile.png";
    std::string starfile = resource_path + "star.png";
    std::string wallfile = resource_path + "wall.png";
    SDL_Texture* character_texture = IMG_LoadTexture(renderer, charfile.c_str());
    SDL_Texture* bgtile_texture = IMG_LoadTexture(renderer, bgfile.c_str());
    SDL_Texture* star_texture = IMG_LoadTexture(renderer, starfile.c_str());
    SDL_Texture* wall_texture = IMG_LoadTexture(renderer,wallfile.c_str());
    if (character_texture == nullptr || bgtile_texture == nullptr || star_texture == nullptr || wall_texture == nullptr){
            std::cerr << "IMG_LoadTexture error: " << SDL_GetError() << std::endl;
            SDL_DestroyTexture(character_texture);
            SDL_DestroyTexture(bgtile_texture);
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_Quit();
            return 1;
    }

    std::string fontfile = resource_path + "sample.ttf";
    TTF_Font* font = TTF_OpenFont(fontfile.c_str(), 15);
    if (font == NULL){
        std::cerr << "TTF_OpenFont error: " << SDL_GetError() << std::endl;
    }


	CameraControl camera(&gamesettings);
    ObjectController objects;
    DeveloperConsoleClass console(&gamesettings);
    console.add_controller(&console);
    console.add_controller(&camera);

    const double tilew = 0.5;
    const double tileh = 0.5;
    double mousex = gamesettings.mapmidx;
    double mousey = gamesettings.mapmidy;
    int mousepx = gamesettings.window_width/2;
    int mousepy = gamesettings.window_height/2;

    double wallthickness = 0.1;
    TextureWall bottomwall, topwall, leftwall, rightwall;
    bottomwall.x = gamesettings.mapw/2;
    bottomwall.y = gamesettings.maph+wallthickness/2;
    bottomwall.setTexture(wall_texture,gamesettings.mapw,wallthickness);
    objects.add_object(&bottomwall);

    topwall.x = gamesettings.mapw/2;
    topwall.y = -wallthickness/2;
    topwall.setTexture(wall_texture,gamesettings.mapw,wallthickness);
    objects.add_object(&topwall);

    leftwall.x = -wallthickness/2;
    leftwall.y = gamesettings.maph/2;
    leftwall.setTexture(wall_texture,wallthickness,gamesettings.maph);
    objects.add_object(&leftwall);

    rightwall.x = gamesettings.mapw + wallthickness/2;
    rightwall.y = gamesettings.maph/2;
    rightwall.setTexture(wall_texture,wallthickness,gamesettings.maph);
    objects.add_object(&rightwall);

    Player human;
    human.x = 5; human.y = 5;
    human.dx = -0.025; human.dy = -0.03;
    human.setTexture(character_texture, 0.05, 0.05);
    objects.add_object(&human);

    // map x [0, 10]
    // map y [0,  6]
    // star width 0.256
    std::vector<vec2d> star_positions = {
        vec2d(6,4),
        vec2d(3,4.1),
        vec2d(9,0.2),
        vec2d(1,0.4),
        vec2d(2,2.5),
        vec2d(3,2.5),
        vec2d(9,4.9),
        vec2d(0.2,5.1),
        vec2d(4.1,4.1)
    };
    std::vector<double> star_thetas = {
        0,
        45,
        15,
        60,
        85,
        4,
        50,
        66,
        31
    };

    std::vector<Star*> star_field;
    for(unsigned int i = 0; i < star_positions.size(); ++i){
        Star* newstar = new Star();

        newstar->x = star_positions[i].x;
        newstar->y = star_positions[i].y;
        newstar->setTexture(star_texture, 0.256, 0.256);

        if(i < star_thetas.size())
            newstar->rotate(star_thetas[i]*3.14159265359/180.0);


        star_field.push_back(newstar);
        objects.add_object(star_field[i]);

    }

    bool rightmouse_down = false;

    SDL_Event event;	
    bool quitnow = false;
    Uint32 fps_lastframe = SDL_GetTicks();
    while(!quitnow){
		
        int zoomdirection = 0;

        while(SDL_PollEvent(&event)){

            if (console.is_active()){
                if (event.type == SDL_KEYDOWN){
                    switch(event.key.keysym.sym){
                    case SDLK_BACKQUOTE:
                        console.toggle();
                        break;
                    case SDLK_BACKSPACE:
                        console.backspace();
                        break;
                    case SDLK_RETURN:
                    case SDLK_RETURN2:
                        console.enter();
                        break;
                    case SDLK_UP:
                        console.goback_inhistory();
                        break;
                    case SDLK_DOWN:
                        console.goforward_inhistory();
                        break;
                    default:
                        break;
                    }
                    console.render_current_command(renderer);

                }
                else if (event.type == SDL_TEXTINPUT && event.text.text[0] != '`'){
                    console.addinput(event.text.text);
                    console.render_current_command(renderer);
                }
                else if (event.type == SDL_MOUSEBUTTONDOWN){
                    if (event.button.button == SDL_BUTTON_LEFT){
                        if(!console.mouse_grab(true, event.button.x, event.button.y))
                            camera.mousecontrol_on();
                    }
                    //if (event.button.button == SDL_BUTTON_RIGHT)

                }
                else if (event.type == SDL_MOUSEBUTTONUP){
                    if (event.button.button == SDL_BUTTON_LEFT){
                        console.mouse_grab(false, -1,-1);
                        camera.mousecontrol_off();
                    }
                }
                else if (event.type == SDL_MOUSEMOTION){
                    mousepx = event.motion.x;
                    mousepy = event.motion.y;
                    console.handle_mouse(event.motion.xrel, event.motion.yrel);

                    if (camera.mouse_controlling()){
                        camera.mousecontrol_move(mousepx, mousepy, event.motion.xrel, event.motion.yrel,SDL_GetModState()==KMOD_LCTRL);
                    }
                    else{
                        mousex = camera.xfrompixel(event.motion.x, event.motion.y, db::Player);
                        mousey = camera.yfrompixel(event.motion.x, event.motion.y, db::Player);
                    }
                }
                else if (event.type == SDL_MOUSEWHEEL){
                    if(!console.scroll(event.wheel.y, mousepx, mousepy))
                        zoomdirection += event.wheel.y;
                }
                else if (event.type == SDL_QUIT){
                    quitnow = true;
                }

                continue;
            }

            // if console is not up
            if (event.type == SDL_KEYDOWN){
                switch(event.key.keysym.sym){
                case SDLK_ESCAPE:
                        quitnow = true;
                        break;
                case SDLK_BACKQUOTE:
                    console.toggle();
                    break;
                case SDLK_t:
                    if (!camera.is_tracking())
                        camera.track_object(&(human.x), &(human.y));
                    else
                        camera.stop_tracking();
                    break;
                case SDLK_w:
                case SDLK_UP:
                    camera.pan_updown(-1);
                    break;
                case SDLK_a:
                case SDLK_LEFT:
                    camera.pan_leftright(-1);
                    break;
                case SDLK_s:
                case SDLK_DOWN:
                    camera.pan_updown(1);
                    break;
                case SDLK_d:
                case SDLK_RIGHT:
                    camera.pan_leftright(1);
                    break;
                default:
                    break;
                }
            }
            else if (event.type == SDL_KEYUP){
                switch(event.key.keysym.sym){
                case SDLK_w:
                case SDLK_UP:
                    camera.pan_updown(0);
                    break;
                case SDLK_a:
                case SDLK_LEFT:
                    camera.pan_leftright(0);
                    break;
                case SDLK_s:
                case SDLK_DOWN:
                    camera.pan_updown(0);
                    break;
                case SDLK_d:
                case SDLK_RIGHT:
                    camera.pan_leftright(0);
                    break;
                default:
                    break;
                }
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN){
                if (event.button.button == SDL_BUTTON_LEFT){
                    camera.mousecontrol_on();
                }
                else if (event.button.button == SDL_BUTTON_RIGHT){
                    rightmouse_down = true;
                    human.bound.xclick = camera.xfrompixel(event.button.x,event.button.y,db::Player);
                    human.bound.yclick = camera.yfrompixel(event.button.x,event.button.y,db::Player);
                    human.bound.xdrag = 0;
                    human.bound.ydrag = 0;
                    human.bound.enabled = true;
                }
            }
            else if (event.type == SDL_MOUSEBUTTONUP){
                if (event.button.button == SDL_BUTTON_LEFT){
                    camera.mousecontrol_off();
                }
                else if (event.button.button == SDL_BUTTON_RIGHT){
                    rightmouse_down = false;
                }
            }
            else if (event.type == SDL_MOUSEWHEEL){
                zoomdirection += event.wheel.y;
            }
            else if (event.type == SDL_MOUSEMOTION){
                mousepx = event.motion.x;
                mousepy = event.motion.y;

                if (camera.mouse_controlling()){
                    camera.mousecontrol_move(mousepx, mousepy, event.motion.xrel, event.motion.yrel,SDL_GetModState()==KMOD_LCTRL);
                }
                else{
                    mousex = camera.xfrompixel(event.motion.x, event.motion.y, db::Player);
                    mousey = camera.yfrompixel(event.motion.x, event.motion.y, db::Player);
                    if(mousepx <= 1) camera.pan_leftright(-1);
                    else if (mousepx >= (int)gamesettings.window_width-1) camera.pan_leftright(1);
                    else if (mousepx - event.motion.xrel <= 1) camera.pan_leftright(0);
                    else if (mousepx - event.motion.xrel >= (int)gamesettings.window_width-1) camera.pan_leftright(0);
                    if(mousepy <= 1) camera.pan_updown(-1);
                    else if (mousepy >= (int)gamesettings.window_height-1) camera.pan_updown(1);
                    else if (mousepy - event.motion.yrel <= 1) camera.pan_updown(0);
                    else if (mousepy - event.motion.yrel >= (int)gamesettings.window_height-1) camera.pan_updown(0);

                    if(rightmouse_down){
                        human.bound.xdrag += event.motion.xrel;
                        human.bound.ydrag += event.motion.yrel;
                    }
                }

            }
            else if (event.type == SDL_QUIT){
                quitnow = true;
            }
	
        }


        objects.step_time();

        SDL_SetRenderDrawColor(renderer, 0,0,0,255);
        SDL_RenderClear(renderer);

        camera.adjust_zoom(zoomdirection, mousex, mousey);
		
        for (double x = gamesettings.mapx+tilew/2; x < gamesettings.mapx+gamesettings.mapw+tilew/2; x += tilew){
            for (double y = gamesettings.mapy+tileh/2; y < gamesettings.mapy+gamesettings.maph+tileh/2; y += tileh){
                SDL_Rect dst = camera.calculate_display_destination(x,y,tilew,tileh,db::Floor);
                SDL_RenderCopyEx(renderer, bgtile_texture, NULL, &dst, -camera.camyaw*180.0/3.14156033, NULL, SDL_FLIP_NONE);
            }
        }

        objects.drawon(renderer, &camera);
        if(console.is_active()) console.drawon(renderer);
        human.bound.drawon(renderer, &camera);


        Uint32 fps_newframe = SDL_GetTicks();
        if((fps_newframe-fps_lastframe) < SCREEN_TICKS_PER_FRAME){
            SDL_Delay(SCREEN_TICKS_PER_FRAME - (fps_newframe-fps_lastframe));
        }
        draw_fps(renderer, font, 1.0/(fps_newframe/1000.0 - fps_lastframe/1000.0));
        fps_lastframe = fps_newframe;

        SDL_RenderPresent(renderer);
	}
    SDL_DestroyTexture(character_texture);
	SDL_DestroyTexture(bgtile_texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    for(unsigned int i = 0; i < star_field.size(); ++i)
        delete star_field[i];

    return 0;
}

void draw_fps(SDL_Renderer* renderer, TTF_Font* font, double fps){

    static double slowed_fps = 0;
    slowed_fps = 0.05*fps + 0.95*slowed_fps;

    std::stringstream fps_ss;
    fps_ss << "fps: " << slowed_fps;
    SDL_Surface* input_surface = NULL;
    SDL_Texture* input_texture = NULL;
    static SDL_Color font_color = {255,255,255,255};

    input_surface = TTF_RenderText_Solid(font, fps_ss.str().c_str(), font_color);
    if (input_surface == NULL){
        std::cerr << "input_surface TTF_RenderText error: " << SDL_GetError() << std::endl;
        return;
    }
    input_texture = SDL_CreateTextureFromSurface(renderer, input_surface);
    if (input_texture == NULL){
        std::cerr << "input_texture SDL_CreateTextureFromSurface error: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(input_surface);
        return;
    }

    SDL_Rect inputrect;
    SDL_QueryTexture(input_texture, NULL, NULL, &inputrect.w, &inputrect.h);
    inputrect.x = 0;
    inputrect.y = 0;
    SDL_RenderCopy(renderer, input_texture, NULL, &inputrect);


    SDL_FreeSurface(input_surface);
    SDL_DestroyTexture(input_texture);
}
