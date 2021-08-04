#pragma once

#include <vector>
#include <memory>

#include "jsonelement.h"
#include "jsonvalue.h"

namespace pson {

class JsonObject;

class JsonArray final : public JsonElement {
    std::vector<std::shared_ptr<JsonElement>> m_items;

public:
    JsonArray() : m_items{}, JsonElement(Array) {}
    static std::shared_ptr<JsonArray> create() { return std::make_shared<JsonArray>(); }

    inline void addItem(std::shared_ptr<JsonElement> element) { m_items.push_back(element); }
    inline void addItem(std::string_view value) { m_items.push_back(std::make_shared<JsonString>(value)); }
    inline void addItem(char const *value) { m_items.push_back(std::make_shared<JsonString>(value)); }
    inline void addItem(int value) { m_items.push_back(std::make_shared<JsonInt>(value)); }
    inline void addItem(float value) { m_items.push_back(std::make_shared<JsonFloat>(value)); }
    inline void addItem(bool value) { m_items.push_back(std::make_shared<JsonBool>(value)); }
    inline void addNullItem() { m_items.push_back(std::make_shared<JsonNull>()); }

    inline auto getItems() { return m_items; }

    inline Type getType(size_t index) const { return m_items.at(index)->m_type; }

    std::shared_ptr<JsonObject> getAsObject(size_t index) const;
    std::shared_ptr<JsonArray> getAsArray(size_t index) const;
    std::string_view getAsString(size_t index) const;
    int getAsInt(size_t index) const;
    float getAsFloat(size_t index) const;
    bool getAsBool(size_t index) const;

};

}