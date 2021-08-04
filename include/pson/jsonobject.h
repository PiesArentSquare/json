#pragma once

#include <unordered_map>
#include <memory>

#include "jsonelement.h"
#include "jsonvalue.h"

namespace pson {

class JsonArray;

class JsonObject final : public JsonElement {
    std::unordered_map<std::string_view, std::shared_ptr<JsonElement>> m_properties;

public:
    JsonObject() : m_properties{}, JsonElement(Object) {}
    static std::shared_ptr<JsonObject> create() { return std::make_shared<JsonObject>(); }

    inline void addProperty(std::string_view const &name, std::shared_ptr<JsonElement> element) { m_properties.insert({name, element}); }
    inline void addProperty(std::string_view const &name, std::string_view value) { m_properties.insert({name, std::make_shared<JsonString>(value)}); }
    inline void addProperty(std::string_view const &name, char const *value) { m_properties.insert({name, std::make_shared<JsonString>(value)}); }
    inline void addProperty(std::string_view const &name, int value) { m_properties.insert({name, std::make_shared<JsonInt>(value)}); }
    inline void addProperty(std::string_view const &name, float value) { m_properties.insert({name, std::make_shared<JsonFloat>(value)}); }
    inline void addProperty(std::string_view const &name, bool value) { m_properties.insert({name, std::make_shared<JsonBool>(value)}); }
    inline void addNullProperty(std::string_view const &name) { m_properties.insert({name, std::make_shared<JsonNull>()}); }

    inline auto getProperties() const { return m_properties; }

    inline Type getType(std::string_view const &key) const { return m_properties.at(key)->m_type; }

    std::shared_ptr<JsonObject> getAsObject(std::string_view const &key) const;
    std::shared_ptr<JsonArray> getAsArray(std::string_view const &key) const;
    std::string_view getAsString(std::string_view const &key) const;
    int getAsInt(std::string_view const &key) const;
    float getAsFloat(std::string_view const &key) const;
    bool getAsBool(std::string_view const &key) const;

};

}