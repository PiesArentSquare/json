#pragma once

#include "jsonserializer.h"

namespace pson {

class Json {
    JsonObject m_jsonRoot;
    JsonSerializer serializer;
public:
    Json() = default;
    ~Json() = default;
    static Json &&readJson(std::string const &filename);

    JsonObject &root() { return m_jsonRoot; }
    JsonObject *operator->() { return &m_jsonRoot; }

    bool serialize(std::string const &filename, int indentSize = 4);

};

}