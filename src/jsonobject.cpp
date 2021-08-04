#include "jsonutil.h"

namespace pson {

std::shared_ptr<JsonObject> JsonObject::getAsObject(std::string_view const &key) const { return getElementAsObject(m_properties.at(key), key); }
std::shared_ptr<JsonArray> JsonObject::getAsArray(std::string_view const &key) const { return getElementAsArray(m_properties.at(key), key); }
std::string_view JsonObject::getAsString(std::string_view const &key) const { return getElementAs<std::string_view>(m_properties.at(key), key); }
int JsonObject::getAsInt(std::string_view const &key) const { return getElementAs<int>(m_properties.at(key), key); }
float JsonObject::getAsFloat(std::string_view const &key) const { return getElementAs<float>(m_properties.at(key), key); }
bool JsonObject::getAsBool(std::string_view const &key) const { return getElementAs<bool>(m_properties.at(key), key); }
    
}