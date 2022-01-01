#pragma once

#include "jsonobject.h"
#include "jsonarray.h"

namespace pson {

class Json {
    std::shared_ptr<JsonObject> m_jsonRoot;
public:
    Json() { m_jsonRoot = std::make_shared<JsonObject>(); };
    Json(Json const &) = default;
    Json(Json &&) = default;
    Json &operator=(Json const &) = default;
    Json &operator=(Json &&) = default;
    ~Json() = default;

    static Json deserialize(std::string &input);
    std::string serialize(int indentSize = 4);

    static Json readFromFile(std::string const &filename);
    void writeToFile(std::string const &filename, int indentSize = 4);

    auto getRoot() { return m_jsonRoot; }
    auto operator->() { return m_jsonRoot; }

};

}