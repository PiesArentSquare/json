#pragma once

#include <stdexcept>
#include <string>

namespace pson {

class JsonElement {
public:
    enum Type {
        Empty,
        Object,
        Array,
        String,
        Int,
        Float
    } m_type;

    static inline std::string_view getTypeName(Type type) {
        switch(type) {
        case JsonElement::Empty:
            return "empty";
        case JsonElement::Object:
            return "object";
        case JsonElement::Array:
            return "array";
        case JsonElement::String:
            return "string";
        case JsonElement::Int:
            return "int";
        case JsonElement::Float:
            return "float";
        default:
            return "";
        }
    }

protected:
    JsonElement(Type type) : m_type(type) {}
    virtual ~JsonElement() {}
};

class InvalidJsonTypeException : public std::runtime_error {
    std::string_view m_property;
    JsonElement::Type m_type, m_expected;
public:
    InvalidJsonTypeException(std::string_view const &property, JsonElement::Type type, JsonElement::Type expectedType)
        : runtime_error("invalid json type error"), m_property(property), m_type(type), m_expected(expectedType) {}

    virtual const char* what() const throw() {
        static std::string str{""};
        str += runtime_error::what();
        str += ": '";
        str += m_property;
        str += "' is of type ";
        str += JsonElement::getTypeName(m_type);
        str += "; expected ";
        str += JsonElement::getTypeName(m_expected);
        return str.c_str();
    }
};

}