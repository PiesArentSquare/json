#ifndef H_PSONUTIL
#define H_PSONUTIL

#include "pson/jsonobject.h"
#include "pson/jsonarray.h"
#include "pson/jsonvalue.h"

#include <string>

namespace pson {

template<typename T> JsonElement::Type getType();

std::string_view getElementName(size_t index);

template<typename T> T getElementAs(std::shared_ptr<JsonElement> element, std::string_view const &name) {
    if (element->m_type == getType<T>())
        return std::static_pointer_cast<JsonValue<T>>(element)->get();
    throw InvalidJsonTypeException(name, element->m_type, getType<T>());
    return T{0};
}
template<typename T> T getElementAs(std::shared_ptr<JsonElement> element, size_t index) { return getElementAs<T>(element, getElementName(index)); }

std::shared_ptr<JsonObject> getElementAsObject(std::shared_ptr<JsonElement> element, std::string_view const &name);
std::shared_ptr<JsonObject> getElementAsObject(std::shared_ptr<JsonElement> element, size_t index);

std::shared_ptr<JsonArray> getElementAsArray(std::shared_ptr<JsonElement> element, std::string_view const &name);
std::shared_ptr<JsonArray> getElementAsArray(std::shared_ptr<JsonElement> element, size_t index);

}

#endif