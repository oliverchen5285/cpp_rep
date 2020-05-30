#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include "cd3_base.h"

TEST_CASE("Test if cd3_base functions work", "[cd3_base]"){
  cd3_base cd3_base_test;
  SECTION("collide_1d"){
    REQUIRE(cd3_base_test.collide_1d({1, 7},{3, 8}));
    REQUIRE(cd3_base_test.collide_1d({3, 8},{1, 7}));
    REQUIRE(!cd3_base_test.collide_1d({1, 12},{12, 50}));
  }
  SECTION("collide_2d"){
    cd3_base::Rect rect_test, rect_test2;
    rect_test.x = 0; rect_test.y = 0; rect_test.x2 = 50; rect_test.y2 = 50;
    rect_test2.x = 25; rect_test2.y = 25; rect_test2.x2 = 50; rect_test2.y2 = 50;
    REQUIRE(cd3_base_test.collide_2d(rect_test, rect_test2));
    rect_test2.x = 50; rect_test2.y = 50; rect_test2.x2 = 100; rect_test2.y2 = 100;
    REQUIRE(!cd3_base_test.collide_2d(rect_test, rect_test2));
  }
}

TEST_CASE("Meh", "yeh"){
  REQUIRE(1 == 1);
}
