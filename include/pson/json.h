#pragma once

#include "jsonserializer.h"

namespace pson {

class Json {
    std::shared_ptr<JsonObject> m_jsonRoot;
    JsonSerializer m_serializer;
public:
    Json() { m_jsonRoot = std::make_shared<JsonObject>(); };
    Json(Json const &) = default;
    Json(Json &&) = default;
    Json &operator=(Json const &) = default;
    Json &operator=(Json &&) = default;
    ~Json() = default;
    static bool readJson(std::string const &filename, Json &json);

    auto getRoot() { return m_jsonRoot; }
    auto operator->() { return m_jsonRoot; }

    bool serialize(std::string const &filename, int indentSize = 4);
};

}