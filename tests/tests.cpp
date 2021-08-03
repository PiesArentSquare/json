#include "pson/json.h"

#include <iostream>

using namespace pson;

int main() {

    Json json{};

    json.root().addProperty("type", "testmod:pressing");

    auto ingredient = JsonObject::create();
    ingredient->addProperty("item", "testmood:silver_ingot");
    json.root().addProperty("ingredient", ingredient);

    json.root().addProperty("count", 1);

    auto result = JsonObject::create();
    result->addProperty("item", "testmod:silver_plate");
    json.root().addProperty("result", result);



    std::cout << "type: " <<  json.root().getAsString("type") << ",\n";

    auto readIngredient = json.root().getAsObject("ingredient");
    std::cout << "ingredient.item: " << readIngredient->getAsString("item") << ",\n";

    std::cout << "count: " << json.root().getAsInt("count") << ",\n";

    auto readResult = json.root().getAsObject("result");
    std::cout << "result.item: " << readResult->getAsString("item") << "\n";

    return 0;
}