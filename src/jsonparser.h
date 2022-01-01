#pragma once

#include <fstream>

#include <pson/json.h>

namespace pson {

class Json;

class InvalidJsonParseException : public std::runtime_error {
    std::string m_error;
    size_t m_lineNumber = 1;
public:
    InvalidJsonParseException(std::string const &error, size_t lineNumber)
        : runtime_error("invalid json parse error"), m_error(error), m_lineNumber(lineNumber) {}

    virtual const char* what() const throw() {
        static std::stringstream ss;
        ss << "line " << m_lineNumber << ": " << runtime_error::what() <<": " << m_error << "\n";
        static std::string str = ss.str();
        return str.c_str();
    }
};

class JsonParser {
    std::istream &m_input;
    char m_current;
    size_t m_currentLine = 1;

    struct Number {
        bool isFloat;
        union {
            int i;
            float f;
        };
    };

    inline bool advance() {
        m_input.get(m_current);
        if (m_current == '\n') m_currentLine++; 
        return !m_input.fail();
    }

    inline void advanceEx() {
        if (!advance()) throw InvalidJsonParseException("prematurely reached stream end", m_currentLine);
    }
    inline void matchLine(std::string str) {
        for (char c : str) {
            advanceEx();
            if (m_current != c) throw InvalidJsonParseException("invalid value", m_currentLine);
        }
    }
    inline bool isWhitespace(char c) {
        return std::string(" \t\n\r").find(c) != std::string::npos;
    }
    inline bool isDigit(char c) {
        return std::string("1234567890").find(c) != std::string::npos;
    }

    std::shared_ptr<JsonObject> makeObject();
    void fillObject(std::shared_ptr<JsonObject> const &object);
    std::shared_ptr<JsonArray> makeArray();
    std::string makeString();
    Number makeNumber();
    bool makeBool();
    void makeNull();

public:
    JsonParser(std::istream &input, Json &json);
    static Json parseFile(std::string const &filename);
};

}