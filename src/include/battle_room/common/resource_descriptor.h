#ifndef RESOURCE_DESCRIPTOR_H
#define RESOURCE_DESCRIPTOR_H

#include <vector>
#include <string>

namespace Common {

/*!
 * Stores the contents of a resource file describing an object such
 * as an animation. Files will be parsed into these objects which will
 * be read into specific classes.
 */
class ResourceDescriptor {

public:

    /*!
     * Key of resource descriptor, labeling what is being described.
     */
    std::string getKey();

    /*!
     * Value of resource descriptor, string representation of what is labeled.
     */
    std::string getValue();

    /*!
     * Any resource descriptors within the current one, e.g. bounding box within a frame.
     */
    std::vector<ResourceDescriptor> getSubResources();

    static ResourceDescriptor readFile(std::string filePath);

    /*!
     * Reads in an input file or string and fills resource descriptor.
     * Assumes first line describes the top level descriptor
     */
    void fillFromInput(std::vector<std::string> lines, unsigned& start);

    void setKey(std::string key);
    void setValue(std::string value);
    void setSubResources(std::vector<ResourceDescriptor> subResources);

    ResourceDescriptor();

private:

    std::string m_key;
    std::string m_value;
    std::vector<ResourceDescriptor> m_subResources;

}; // RecourseDescriptor class

} // Common namespace
#endif // RESOURCE_DESCRIPTOR_H
