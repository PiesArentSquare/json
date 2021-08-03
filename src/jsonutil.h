#ifndef H_PSONUTIL
#define H_PSONUTIL

#include "pson/jsonobject.h"
#include "pson/jsonarray.h"
#include "pson/jsonvalue.h"

#include <string>

namespace pson {

template<typename T> JsonElement::Type getType();

std::string_view getElementName(size_t index);

template<typename T> T getElementAs(JsonElement *element, std::string_view const &name) {
    if (element->m_type == getType<T>())
        return static_cast<JsonValue<T> *>(element)->get();
    throw InvalidJsonTypeException(name, element->m_type, getType<T>());
    return T{0};
}
template<typename T> T getElementAs(JsonElement *element, size_t index) { return getElementAs<T>(element, getElementName(index)); }

JsonObject *getElementAsObject(JsonElement *element, std::string_view const &name);
JsonObject *getElementAsObject(JsonElement *element, size_t index);

JsonArray *getElementAsArray(JsonElement *element, std::string_view const &name);
JsonArray *getElementAsArray(JsonElement *element, size_t index);

}

#endif