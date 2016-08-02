#ifndef CONTROLBASECLASS_H
#define CONTROLBASECLASS_H

#include <string>
#include <vector>
#include <iostream>
#include <sstream>

/*!
 * \brief The ControlBaseClass class is the template for what every controller class will have.
 *
 * As of Feb 02, 2015 my idea is to have controller classes that control the main processes of the program.
 * For example, the CameraControlClass keeps track of the camera and controls the view of the user. Each of
 * the control classes will inherit ControlBaseClass so it will have access to any settings changed that affect
 * it.
 */
class ControlBaseClass {

public:
    ControlBaseClass();
    virtual ~ControlBaseClass(){}

    /*!
     * \brief Recalculates all inner members that are dependent on other settings. This function
     * should be called for every controller class when a setting is changed.
     */
    virtual void update_settings(){}

    /*!
     * \brief Checks the arguments of the command console to first, see if the command is for the
     * current class, and second, to parst the commmands. Note it assumes args.size() >= 3
     * \return True if commands parsed (correct class)
     */
    virtual std::string parse_arguments(std::vector<std::string> args){return args[0];}
    void change_setting(std::string command); //!< Splits the command into a vector and passes into parse_arguments

    static std::ostream* outstream;

    /*!
     * \brief Contains the name trigger for commands.
     */
    std::string name;
};


#endif // CONTROLBASECLASS_H
