#include "collision_detect3_base.h"

class collision_detect3_bf: public collision_detect3_base{
public:
  collision_detect3_bf(vector<Rect> new_rects): collision_detect3_base();

  vector<pair<int, int>> intersections();
}
