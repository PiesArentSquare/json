#include "pson/json.h"

#include <iostream>

using namespace pson;

int main() {

    Json json{};

    json.root().addProperty("type", "testmod:pressing");
    JsonObject *ingredient = new JsonObject();
    ingredient->addProperty("item", "testmood:silver_ingot");
    json.root().addProperty("type", ingredient);








    delete ingredient;
    return 0;
}