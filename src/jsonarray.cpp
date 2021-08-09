#include "jsonutil.h"

namespace pson {

std::shared_ptr<JsonObject> JsonArray::getAsObject(size_t index) const { return getElementAsObject(m_items.at(index), index); }
std::shared_ptr<JsonArray> JsonArray::getAsArray(size_t index) const { return getElementAsArray(m_items.at(index), index); }
std::string JsonArray::getAsString(size_t index) const { return getElementAs<std::string>(m_items.at(index), index); }
int JsonArray::getAsInt(size_t index) const { return getElementAs<int>(m_items.at(index), index ); }
float JsonArray::getAsFloat(size_t index) const { return getElementAs<float>(m_items.at(index), index); }
bool JsonArray::getAsBool(size_t index) const { return getElementAs<bool>(m_items.at(index), index); }
    
}