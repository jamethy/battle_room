#ifndef DEVELOPER_CONSOLE_H
#define DEVELOPER_CONSOLE_H

#include "controller_base/tempsettings.h"
#include "controller_base/controlbaseclass.h"

#include "SDL.h"
#include "SDL_ttf.h"

#include <iostream>
#include <vector>
#include <string>

/*!
 * \brief The DeeloperConsoleClass is a controller class that is the developer console. 
 * 
 * This class currently contains the ability to handle commands and deliver them to other controllers,
 * and creates the graphics object and handles user input. The latter should be in an inherited class.
 */
class DeveloperConsoleClass : public ControlBaseClass {

public:
    DeveloperConsoleClass(TempSettings *gamesettings);
    ~DeveloperConsoleClass();

    /*!
     * \brief Splits the command into arguments and passes them to the controllers.
     *
     * \param command_and_arguments A string of command/arguments separated by spaces.
     * \return Return of the command.
     */
    std::string execute_command(std::string command_and_arguments);

    /*!
     * \brief Renders the console window on the renderer.
     *
     * \param Renderer to draw the window on.
     */
    void drawon(SDL_Renderer* renderer);
    
    /*!
     * \brief Renders the text of the current command to the input_texture variable.
     */
    void render_current_command(SDL_Renderer *renderer);
    
    /*!
     * \bief Renders the text of the history to the history_texture variable.
     */
    void render_history(SDL_Renderer *renderer);

    // User input handlers
    void addinput(std::string input); //!< Reads what the user types
    void backspace(); //!< Deletes last character in current_command
    void enter(); //!< Executes current_command
    void goback_inhistory(); //!< Handles up-arrow and changes current_command
    void goforward_inhistory(); //!< Handles down-arrow and changes current_command
    bool mouse_grab(bool mousedown, int mousex, int mousey); //!< Handles left mouseclick to move/resize window
    void handle_mouse(int relmousex, int relmousey); //!< Reacts to mouse move if grabbed
    bool scroll(int input, int mousepx, int mousepy); //!< Handles mouse wheel to scroll through history
    
    // basic private member manipulation
    void set_historymaxlength(unsigned int newlength); //!< Sets max length and resizes history
    void setfont(std::string filename, unsigned int font_size); //!< Reads the font file and creates the font
    void add_controller(ControlBaseClass* newclass); //!< Adds the controller to the vector
    void bringup()  { active = true; }
    void close()    { active = false; }
    void toggle()   { active = !active; }
    bool is_active(){ return active; }

    // virtual functions
    virtual void update_settings();
    virtual std::string parse_arguments(std::vector<std::string> args);
	
private:

    // Settings
    TTF_Font *font; //!< Font for text
    unsigned int fontsize; //!< Height of font in pixels
    SDL_Color font_color; //!< Color of text
    SDL_Color background_color; //!< Color of the background of text
    SDL_Rect position; //!< Window x,y,width, and height

    // other internal
    TempSettings* game_settings; //!< Pointer to game basic settings
    std::string current_command; //!< Command the user is typing
    SDL_Texture *history_texture; //!< Stores the rendered history text
    SDL_Texture *input_texture; //!< Stores the rendered command text
    bool active; //!< Window is in the foreground
    bool move_grabbed; //!< Window is being dragged by mouse
    bool resize_left,resize_right,resize_top,resize_bottom; //!< Window is being resized by mouse
    int scroll_offset; //!< Scroll position of history

    std::vector<ControlBaseClass*> controllers; //!< Controllers that accept commands
    std::vector<std::string> history; //!< Commands used in the past
    std::vector<std::string> rethistory; //!< Return strings resulting from commands in history
    unsigned int history_maxlength; //!< Maximum length of history
    unsigned int history_place; //!< Current location in history recall
    void addtohistory(std::string prompt, std::string result); //!< Adds command and return string to history

};

#endif
