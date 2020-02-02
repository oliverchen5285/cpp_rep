#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <queue>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

/*
notes:
could have used ordered map for cow names instead of sorting vector
function "findintertimepos" should be renamed "findcowinter"
*/

int barn2;

struct cow{
  int name;
  int weight;
  int startpos;
  bool direction;
};

struct inter{
  int cow1;
  int cow2;
  double time;
  double pos;
};

struct timepos{
  double time;
  double pos;
};

bool sortpos(cow x, cow y){
  return x.startpos < y.startpos;
}

bool sortname(cow x, cow y){
  return x.name < y.name;
}

bool sorttime(inter x, inter y){
  return x.time < y.time;
}

timepos findintertimepos(cow x, cow y){
  //debug
  cout << "debug: enter function findintertimepos" << endl;

  if(x.direction == false){
    swap(x, y);
  }
  //cow x starts at left, goes right
  //cow y starts at right, goes left

  //debug
  cout << "debug: x.startpos = " << x.startpos << endl;
  cout << "debug: y.startpos = " << y.startpos << endl;

  double dist = y.startpos - x.startpos;
  double time = dist/2;

  double pos = x.startpos + dist/2;

  //debug
  cout << "debug: dist = " << dist << endl;
  cout << "debug: time = " << time << endl;
  cout << "debug: pos = " << pos << endl;
  
  timepos ans;
  ans.time = time;
  ans.pos = pos;

  //debug
  cout << "debug: ans.time = " << ans.time << endl;
  cout << "debug: ans.pos = " << ans.pos << endl;

  return ans;
  
}

timepos findbarninter(cow x){
  //debug
  cout << "debug: enter function findbarninter" << endl;
  
  if(x.direction == true){
    //intersect with barn2
    
    timepos ans;
    ans.time = barn2 - x.startpos;
    ans.pos = barn2;
    
    return ans;
    
  }
  else{
    //intersect with barn1 (0)
 
    timepos ans;
    ans.time = x.startpos;
    ans.pos = 0;
    
    return ans;
  }
}

vector<inter> findinter(vector<cow> cowvec){
  //debug
  cout << "debug: enter function findinter" << endl;
  cout << "debug: cowvec" << endl;
  for(int i = 0; i < cowvec.size(); ++i){
    cout << cowvec[i].name << " ";
  }
  cout << endl;

  
  vector<inter> intervec;

  sort(cowvec.begin(), cowvec.end(), sortpos);
  for(int i = 0; i < cowvec.size(); ++i){

    //cow, barn intersection (for every cow)
    inter tempinter;
    tempinter.cow1 = cowvec[i].name;
    tempinter.cow2 = -1;
    
    timepos temptimepos = findbarninter(cowvec[i]);

    tempinter.time = temptimepos.time;
    tempinter.pos = temptimepos.pos;

    intervec.push_back(tempinter);

    if(cowvec[i].direction == false){
      continue;
    }
    else{
      for(int j = 0; j < cowvec.size(); ++j){
        if(j == i){
          continue;
        }
        if(cowvec[j].direction == false){
          //tempinter declared above
          //inter tempinter;
          
          //cow, cow intersection
          tempinter.cow1 = cowvec[i].name;
          tempinter.cow2 = cowvec[j].name;

          //temptimepos declared above
          //timepos temptimepos;

          temptimepos = findintertimepos(cowvec[i], cowvec[j]);
          tempinter.time = temptimepos.time;
          tempinter.pos = temptimepos.pos;

          intervec.push_back(tempinter);

        }
      }
    }
  }

  //debug
  cout << "debug: exit function findinter" << endl;
  cout << "debug: intervec" << endl;
  for(int i = 0; i < intervec.size(); ++i){
    cout << intervec[i].time << " ";
  }
  cout << endl;

  
  return intervec;
}


void swapcow(cow &x, cow &y){
  //debug
  cout << "debug: enter swapcow" << endl;
  int tempweight = x.weight;
  int tempstartpos = x.startpos;
  //bool tempdirection = x.direction;
  
  x.weight = y.weight;
  x.startpos = y.startpos;
  //x.direction = y.direction;
  
  y.weight = tempweight;
  y.startpos = tempstartpos;
  //y.direction = tempdirection;
}


int simulateinter(vector<inter> intervec, vector<cow> cowvec){
  //debug
  cout << "debug: enter function simulateinter" << endl;
  
  int ans = 0;
  int curweight = 0;
  double totalweight = 0;
  
  for(int i = 0; i < cowvec.size(); ++i){
    totalweight += cowvec[i].weight;
  }


  for(int i = 0; i < intervec.size(); ++i){
    if(intervec[i].cow2 == -1){
      //cow, barn intersection
      
      curweight += cowvec[intervec[i].cow1 - 1].weight;
    }
    else{
      //cow, cow intersection

      ans++;
      swapcow(cowvec[intervec[i].cow1 - 1], cowvec[intervec[i].cow2 - 1]);

    }
    //check for termination condition

    if(curweight >= totalweight){
      return ans;
    }
  }
  return 0;
}


int main(){
  
  ifstream fin("meetings.in");
  ofstream fout("meetings.out");
  
  int cownum;
  //barn2 is global

  //cin >> cownum >> barn2;
  fin >> cownum >> barn2;

  vector <cow> cowvec;

  int tempdirection;
  cow tempcow;
  
  for(int i = 0; i < cownum; ++i){
    tempcow.name = i+1;
    //cin >> tempcow.weight;
    //cin >> tempcow.startpos;
    //cin >> tempdirection;
    fin >> tempcow.weight;
    fin >> tempcow.startpos;
    fin >> tempdirection;
    if(tempdirection == 1){
      tempcow.direction = true;
    }
    else{
      tempcow.direction = false;
    }
    cowvec.push_back(tempcow);
    
  }
  
  //list intersections
  vector<inter> intervec = findinter(cowvec);

  //sort intersections (by time) and sort cows (by name)
  sort(intervec.begin(), intervec.end(), sorttime);
  sort(cowvec.begin(), cowvec.end(), sortname);


  //debug
  cout << "debug: intervec" << endl;
  for(int i = 0; i < intervec.size(); ++i){
    cout << intervec[i].time << " ";
  }
  cout << endl;

  cout << "debug: cowvec" << endl;
  for(int i = 0; i < cowvec.size(); ++i){
    cout << cowvec[i].name << " ";
  }
  cout << endl;
  

  //simulate intersections
  int ans = simulateinter(intervec, cowvec);

  //print answer :)
  //cout << ans << endl;
  fout << ans << endl;

}
