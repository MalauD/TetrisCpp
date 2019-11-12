#define CATCH_CONFIG_MAIN
#include "./../../lib/catch.hpp"
#include "./../../src/Primitives/Grid.hpp"
#include "SFML/Graphics.hpp"

using namespace TetrisEngine;

TEST_CASE("Test Grid mechanics"){
    SECTION("Test constructor"){
        Grid myGrid = Grid(sf::Vector2i(20,3),20);
        REQUIRE(myGrid.GetSize().x == 20);
        REQUIRE(myGrid.GetSize().y == 3);
    }
}