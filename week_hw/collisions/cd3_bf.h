#ifndef __CD3_BF_H__
#define __CD3_BF_H__

#include "cd3_base.h"

class cd3_bf: public cd3_base{
private:
public:
  //cd3_bf(vector<Rect> new_rects): cd3_base(new_rects);

  vector<pair<int, int>> intersections();
};
#endif
