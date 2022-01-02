#include "jsonserializer.h"

#include "jsonutil.h"

namespace pson {

void JsonSerializer::serializeItem(std::shared_ptr<JsonElement> const &element, bool whitespace) {
    switch(element->m_type) {
    case JsonElement::Object:
        serializeObject(getElementAsObject(element, ""), whitespace);
        break;
    case JsonElement::Array:
        serializeArray(getElementAsArray(element, ""), whitespace);
        break;
    case JsonElement::String:
        serializeString(getElementAs<std::string>(element, ""));
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

void JsonSerializer::serializeObject(std::shared_ptr<JsonObject> const &base, bool whitespace) {
    m_output << '{';
    if (whitespace) m_output << '\n';
    m_currentIndent++;

    auto properties = base->getProperties();
    auto propertyOrder = base->getProperyOrder();
    for (auto i = 0; i < propertyOrder.size(); i++) {
        if (whitespace) insertIndent();
        m_output << '"' << propertyOrder[i] << "\":";
        if (whitespace) m_output << ' ';
        serializeItem(properties[propertyOrder[i]], whitespace);
        if (i != propertyOrder.size() - 1)
            m_output << ',';
        if (whitespace) m_output << '\n';
    }

    m_currentIndent--;
    if (whitespace) insertIndent();
    m_output << '}';
}

void JsonSerializer::serializeArray(std::shared_ptr<JsonArray> const &base, bool whitespace) {
    m_output << "[";
    if (whitespace) m_output << '\n';
    m_currentIndent++;

    auto items = base->getItems();
    for (auto it = items.begin(); it != items.end(); it++) {
        if (whitespace) insertIndent();
        serializeItem(*it, whitespace);
        if (std::next(it) != items.end())
            m_output << ',';
        if (whitespace) m_output << '\n';
    }

    m_currentIndent--;
    if (whitespace) insertIndent();
    m_output << ']';
}

}