#include "collision_detect3_base.h"

class collision_detect3_sh: public collision_detect3_base{
private:
  int zsize;

  pair<int, int> zoneForPoint(const pair<int, int> &pt, const int &zsize);

  vector<pair<int, int>> zoneForRect(const Rect &rect, int zsize);

public:
  collision_detect3_sh(int zsize, vector<Rect> rects): collision_detect3_base(rects);

  vector<pair<int, int>> intersections();

};
