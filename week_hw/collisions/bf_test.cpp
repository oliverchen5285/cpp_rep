#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include "cd3_bf.h"
#include <set>

TEST_CASE("Test if collisions work", "[collisions_detect3_bf]"){
  SECTION("No repeats"){
    collisions_detect3_bf cd3_bf_test;
    set<pair<int, int>> test_set;
    //vector<pair<int, int>> test_vec = cd3_bf_test.intersections();
  }
}
