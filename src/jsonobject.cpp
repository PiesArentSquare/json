#include "jsonutil.h"

namespace pson {

std::shared_ptr<JsonObject> JsonObject::getAsObject(std::string const &key) const { return getElementAsObject(m_properties.at(key), key); }
std::shared_ptr<JsonArray> JsonObject::getAsArray(std::string const &key) const { return getElementAsArray(m_properties.at(key), key); }
std::string JsonObject::getAsString(std::string const &key) const { return getElementAs<std::string>(m_properties.at(key), key); }
int JsonObject::getAsInt(std::string const &key) const { return getElementAs<int>(m_properties.at(key), key); }
float JsonObject::getAsFloat(std::string const &key) const { return getElementAs<float>(m_properties.at(key), key); }
bool JsonObject::getAsBool(std::string const &key) const { return getElementAs<bool>(m_properties.at(key), key); }
    
}