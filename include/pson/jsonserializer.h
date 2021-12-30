#pragma once

#include <ostream>
#include <iomanip>

#include "jsonobject.h"
#include "jsonarray.h"

namespace pson {

class JsonSerializer {
    std::ostream &m_output;
    int m_currentIndent = 0;
    int m_indentSize;
    
    inline void insertIndent() {
        if (m_currentIndent) m_output << std::setw(m_currentIndent * m_indentSize) << ' ';
    }

    inline void serializeString(std::string value) { m_output << '"' << value << '"'; }
    inline void serializeInt(int value) { m_output << value; }
    inline void serializeFloat(float value) {
        m_output << value;
        if (value == (int) value) m_output << ".0";
    }
    inline void serializeBool(bool value) { m_output << (value ? "true" : "false"); }
    inline void serializeNull() { m_output << "null"; }

    void serializeItem(std::shared_ptr<JsonElement> const &element);
    void serializeObject(std::shared_ptr<JsonObject> const &base);
    void serializeArray(std::shared_ptr<JsonArray> const &base);

public:
    JsonSerializer(std::ostream &output, std::shared_ptr<JsonObject> const &root, int indentSize = 4)
        : m_output(output), m_indentSize(indentSize) {
        serializeObject(root);
    }
};

}