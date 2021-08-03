#pragma once

#include <unordered_map>

#include "jsonelement.h"
#include "jsonvalue.h"

namespace pson {

class JsonArray;

class JsonObject final : public JsonElement {
    std::unordered_map<std::string_view, JsonElement *> m_items;

public:
    JsonObject() : m_items{}, JsonElement(Type::Object) {}

    inline void addProperty(std::string_view const &name, int value) { m_items.insert({name, new JsonInt(value)}); }
    inline void addProperty(std::string_view const &name, float value) { m_items.insert({name, new JsonFloat(value)}); }
    inline void addProperty(std::string_view const &name, std::string_view value) { m_items.insert({name, new JsonString(value)}); }
    inline void addProperty(std::string_view const &name, JsonElement *element) { m_items.insert({name, element}); }

    inline JsonElement::Type getType(std::string_view const &key) const { return m_items.at(key)->m_type; }

    int getAsInt(std::string_view const &key) const;
    float getAsFloat(std::string_view const &key) const;
    std::string_view getAsString(std::string_view const &key) const;
    JsonObject *getAsObject(std::string_view const &key) const;
    JsonArray *getAsArray(std::string_view const &key) const;

};

}