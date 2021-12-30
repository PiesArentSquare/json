#include "pson/json.h"
#include "jsonparser.h"

#include <fstream>
#include <iostream>

namespace pson {

bool Json::serialize(std::string const &filepath, int indentSize) {
    try {
        std::ofstream file(filepath);
        if (!file) return false;
        JsonSerializer(file, m_jsonRoot, indentSize);
        file.close();
        return false;
    } catch (std::runtime_error e) {
        std::cerr << e.what() << '\n';
        return true;
    }
}

void Json::readJson(std::string const &filename, Json &json) {
    JsonParser::parseFile(filename, json);
}

}