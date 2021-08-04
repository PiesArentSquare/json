#pragma once

#include "jsonelement.h"

namespace pson {

template<typename T>
class JsonValue final : public JsonElement {
    T m_value;
public:
    explicit JsonValue(T value);

    inline T get() const { return m_value; }
};

typedef JsonValue<int> JsonInt;
typedef JsonValue<float> JsonFloat;
typedef JsonValue<bool> JsonBool;
typedef JsonValue<std::string_view> JsonString;

}