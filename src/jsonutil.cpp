#include "jsonutil.h"
#include <sstream>

namespace pson {
template<> JsonElement::Type getType<std::string>() { return JsonElement::String; }
template<> JsonElement::Type getType<int>() { return JsonElement::Int; }
template<> JsonElement::Type getType<float>() { return JsonElement::Float; }
template<> JsonElement::Type getType<bool>() { return JsonElement::Bool; }

std::string getElementName(size_t index) {
    static std::stringstream ss;
    ss << index;
    static std::string str = ss.str();
    return str;
}

std::shared_ptr<JsonObject> getElementAsObject(std::shared_ptr<JsonElement> element, std::string const &name) {
    if (element->m_type == JsonElement::Object)
        return std::static_pointer_cast<JsonObject>(element);
    throw InvalidJsonTypeException(name, element->m_type, JsonElement::Object);
    return nullptr;
}
std::shared_ptr<JsonObject> getElementAsObject(std::shared_ptr<JsonElement> element, size_t index) { return getElementAsObject(element, getElementName(index)); }

std::shared_ptr<JsonArray> getElementAsArray(std::shared_ptr<JsonElement> element, std::string const &name) {
    if (element->m_type == JsonElement::Array)
        return std::static_pointer_cast<JsonArray>(element);
    throw InvalidJsonTypeException(name, element->m_type, JsonElement::Array);
    return nullptr;
}
std::shared_ptr<JsonArray> getElementAsArray(std::shared_ptr<JsonElement> element, size_t index) { return getElementAsArray(element, getElementName(index)); }

}