#include "pson/jsonvalue.h"

namespace pson {
    template<> JsonValue<int>::JsonValue(int value) : m_value(value), JsonElement(Int) {}
    template<> JsonValue<float>::JsonValue(float value) : m_value(value), JsonElement(Float) {}
    template<> JsonValue<std::string_view>::JsonValue(std::string_view value) : m_value(value), JsonElement(String) {}
}