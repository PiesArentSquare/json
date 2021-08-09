#include "pson/json.h"

#include <iostream>
#include <sstream>

using namespace pson;

void serializeTest() {

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
    testarray->addNullItem();
    testarray->addItem(17.9f);
    testarray->addItem(11.8f);
    json->addProperty("testarray", testarray);

    json->addProperty("testbool", true);

    json.serialize("testjson.json");
}

void parseTest() {
    Json json{};
    if(!Json::readJson("testjson1.json", json)) {
        std::cerr << "unable to read json\n";
    }
    json.serialize("testjson1output.json");
}

int main() {
    serializeTest();
    parseTest();

    return 0;
}