#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include "cd3_bf.h"
#include "cd3_sh.h"
#include "cd3_qt.h"

TEST_CASE("Test base functions", "[cd3_base]"){
  cd3_base cd3_base_test;
  SECTION("collide_1d"){
    REQUIRE(cd3_base_test.collide_1d({1, 7},{3, 8}));
    REQUIRE(cd3_base_test.collide_1d({3, 8},{1, 7}));
    REQUIRE(cd3_base_test.collide_1d({5, 6},{1, 12}));
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

TEST_CASE("Test all intersections", "[intersections]"){
  SECTION("base"){
    cd3_base cd3_base_test;
    cd3_base::Rect rect_test;
    rect_test.x = 0; rect_test.y = 0; rect_test.x2 = 50; rect_test.y2 = 50;
    cd3_base_test.add_rect(rect_test);
    
    rect_test.x = 0; rect_test.y = 50; rect_test.x2 = 50; rect_test.y2 = 100;
    cd3_base_test.add_rect(rect_test);

    REQUIRE(cd3_base_test.intersections_bf().size() == 0);

    cd3_base_test.clear_rects();
    
    cd3_base_test.add_rect(rect_test);
    
    rect_test.x = 10; rect_test.y = 60; rect_test.x2 = 40; rect_test.y2 = 90;
    cd3_base_test.add_rect(rect_test);

    REQUIRE(cd3_base_test.intersections_bf().size() == 1);
  }

  SECTION("bf"){
    cd3_bf cd3_bf_test;
    cd3_base::Rect rect_test;
    rect_test.x = 0; rect_test.y = 0; rect_test.x2 = 50; rect_test.y2 = 50;
    cd3_bf_test.add_rect(rect_test);
    
    rect_test.x = 0; rect_test.y = 50; rect_test.x2 = 50; rect_test.y2 = 100;
    cd3_bf_test.add_rect(rect_test);

    REQUIRE(cd3_bf_test.intersections().size() == 0);

    cd3_bf_test.clear_rects();
    
    cd3_bf_test.add_rect(rect_test);
    
    rect_test.x = 10; rect_test.y = 60; rect_test.x2 = 40; rect_test.y2 = 90;
    cd3_bf_test.add_rect(rect_test);

    REQUIRE(cd3_bf_test.intersections().size() == 1);
  }
  
  SECTION("sh"){
    cd3_sh cd3_sh_test;
    cd3_sh_test.zsize = 20; //I just made everything public
    cd3_base::Rect rect_test;
    rect_test.x = 0; rect_test.y = 0; rect_test.x2 = 50; rect_test.y2 = 50;
    cd3_sh_test.add_rect(rect_test);
    
    rect_test.x = 0; rect_test.y = 50; rect_test.x2 = 50; rect_test.y2 = 100;
    cd3_sh_test.add_rect(rect_test);

    REQUIRE(cd3_sh_test.intersections().size() == 0);

    cd3_sh_test.clear_rects();
    
    cd3_sh_test.add_rect(rect_test);
    
    rect_test.x = 10; rect_test.y = 60; rect_test.x2 = 40; rect_test.y2 = 90;
    cd3_sh_test.add_rect(rect_test);

    REQUIRE(cd3_sh_test.intersections().size() == 1);
  }
  
  SECTION("qt"){
    cd3_qt cd3_qt_test;
    cd3_qt_test.bound.x = 0; cd3_qt_test.bound.y = 0; cd3_qt_test.bound.x2 = 100; cd3_qt_test.bound.y2 = 100;
    cd3_base::Rect rect_test;
    rect_test.x = 0; rect_test.y = 0; rect_test.x2 = 50; rect_test.y2 = 50;
    cd3_qt_test.add_rect(rect_test);
    
    rect_test.x = 0; rect_test.y = 50; rect_test.x2 = 50; rect_test.y2 = 100;
    cd3_qt_test.add_rect(rect_test);

    REQUIRE(cd3_qt_test.intersections(1).size() == 0);

    cd3_qt_test.clear_rects();
    
    cd3_qt_test.add_rect(rect_test);
    
    rect_test.x = 10; rect_test.y = 60; rect_test.x2 = 40; rect_test.y2 = 90;
    cd3_qt_test.add_rect(rect_test);
    
    cout << "debug: " << cd3_qt_test.rects.size() << endl;

    REQUIRE(cd3_qt_test.intersections(1).size() == 1);
  }
}
