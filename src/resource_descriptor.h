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

        // Constructors
        ResourceDescriptor();

        ResourceDescriptor(const std::string &key, const std::string &value);

        ResourceDescriptor(std::vector<std::string> lines);

        static ResourceDescriptor fromJson(const std::string& json);

        /**
         * \brief Returns the filtered subresources whose Key matches fileter (ignoring case)
         *
         * Use this function to fill a collection within a resource, such as frames in an animation
         *
         * \param filter Filter to Key
         * \return Vector of descriptors that match the filter
         */
        std::vector<ResourceDescriptor> getSubResources(std::string filter = "") const;

        /**
         * \brief Gets the first resource descriptor that matches the filter
         *
         * Helps fill a member variable by passing the return value into the variable's settings
         * Returns empty resource descriptor if none was found
         *
         * \param filter Filter to keys
         * \return ResourceDescriptor that matches the fitler
         */
        ResourceDescriptor getSubResource(std::string filter) const;

        /**
         * \brief Gets the resource Descriptor from the file
         *
         * The key of the result is the file path and the value is the extension
         * The file is all the sub resources, e.g. the animation resource file will have an
         * Animation sub resource.
         *
         * \param filePath Full file path to the text file
         * \return Resource descriptor filled by the file
         */
        static ResourceDescriptor readFile(std::string filePath);

        /**
         * \brief Gets the resource Descriptor from the resource file
         *
         * \param resourcePath File path to the text file relative to res dir
         * \return Resource descriptor filled by the file
         */
        static ResourceDescriptor readResource(std::string resourcePath);

        // Getters and Setters

        std::string getKey() const;

        std::string getValue() const;

        void setKey(std::string key);

        void setValue(std::string value);

        void setSubResources(std::vector<ResourceDescriptor> subResources);

        void addSubResources(std::vector<ResourceDescriptor> subResources);

    private:

        /*!
         * \brief Reads in an input file or string and fills resource descriptor.
         *
         * Mainly used in readFile or manually creating a resource descriptor
         * Assumes first line describes the top level descriptor (and is not empty)
         *
         * \param lines Vector of lines in the file
         * \param start Current position in lines
         */
        void fillFromInput(std::vector<std::string> lines, unsigned &start);

        std::string m_key; ///< What the descriptor is describing
        std::string m_value; ///< The value of what the descriptor is describing
        std::vector<ResourceDescriptor> m_subResources; ///< Entites contained in the current

    }; // RecourseDescriptor class
} // BattleRoom namespace
#endif // RESOURCE_DESCRIPTOR_H
