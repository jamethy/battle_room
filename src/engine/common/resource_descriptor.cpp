
#include "battle_room/common/resource_descriptor.h"

using std::string;
using std::vector;

namespace Common {

string ResourceDescriptor::getKey() {
    return m_key;
}

string ResourceDescriptor::getValue() {
    return m_value;
}

vector<ResourceDescriptor> ResourceDescriptor::getSubResources() {
    return m_subResources;
}

void ResourceDescriptor::setKey(string key) {
    m_key = key;
}

void ResourceDescriptor::setValue(string value) {
    m_value = value;
}

void ResourceDescriptor::setSubResources(vector<ResourceDescriptor> subResources) {
    m_subResources = subResources;
}

void ResourceDescriptor::fillFromInput(vector<string> lines) {
    // TODO fill this function
}




} // Common namespace
