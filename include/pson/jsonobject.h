#pragma once

#include <unordered_map>
#include <vector>
#include <memory>

#include "jsonelement.h"
#include "jsonvalue.h"

namespace pson {

class JsonArray;

class JsonObject final : public JsonElement {
    std::unordered_map<std::string, std::shared_ptr<JsonElement>> m_properties;
    std::vector<std::string> m_propertyOrder;

    inline void insert(std::pair<std::string, std::shared_ptr<JsonElement>> item) {
        m_properties.insert(item);
        m_propertyOrder.push_back(item.first);
    }

public:
    JsonObject() : m_properties{}, JsonElement(Object) {}
    ~JsonObject() = default;
    static std::shared_ptr<JsonObject> create() { return std::make_shared<JsonObject>(); }

    inline void addProperty(std::string const &name, std::shared_ptr<JsonElement> element) { insert({name, element}); }
    inline void addProperty(std::string const &name, std::string value) { insert({name, std::make_shared<JsonString>(value)}); }
    inline void addProperty(std::string const &name, char const *value) { insert({name, std::make_shared<JsonString>(value)}); }
    inline void addProperty(std::string const &name, int value) { insert({name, std::make_shared<JsonInt>(value)}); }
    inline void addProperty(std::string const &name, float value) { insert({name, std::make_shared<JsonFloat>(value)}); }
    inline void addProperty(std::string const &name, bool value) { insert({name, std::make_shared<JsonBool>(value)}); }
    inline void addNullProperty(std::string const &name) { insert({name, std::make_shared<JsonNull>()}); }

    inline auto getProperties() const { return m_properties; }
    inline auto getProperyOrder() const { return m_propertyOrder; }

    inline Type getType(std::string const &key) const { return m_properties.at(key)->m_type; }

    std::shared_ptr<JsonObject> getAsObject(std::string const &key) const;
    std::shared_ptr<JsonArray> getAsArray(std::string const &key) const;
    std::string getAsString(std::string const &key) const;
    int getAsInt(std::string const &key) const;
    float getAsFloat(std::string const &key) const;
    bool getAsBool(std::string const &key) const;

};

}