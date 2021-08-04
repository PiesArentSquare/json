#include "pson/json.h"
#include "jsonutil.h"

#include <fstream>
#include <iomanip>
#include <iostream>

namespace pson {

void insertIndent(std::ofstream &file, int indent, int indentSize) {
    if (indent) file << std::setw(indent * indentSize) << ' ';
}

void serializeObject(std::ofstream &, JsonObject *, int &, int);
void serializeArray(std::ofstream &, JsonArray *, int &, int);

void serializeString(std::ofstream &file, std::string_view value) {
    file << '"' << value << '"';
}

void serializeInt(std::ofstream &file, int value) {
    file << value;
}

void serializeFloat(std::ostream &file, float value) {
    file << value;
    if (value == (int) value) file << ".0";
}

void serializeBool(std::ofstream &file, bool value) {
    file << (value ? "true" : "false");
}

void serializeNull(std::ostream &file) {
    file << "null";
}

void serializeItem(std::ofstream &file, std::shared_ptr<JsonElement> const &element, int &currentIndent, int indentSize) {
    switch(element->m_type) {
    case JsonElement::Object:
        serializeObject(file, getElementAsObject(element, "").get(), currentIndent, indentSize);
        break;
    case JsonElement::Array:
        serializeArray(file, getElementAsArray(element, "").get(), currentIndent, indentSize);
        break;
    case JsonElement::String:
        serializeString(file, getElementAs<std::string_view>(element, ""));
        break;
    case JsonElement::Int:
        serializeInt(file, getElementAs<int>(element, ""));
        break;
    case JsonElement::Float:
        serializeFloat(file, getElementAs<float>(element, ""));
        break;
    case JsonElement::Bool:
        serializeBool(file, getElementAs<bool>(element, ""));
        break;
    case JsonElement::Null:
        serializeNull(file);
    default:
        break;
    }
}

void serializeObject(std::ofstream &file, JsonObject *base, int &currentIndent, int indentSize) {
    file << "{\n";
    currentIndent++;

    auto properties = base->getProperties();
    for (auto it = properties.begin(); it != properties.end(); it++) {
        insertIndent(file, currentIndent, indentSize);
        file << '"' << it->first << "\": ";
        serializeItem(file, it->second, currentIndent, indentSize);
        if (std::next(it) != properties.end())
            file << ',';
        file << '\n';
    }

    currentIndent--;
    insertIndent(file, currentIndent, indentSize);
    file << '}';
}

void serializeArray(std::ofstream &file, JsonArray *base, int &currentIndent, int indentSize) {
    file << "[\n";
    currentIndent++;

    auto items = base->getItems();
    for (auto it = items.begin(); it != items.end(); it++) {
        insertIndent(file, currentIndent, indentSize);
        serializeItem(file, *it, currentIndent, indentSize);
        if (std::next(it) != items.end())
            file << ',';
        file << '\n';
    }

    currentIndent--;
    insertIndent(file, currentIndent, indentSize);
    file << ']';
}

bool Json::serialize(std::string const &filepath, int indentSize) {
    std::ofstream file(filepath);
    if (!file.is_open()) return 1;

    int currentIndent = 0;
    serializeObject(file, &m_jsonRoot, currentIndent, 4);

    file.close();
    return 0;
}

}