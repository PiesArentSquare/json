#pragma once

#include <fstream>
#include <iomanip>

#include "jsonobject.h"
#include "jsonarray.h"

namespace pson {

class JsonSerializer {
    std::ofstream m_file;
    int m_currentIndent = 0;
    int m_indentSize;
    
    inline void insertIndent() {
        if (m_currentIndent) m_file << std::setw(m_currentIndent * m_indentSize) << ' ';
    }

    inline void serializeString(std::string value) { m_file << '"' << value << '"'; }
    inline void serializeInt(int value) { m_file << value; }
    inline void serializeFloat(float value) {
        m_file << value;
        if (value == (int) value) m_file << ".0";
    }
    inline void serializeBool(bool value) { m_file << (value ? "true" : "false"); }
    inline void serializeNull() { m_file << "null"; }

    void serializeItem(std::shared_ptr<JsonElement> const &element);
    void serializeObject(std::shared_ptr<JsonObject> const &base);
    void serializeArray(std::shared_ptr<JsonArray> const &base);

public:
    inline bool serialize(std::string const &filepath, std::shared_ptr<JsonObject> const &root, int indentSize = 4) {
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