#include "jsonutil.h"

namespace pson {
template<> JsonElement::Type getType<int>() { return JsonElement::Int; }
template<> JsonElement::Type getType<float>() { return JsonElement::Float; }
template<> JsonElement::Type getType<std::string_view>() { return JsonElement::String; }

std::string_view getElementName(size_t index) {
    static std::string name{"element "};
    name += ('0' + index);
    return name;
}

JsonObject *getElementAsObject(JsonElement *element, std::string_view const &name) {
    if (element->m_type == JsonElement::Object)
        return static_cast<JsonObject *>(element);
    throw InvalidJsonTypeException(name, element->m_type, JsonElement::Object);
    return nullptr;
}
JsonObject *getElementAsObject(JsonElement *element, size_t index) { return getElementAsObject(element, getElementName(index)); }

JsonArray *getElementAsArray(JsonElement *element, std::string_view const &name) {
    if (element->m_type == JsonElement::Array)
        return static_cast<JsonArray *>(element);
    throw InvalidJsonTypeException(name, element->m_type, JsonElement::Array);
    return nullptr;
}
JsonArray *getElementAsArray(JsonElement *element, size_t index) { return getElementAsArray(element, getElementName(index)); }

}