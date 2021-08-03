#pragma once

#include <vector>

#include "jsonelement.h"
#include "jsonvalue.h"

namespace pson {

class JsonObject;

class JsonArray final : public JsonElement {
    std::vector<JsonElement *> m_elements;

public:
    JsonArray() : m_elements{}, JsonElement(Array) {}

    template<typename T>
    inline void addItem(T value) { m_elements.push_back(new JsonValue<T>(value)); }
    inline void addItem(JsonElement *element) { m_elements.push_back(element); }

    inline JsonElement::Type getType(size_t index) const { return m_elements.at(index)->m_type; }

    int getAsInt(size_t index) const;
    float getAsFloat(size_t index) const;
    std::string_view getAsString(size_t index) const;
    JsonObject *getAsObject(size_t index) const;
    JsonArray *getAsArray(size_t index) const;

};

}