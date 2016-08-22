#ifndef RESOURCE_DESCRIPTOR_H
#define RESOURCE_DESCRIPTOR_H

#include <vector>
#include <string>

namespace BattleRoom {

const std::string DESCRIPTOR_EXTENSION = ".yml";

/*!
 * \breif Stores the contents of a resource file describing an object, such
 * as an animation. 
 *
 * These will containg all the settings for objects such as animation, frame, camera, and
 * display window, and instances of the level map, character info, or weapon
 */
class ResourceDescriptor {

public:


    std::vector<ResourceDescriptor> getSubResources(std::string filter = "");

    ResourceDescriptor getSubResource(std::string filter);

    static ResourceDescriptor readFile(std::string filePath);

    /*!
     * Reads in an input file or string and fills resource descriptor.
     * Assumes first line describes the top level descriptor
     */
    void fillFromInput(std::vector<std::string> lines, unsigned& start);

    // Setters and Getters

    void setKey(std::string key);
    std::string getKey();

    void setValue(std::string value);
    std::string getValue();

    void setSubResources(std::vector<ResourceDescriptor> subResources);

    ResourceDescriptor();

private:

    std::string m_key;
    std::string m_value;
    std::vector<ResourceDescriptor> m_subResources;

}; // RecourseDescriptor class

} // BattleRoom namespace
#endif // RESOURCE_DESCRIPTOR_H
