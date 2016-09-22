#ifndef VIEW_INTERFACE_H
#define VIEW_INTERFACE_H

#include "battle_room/common/resource.h"
#include "battle_room/common/inputs.h"
#include "battle_room/common/drawable_object.h"
#include "battle_room/common/drawable_text.h"

#include <vector>

namespace BattleRoom {


/**
 *
 */
class ViewInterface : public Resource {

public:

    // destructor
    virtual ~ViewInterface() {}

    /**
     * \brief Handle inputs and return any remaining
     * \param inputs Collection of inputs from the display window
     * \return Remaining inputs that were not used here
     */
    virtual Inputs handleInputs(Inputs inputs) = 0;

    /**
     * \brief Gets a list of objects that are drawable (probably on associated view)
     * \return List of objects
     */
    virtual std::vector<DrawableObject> getDrawableObjects() = 0;

    /**
     * \brief Gets a list of drawable texts (probably on associated view)
     * \return List of texts
     */
    virtual std::vector<DrawableText> getDrawableTexts() = 0;

    // getters and setters

    std::string getAssociatedView() const;
    void setAssociatedView(std::string viewName);

    // inherited
    virtual void applySettings(ResourceDescriptor settings) override;

private:

    std::string m_associatedView; ///< View being interfaced with

}; // ViewInterface class
} // BattleRoom namespace
#endif // VIEW_INTERFACE_H