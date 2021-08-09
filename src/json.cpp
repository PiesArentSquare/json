#include "pson/json.h"
#include "jsonparser.h"

#include <fstream>
#include <iostream>

namespace pson {

bool Json::serialize(std::string const &filepath, int indentSize) {
    return m_serializer.serialize(filepath, m_jsonRoot, indentSize);
}

bool Json::readJson(std::string const &filename, Json &json) {
    static JsonParser parser{};
    return parser.parseFile(filename, json);
}

}