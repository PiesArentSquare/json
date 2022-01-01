#include "jsonparser.h"

#include <iostream>

namespace pson {

std::shared_ptr<JsonObject> JsonParser::makeObject() {
    auto object = JsonObject::create();
    fillObject(object);
    return object;
}

void JsonParser::fillObject(std::shared_ptr<JsonObject> const &object) {
    bool isKey = true;
    std::string currentKey;
    advanceEx();
    while (m_current != '}') {
        if (isWhitespace(m_current)) {}
        else if (isKey) {
            if (m_current == '"') currentKey = makeString();
            else if (m_current == ':') isKey = false;
            else throw InvalidJsonParseException("key is not a string", m_currentLine);
        } else {
            if (m_current == ',') isKey = true;
            else if (m_current == '{') {
                object->addProperty(currentKey, makeObject());
            }
            else if (m_current == '[') {
                object->addProperty(currentKey, makeArray());
            }
            else if (m_current == '"') {
                object->addProperty(currentKey, makeString());
            }
            else if (isDigit(m_current) || m_current == '-') {
                auto number = makeNumber();
                if (number.isFloat) object->addProperty(currentKey, number.f);
                else object->addProperty(currentKey, number.i);
            }
            else if (m_current == 't' || m_current == 'f') {
                object->addProperty(currentKey, makeBool());
            }
            else if (m_current == 'n') {
                matchLine("ull");
                object->addNullProperty(currentKey);
            }
            else throw InvalidJsonParseException("invalid value", m_currentLine);
        }
        advanceEx();
    }
}

std::shared_ptr<JsonArray> JsonParser::makeArray() {
    auto array = JsonArray::create();
    advanceEx();
    while (m_current != ']') {
        if (isWhitespace(m_current)) {}
        else if (m_current == ',') {}
        else if (m_current == '{') array->addItem(makeObject());
        else if (m_current == '[') array->addItem(makeArray());
        else if (m_current == '"') array->addItem(makeString());
        else if (isDigit(m_current) || m_current == '-') {
            auto number = makeNumber();
            if (number.isFloat) array->addItem(number.f);
            else array->addItem(number.i);
        }
        else if (m_current == 't' || m_current == 'f') array->addItem(makeBool());
        else if (m_current == 'n') {
            matchLine("ull");
            array->addNullItem();
        }
        else throw InvalidJsonParseException("invalid value", m_currentLine);
        advanceEx();
    }
    return array;
}

std::string JsonParser::makeString() {
    std::string res{};
    advanceEx();
    while (m_current != '"') {
        if (m_current == '\\') advanceEx();
        res += m_current;
        advanceEx();
    }
    return res;
}

JsonParser::Number JsonParser::makeNumber() {
    std::string numberStr{};
    JsonParser::Number number{};

    numberStr += m_current;
    while((isDigit(m_input.peek()) || m_input.peek() == '.')) {
        advanceEx();
        if (m_current == '.') {
            if (number.isFloat) throw InvalidJsonParseException("float had too many decimal points", m_currentLine);
            else number.isFloat = true;
        }
        numberStr += m_current;
    }
    if (number.isFloat) number.f = std::stof(numberStr);
    else number.i = std::stoi(numberStr);
    return number;
}

bool JsonParser::makeBool() {
    if (m_current == 't') {
        matchLine("rue");
        return true;
    } else {
        matchLine("alse");
        return false;
    }
}

JsonParser::JsonParser(std::istream &input, Json &json) : m_input(input) {
    advanceEx();
    do {
        if (isWhitespace(m_current)) continue;
        else if (m_current == '{') fillObject(json.getRoot());
        else throw InvalidJsonParseException("did not start with {", m_currentLine);
    } while (advance());
}

Json JsonParser::parseFile(std::string const &filename) {
    Json json;
    std::ifstream file(filename);
    if (file.is_open()) {
        JsonParser(file, json);
        file.close();
    }
    return json;
}

}