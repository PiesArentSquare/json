#include "pson/json.h"
#include "jsonserializer.h"

#include <fstream>
#include <iostream>

namespace pson {

bool Json::serialize(std::string const &filepath, int indentSize) {
    return serializer.serialize(filepath, &m_jsonRoot, indentSize);
}

}