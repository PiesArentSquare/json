#include "pson/jsonserializer.h"

#include "jsonutil.h"

namespace pson {

void JsonSerializer::serializeItem(std::shared_ptr<JsonElement> const &element) {
    switch(element->m_type) {
    case JsonElement::Object:
        serializeObject(getElementAsObject(element, ""));
        break;
    case JsonElement::Array:
        serializeArray(getElementAsArray(element, ""));
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

void JsonSerializer::serializeObject(std::shared_ptr<JsonObject> const &base) {
    m_output << "{\n";
    m_currentIndent++;

    auto properties = base->getProperties();
    auto propertyOrder = base->getProperyOrder();
    for (auto i = 0; i < propertyOrder.size(); i++) {
        insertIndent();
        m_output << '"' << propertyOrder[i] << "\": ";
        serializeItem(properties[propertyOrder[i]]);
        if (i != propertyOrder.size() - 1)
            m_output << ',';
        m_output << '\n';
    }

    m_currentIndent--;
    insertIndent();
    m_output << '}';
}

void JsonSerializer::serializeArray(std::shared_ptr<JsonArray> const &base) {
    m_output << "[\n";
    m_currentIndent++;

    auto items = base->getItems();
    for (auto it = items.begin(); it != items.end(); it++) {
        insertIndent();
        serializeItem(*it);
        if (std::next(it) != items.end())
            m_output << ',';
        m_output << '\n';
    }

    m_currentIndent--;
    insertIndent();
    m_output << ']';
}

}