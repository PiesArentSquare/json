#include "pson/json.h"
#include "jsonparser.h"
#include "jsonserializer.h"

#include <fstream>
#include <iostream>

namespace pson {

void Json::writeToFile(std::string const &filename, int indentSize) {
    JsonSerializer::writeFile(filename, m_jsonRoot, indentSize);
}

Json Json::readFromFile(std::string const &filename) {
    return JsonParser::parseFile(filename);
}

std::string Json::serialize(int indentSize) {
    std::stringstream ss;
    JsonSerializer(ss, m_jsonRoot, indentSize);
    return ss.str();
}


Json Json::deserialize(std::string &input) {
    std::stringstream ss(input);
    Json json;
    JsonParser(ss, json);
    return json;
}

}