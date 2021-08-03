#include "jsonutil.h"

namespace pson {

int JsonArray::getAsInt(size_t index) const { return getElementAs<int>(m_elements.at(index), index ); }
float JsonArray::getAsFloat(size_t index) const { return getElementAs<float>(m_elements.at(index), index); }
std::string_view JsonArray::getAsString(size_t index) const { return getElementAs<std::string_view>(m_elements.at(index), index); }
JsonObject *JsonArray::getAsObject(size_t index) const { return getElementAsObject(m_elements.at(index), index); }
JsonArray *JsonArray::getAsArray(size_t index) const { return getElementAsArray(m_elements.at(index), index); }
    
}