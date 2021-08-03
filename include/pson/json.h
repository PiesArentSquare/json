#pragma once

#include "jsonobject.h"
#include "jsonarray.h"

namespace pson {

class Json {
    JsonObject m_jsonRoot;
public:
    Json() = default;
    ~Json() = default;
    static Json &&readJson(std::string_view filename);

    JsonObject &root() { return m_jsonRoot; }

    void serialize(std::string_view filename);

};

}