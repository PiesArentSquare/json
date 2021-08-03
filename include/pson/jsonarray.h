#pragma once

#include <vector>
#include <memory>

#include "jsonelement.h"
#include "jsonvalue.h"

namespace pson {

class JsonObject;

class JsonArray final : public JsonElement {
    std::vector<std::shared_ptr<JsonElement>> m_elements;

public:
    JsonArray() : m_elements{}, JsonElement(Array) {}
    static std::shared_ptr<JsonArray> create() { return std::make_shared<JsonArray>(); }

    inline void addItem(int value) { m_elements.push_back(std::make_shared<JsonInt>(value)); }
    inline void addItem(float value) { m_elements.push_back(std::make_shared<JsonFloat>(value)); }
    inline void addItem(std::string_view value) { m_elements.push_back(std::make_shared<JsonString>(value)); }
    inline void addItem(std::shared_ptr<JsonElement> element) { m_elements.push_back(element); }

    inline JsonElement::Type getType(size_t index) const { return m_elements.at(index)->m_type; }

    int getAsInt(size_t index) const;
    float getAsFloat(size_t index) const;
    std::string_view getAsString(size_t index) const;
    std::shared_ptr<JsonObject> getAsObject(size_t index) const;
    std::shared_ptr<JsonArray> getAsArray(size_t index) const;

};

}