#ifndef TEMPSETTINGS_H
#define TEMPSETTINGS_H

#include "controller_base/controlbaseclass.h"
#include <vector>

/*!
 * \brief The TempSettings class is just a placeholder for the main controller class? or just the
 * game settings class.
 */
class TempSettings {
public:

    TempSettings();

    ~TempSettings(){}

    unsigned int window_width; //!< width of window in pixels
    unsigned int window_height; //!< height of window in pixels

    double mapw; //!< width of map in game coordinates
    double maph; //!< height of map in game coorinates
    double mapx; //!< game X coordinate of top left map corner
    double mapy; //!< game Y coordinate of top left map corner
    double mapmidx; //!< mapx + mapw/2
    double mapmidy; //!< mapy + maph/2

    /*!
     * \brief A list of other controllers that are affected by a change within this.
     */
    std::vector<ControlBaseClass*> affectedsettings;


    void addToList(ControlBaseClass* newcontrol){
        affectedsettings.push_back(newcontrol);
    }

    void when_a_setting_is_changed(){
        // change the setting
        // eg. mapw = 1400

        for (unsigned int i = 0; i < affectedsettings.size(); ++i)
            affectedsettings[i]->update_settings();
    }

};

#endif // TEMPSETTINGS_H
