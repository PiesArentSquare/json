#include "jsonutil.h"

namespace pson {
template<> JsonElement::Type getType<std::string_view>() { return JsonElement::String; }
template<> JsonElement::Type getType<int>() { return JsonElement::Int; }
template<> JsonElement::Type getType<float>() { return JsonElement::Float; }
template<> JsonElement::Type getType<bool>() { return JsonElement::Bool; }

std::string_view getElementName(size_t index) {
    static std::string name{"element "};
    name += ('0' + index);
    return name;
}

std::shared_ptr<JsonObject> getElementAsObject(std::shared_ptr<JsonElement> element, std::string_view const &name) {
    if (element->m_type == JsonElement::Object)
        return std::static_pointer_cast<JsonObject>(element);
    throw InvalidJsonTypeException(name, element->m_type, JsonElement::Object);
    return nullptr;
}
std::shared_ptr<JsonObject> getElementAsObject(std::shared_ptr<JsonElement> element, size_t index) { return getElementAsObject(element, getElementName(index)); }

std::shared_ptr<JsonArray> getElementAsArray(std::shared_ptr<JsonElement> element, std::string_view const &name) {
    if (element->m_type == JsonElement::Array)
        return std::static_pointer_cast<JsonArray>(element);
    throw InvalidJsonTypeException(name, element->m_type, JsonElement::Array);
    return nullptr;
}
std::shared_ptr<JsonArray> getElementAsArray(std::shared_ptr<JsonElement> element, size_t index) { return getElementAsArray(element, getElementName(index)); }

}