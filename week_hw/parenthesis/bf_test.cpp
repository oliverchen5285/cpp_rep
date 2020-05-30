#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "../catch.hpp"
#include "bf.h"

TEST_CASE("Generate all pairs of parenthesis", "[genAll]") {
  SECTION("Size is equal to 2^(2n)"){
    REQUIRE(genAll(1).size() == 4);
    REQUIRE(genAll(2).size() == 16);
    REQUIRE(genAll(3).size() == 64);
    REQUIRE(genAll(4).size() == 256);
  }
  SECTION("No repeats"){
    vector<string> test_vec = genAll(1);
    set<string> test_set;
    for(const auto &elem: test_vec){
      test_set.insert(elem);
    }
    REQUIRE(test_vec.size() == test_set.size());

    test_vec = genAll(2);
    test_set.clear();
    for(const auto &elem: test_vec){
      test_set.insert(elem);
    }
    REQUIRE(test_vec.size() == test_set.size());

    test_vec = genAll(3);
    test_set.clear();
    for(const auto &elem: test_vec){
      test_set.insert(elem);
    }
    REQUIRE(test_vec.size() == test_set.size());

    test_vec = genAll(4);
    test_set.clear();
    for(const auto &elem: test_vec){
      test_set.insert(elem);
    }
    REQUIRE(test_vec.size() == test_set.size());
  }
}
