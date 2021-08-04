#include "pson/json.h"

#include <iostream>

using namespace pson;

int main() {

    Json json{};

    json->addProperty("type", "testmod:pressing");

    auto ingredient = JsonObject::create();
    ingredient->addProperty("item", "testmood:silver_ingot");
    json->addProperty("ingredient", ingredient);

    json->addProperty("count", 3);

    auto result = JsonObject::create();
    result->addProperty("item", "testmod:silver_plate");
    json->addProperty("result", result);

    auto testarray = JsonArray::create();
    testarray->addItem(12.1f);
    testarray->addItem(9.0f);
    testarray->addItem(17.9f);
    testarray->addItem(11.8f);
    json->addProperty("testarray", testarray);

    json->addProperty("testbool", true);

    json.serialize("testjson.json");

    return 0;
}