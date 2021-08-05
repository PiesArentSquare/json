#pragma once

#include <fstream>
#include <iomanip>

#include "jsonutil.h"

namespace pson {

class JsonSerializer {
    std::ofstream m_file;
    int m_currentIndent = 0;
    int m_indentSize;
    
    void insertIndent() {
        if (m_currentIndent) m_file << std::setw(m_currentIndent * m_indentSize) << ' ';
    }

    void serializeString(std::string_view value) {
        m_file << '"' << value << '"';
    }

    void serializeInt(int value) {
        m_file << value;
    }

    void serializeFloat(float value) {
        m_file << value;
        if (value == (int) value) m_file << ".0";
    }

    void serializeBool(bool value) {
        m_file << (value ? "true" : "false");
    }

    void serializeNull() {
        m_file << "null";
    }

    void serializeItem(std::shared_ptr<JsonElement> const &element) {
        switch(element->m_type) {
        case JsonElement::Object:
            serializeObject(getElementAsObject(element, "").get());
            break;
        case JsonElement::Array:
            serializeArray(getElementAsArray(element, "").get());
            break;
        case JsonElement::String:
            serializeString(getElementAs<std::string_view>(element, ""));
            break;
        case JsonElement::Int:
            serializeInt(getElementAs<int>(element, ""));
            break;
        case JsonElement::Float:
            serializeFloat(getElementAs<float>(element, ""));
            break;
        case JsonElement::Bool:
            serializeBool(getElementAs<bool>(element, ""));
            break;
        case JsonElement::Null:
            serializeNull();
        default:
            break;
        }
    }

    void serializeObject(JsonObject *base) {
        m_file << "{\n";
        m_currentIndent++;

        auto properties = base->getProperties();
        auto propertyOrder = base->getProperyOrder();
        for (auto i = 0; i < propertyOrder.size(); i++) {
            insertIndent();
            m_file << '"' << propertyOrder[i] << "\": ";
            serializeItem(properties[propertyOrder[i]]);
            if (i != propertyOrder.size() - 1)
                m_file << ',';
            m_file << '\n';
        }

        m_currentIndent--;
        insertIndent();
        m_file << '}';
    }

    void serializeArray(JsonArray *base) {
    m_file << "[\n";
    m_currentIndent++;

    auto items = base->getItems();
    for (auto it = items.begin(); it != items.end(); it++) {
        insertIndent();
        serializeItem(*it);
        if (std::next(it) != items.end())
            m_file << ',';
        m_file << '\n';
    }

    m_currentIndent--;
    insertIndent();
    m_file << ']';
}

public:
    inline bool serialize(std::string const &filepath, JsonObject *root, int indentSize = 4) {
        m_file.open(filepath);
        if (!m_file.is_open()) return 1;

        m_currentIndent = 0;
        m_indentSize = indentSize;
        serializeObject(root);

        m_file.close();
        return 0;
    }

};

}