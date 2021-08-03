#include "jsonutil.h"

namespace pson {

int JsonObject::getAsInt(std::string_view const &key) const { return getElementAs<int>(m_items.at(key), key); }
float JsonObject::getAsFloat(std::string_view const &key) const { return getElementAs<float>(m_items.at(key), key); }
std::string_view JsonObject::getAsString(std::string_view const &key) const { return getElementAs<std::string_view>(m_items.at(key), key); }
std::shared_ptr<JsonObject> JsonObject::getAsObject(std::string_view const &key) const { return getElementAsObject(m_items.at(key), key); }
std::shared_ptr<JsonArray> JsonObject::getAsArray(std::string_view const &key) const { return getElementAsArray(m_items.at(key), key); }
    
}