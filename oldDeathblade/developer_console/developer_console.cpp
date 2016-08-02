#include "developer_console.h"
#include <sstream>
#include <iterator>

DeveloperConsoleClass::DeveloperConsoleClass(TempSettings *gamesettings){

    if (gamesettings == NULL){
        std::cerr << "A null pointer was passed into camera control\n";
        return;
    }
    game_settings = gamesettings;

    name = "console";
    history_maxlength = 100;
    history_place = 0;



    // Settings
    fontsize = 18;
    setfont("sample.ttf",fontsize);
    font_color.r = 255;
    font_color.g = 255;
    font_color.b = 255;
    font_color.a = 255;
    background_color.r = 100;
    background_color.g = 100;
    background_color.b = 100;
    background_color.a = 50;

    position.x = 50;
    position.y = 50;
    position.w = game_settings->window_width/2;
    position.h = game_settings->window_height/2;

    // other internal
    current_command = "";
    history.push_back(current_command);
    rethistory.push_back("");
    history_texture = NULL;
    input_texture = NULL;
    active = false;
    move_grabbed = false;
    resize_left = false;
    resize_right = false;
    resize_top = false;
    resize_bottom = false;
    scroll_offset = 0;

}

DeveloperConsoleClass::~DeveloperConsoleClass(){
    SDL_DestroyTexture(history_texture);
    SDL_DestroyTexture(input_texture);
}

void DeveloperConsoleClass::update_settings(){
    position.w = game_settings->window_width;
    position.h = game_settings->window_height;
}

void DeveloperConsoleClass::addtohistory(std::string prompt, std::string result){
	if (history.size() == history_maxlength){
		history.pop_back();
        rethistory.pop_back();
	}
    history.insert(history.begin()+1,prompt);
    rethistory.insert(rethistory.begin()+1,result);
}

void DeveloperConsoleClass::set_historymaxlength(unsigned int newlength){
	for (unsigned int i = newlength; i < history.size(); ++i)
		history.pop_back();
	history_maxlength = newlength;
}


std::string DeveloperConsoleClass::execute_command(std::string command_and_arguments){

    std::vector<std::string> arguments;
    std::stringstream ss(command_and_arguments);
    std::string item;
    while (std::getline(ss,item,' '))
        arguments.push_back(item);

    for(unsigned int i = 0; i < controllers.size(); ++i){
        std::string ret = controllers[i]->parse_arguments(arguments);
        if (ret.length() != 0){
            addtohistory(command_and_arguments, ret);
            return ret;
        }
    }

    std::stringstream error_result;
    error_result << "Invalid controller name in command.\n";
    error_result << "Type '<controller> help' for more information.\n";
    error_result << "Current controllers include: \n";
    for (unsigned int i = 0; i < controllers.size(); ++i)
        error_result << "   " << controllers[i]->name << std::endl;

    addtohistory(command_and_arguments, error_result.str().c_str());
    return error_result.str();
}

void DeveloperConsoleClass::drawon(SDL_Renderer *renderer)
{

    SDL_Rect textfield;
    textfield.w = position.w-4;
    textfield.h = fontsize+3;
    textfield.x = position.x + 2;
    textfield.y = position.y + position.h - textfield.h - 2;

    SDL_Rect topbar;
    topbar.w = position.w-4;
    topbar.h = 21;
    topbar.x = position.x + 2;
    topbar.y = position.y + position.h - topbar.h - 2;
    topbar.y = position.y + 2;

    // draw the box
    SDL_SetRenderDrawColor(renderer,background_color.r,background_color.g,background_color.b,background_color.a);
    SDL_RenderFillRect(renderer, &position);
    SDL_SetRenderDrawColor(renderer,240,240,240,240);
    SDL_RenderDrawRect(renderer,&textfield);
    SDL_SetRenderDrawColor(renderer,40,40,40,40);
    SDL_RenderFillRect(renderer, &topbar);

    // write the text
    render_current_command(renderer);
    if(input_texture != NULL){
        SDL_Rect inputrect;
        SDL_QueryTexture(input_texture, NULL, NULL, &inputrect.w, &inputrect.h);
        inputrect.x = textfield.x+2;
        inputrect.y = textfield.y+4;
        SDL_RenderCopy(renderer, input_texture, NULL, &inputrect);
    }

    render_history(renderer);
    if(history_texture != NULL){
        SDL_Rect inputrect;
        SDL_QueryTexture(history_texture, NULL, NULL, &inputrect.w, &inputrect.h);
        inputrect.x = textfield.x+2;
        inputrect.y = textfield.y-(inputrect.h*0.895+2);
        SDL_Rect crop;
        crop.x = 0;
        crop.w = inputrect.w;
        crop.h = position.h - textfield.h - topbar.h - 8;
        crop.y = position.y + topbar.h + 4 - inputrect.y;

        if(inputrect.h <= crop.h){
            SDL_RenderCopy(renderer, history_texture, NULL, &inputrect);
        }
        else{
            inputrect.y = position.y + topbar.h + 4;
            inputrect.h = crop.h;
            if (scroll_offset < 0) scroll_offset = 0;
            if (scroll_offset > crop.y) scroll_offset = crop.y;
            crop.y -= scroll_offset;
            SDL_RenderCopy(renderer, history_texture, &crop, &inputrect);
        }
    }
}

void DeveloperConsoleClass::render_current_command(SDL_Renderer* renderer){


    if (font == NULL) return;

    if(input_texture != NULL){
        SDL_DestroyTexture(input_texture);
    }

    std::string commandline = "$ " + current_command;
    SDL_Surface *input_surface = TTF_RenderText_Solid(font, commandline.c_str(), font_color);
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
    SDL_FreeSurface(input_surface);
}

void DeveloperConsoleClass::render_history(SDL_Renderer *renderer){

    if (font == NULL) return;

    if(history_texture != NULL){
        SDL_DestroyTexture(history_texture);
    }

    if(history.size() == 1){
        // there is only the current command
        history_texture = NULL;
        return;
    }

    std::stringstream sshistory;
    for(int i = history.size()-1; i > 0; --i){
        if(history[i].length() == 0) continue;
        sshistory << "$ " << history[i] << std::endl;
        sshistory << rethistory[i];
    }

    SDL_Surface *history_surface = TTF_RenderText_Blended_Wrapped(font, sshistory.str().c_str(), font_color, position.w-8);
    if (history_surface == NULL){
        std::cerr << "history_surface TTF_RenderText error: " << SDL_GetError() << std::endl;
        return;
    }

    history_texture = SDL_CreateTextureFromSurface(renderer, history_surface);
    if (history_texture == NULL){
        std::cerr << "history_texture SDL_CreateTextureFromSurface error: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(history_surface);
        return;
    }
    SDL_FreeSurface(history_surface);



}

void DeveloperConsoleClass::addinput(std::string input)
{
    current_command += input;
    history_place = 0;
    history[history_place] = current_command;
}

void DeveloperConsoleClass::backspace(){
    if (current_command.length() > 0)
        current_command = current_command.substr(0,current_command.length()-1);
    history_place = 0;
    history[history_place] = current_command;
}

void DeveloperConsoleClass::enter(){
    scroll_offset = 0;

    if(current_command.length() == 0) return;

    execute_command(current_command);
    current_command = "";

    history_place = 0;
    history[history_place] = current_command;
}

void DeveloperConsoleClass::goback_inhistory(){
    ++history_place;
    if (history_place >= history.size())
        history_place = history.size()-1;
    current_command = history[history_place];
}

void DeveloperConsoleClass::goforward_inhistory(){
    --history_place;
    if (history_place >= history.size())
        history_place = 0;
    current_command = history[history_place];
}

bool DeveloperConsoleClass::mouse_grab(bool mousedown, int mousex, int mousey){

    move_grabbed = false;
    resize_left = false;
    resize_right = false;
    resize_top = false;
    resize_bottom = false;

    if (mousedown == false) return false;

    SDL_Rect topbar;
    topbar.w = position.w-4;
    topbar.h = 21;
    topbar.x = position.x + 2;
    topbar.y = position.y + position.h - topbar.h - 2;
    topbar.y = position.y + 2;
    move_grabbed = (mousex >= topbar.x && mousex <= topbar.x+topbar.w &&
               mousey >= topbar.y && mousey <= topbar.y+topbar.h);

    if (move_grabbed) return true;

    SDL_Rect outer_rect;
    outer_rect.x = position.x-2;
    outer_rect.y = position.y-2;
    outer_rect.w = position.w+4;
    outer_rect.h = position.h+4;

    bool in_outer = (mousex >= outer_rect.x && mousex <= outer_rect.x+outer_rect.w &&
                     mousey >= outer_rect.y && mousey <= outer_rect.y+outer_rect.h);

    if (!in_outer) return false;

    SDL_Rect inner_rect;
    inner_rect.x = position.x+2;
    inner_rect.y = position.y+2;
    inner_rect.w = position.w-4;
    inner_rect.h = position.h-4;

    bool in_inner = (mousex >= inner_rect.x && mousex <= inner_rect.x+inner_rect.w &&
                     mousey >= inner_rect.y && mousey <= inner_rect.y+inner_rect.h);

    if (in_inner) return true;

    resize_left = (abs((position.x) - (mousex)) <= 2);
    resize_right = (abs((position.x+position.w) - (mousex)) <= 2);
    resize_top = (abs((position.y) - (mousey)) <= 2);
    resize_bottom = (abs((position.y+position.h) - (mousey)) <= 2);

    return true;
}

void DeveloperConsoleClass::handle_mouse(int relmousex, int relmousey){

    if (move_grabbed){
        position.x = position.x+relmousex;
        position.y = position.y+relmousey;
    }
    if (resize_left){
        position.x += relmousex;
        position.w -= relmousex;
    }
    else if (resize_right){
        position.w += relmousex;
    }
    if (resize_top){
        position.y += relmousey;
        position.h -= relmousey;
    }
    else if (resize_bottom){
        position.h += relmousey;
    }

    if (position.w < 100) position.w = 100;
    if (position.h < 3*(int)fontsize) position.h = 3*fontsize;
}

bool DeveloperConsoleClass::scroll(int input, int mousepx, int mousepy){
    if (mousepx >= position.x && mousepx <= position.x+position.w &&
        mousepy >= position.y && mousepy <= position.y+position.h){
        scroll_offset += fontsize*input/2;
        return true;
    }
    else {
        return false;
    }
}

void DeveloperConsoleClass::setfont(std::string filename, unsigned int font_size)
{
#ifdef _WIN32
    const char PATH_SEP = '\\';
#else
    const char PATH_SEP = '/';
#endif
    static std::string baseRes;
    if (baseRes.empty()){
        char *basePath = SDL_GetBasePath();
        if (basePath){
            baseRes = basePath;
            SDL_free(basePath);
        }
        else {
            std::cerr << "Error getting resource path: " << SDL_GetError() << std::endl;
            return;
        }
        //We replace the last bin/ with res/ to get the the resource path
        size_t pos = baseRes.rfind("bin");
        baseRes = baseRes.substr(0, pos) + "res" + PATH_SEP;
    }

    fontsize = font_size;

    std::string full_filename = baseRes + filename;
    font = TTF_OpenFont(full_filename.c_str(), fontsize);
    if (font == NULL){
        std::cerr << "TTF_OpenFont error: " << SDL_GetError() << std::endl;
    }
}

void DeveloperConsoleClass::add_controller(ControlBaseClass *newclass)
{
    std::vector<ControlBaseClass*>::iterator controller;
    for (controller = controllers.begin(); controller != controllers.end(); ++controller){
        if (newclass == *controller)
            return;
    }
    controllers.push_back(newclass);
}

std::string DeveloperConsoleClass::parse_arguments(std::vector<std::string> args){
    if (args[0].compare(name) != 0) return "";

    std::stringstream returnstring;

    if (args[1].compare("help") == 0){
        returnstring << "Possilble console setting commands are:\n";
        returnstring << "   console help\n";
        returnstring << "   console <command> help\n\n";
    }
    else if (args[1].compare("font") == 0){
        if (args[2].compare("help") == 0){
            returnstring << "   console font <filename>\n";
            returnstring << "      Sets the new font.\n\n";
        }
        else{
            // update font
            returnstring << "font set to " << args[2] << std::endl;
        }
    }



//    // Settings
//    TTF_Font *font;
//    unsigned int fontsize;
//    SDL_Color font_color;
//    SDL_Color background_color;
//    SDL_Rect position;

    return returnstring.str();

}
