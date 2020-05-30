#ifndef __CD3_SH_H__
#define __CD3_SH_H__
#include "cd3_base.h"

class cd3_sh: public cd3_base{
public:
  int zsize;

  pair<int, int> zoneForPoint(const pair<int, int> &pt, const int &zsize);

  vector<pair<int, int>> zoneForRect(const Rect &rect, int zsize);

  //cd3_sh(int zsize, vector<Rect> rects): cd3_base(rects){};

  vector<pair<int, int>> intersections();

};
#endif
