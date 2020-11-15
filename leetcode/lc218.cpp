class Solution {
private:
    struct edge{
        int x;
        int h;
        bool start; //technically unnecessary (can check if index already visited)
        int index;
    };
    
    static bool compare_edge(const edge &a, const edge &b){
        if(a.x != b.x){
            return a.x < b.x;
        }
        if(a.start && b.start){
            return a.h > b.h;
        }
        if(!a.start && !b.start){
            return a.h < b.h;
        }
        return a.h > b.h;
    }
public:

    vector<vector<int>> getSkyline(vector<vector<int>>& buildings){

        if(buildings.size() == 0){
            return {};
        }
        vector<edge> edges;
        for(int i = 0; i < buildings.size(); ++i){
            edges.push_back({buildings[i][0], buildings[i][2], true, i});
            edges.push_back({buildings[i][1], buildings[i][2], false, i});
        }
        sort(edges.begin(), edges.end(), compare_edge);
        
        set<pair<int, int>, greater<pair<int, int>>> heights;
        heights.insert({0, -1});
        vector<bool> inside(buildings.size(), false);
        vector<vector<int>> ans;

        for(const auto &elem: edges){
            //add first height to ans
            if(elem.start){ //new building
                inside[elem.index] = true;
                heights.insert({elem.h, elem.index});
            }
            else{ //end of building
                inside[elem.index] = false;
            }

            //iterate through set until find height where inside[index] is true (delete false as you go) ({0, -1} is exception)
            for(auto itr = heights.begin(); itr != heights.end(); ++itr){
                pair<int, int> height = *itr;

                //cout << height.first << ", " << height.second << endl;
                if(height == make_pair(0, -1) || inside[height.second]){
 
                    ans.push_back({elem.x, height.first});
                    break;
                }
                else{

                    heights.erase(itr);
                }
            }

        }
        for(const auto &elem: ans){
            for(const auto &elem2: elem){
                cout << elem2 << " ";
            }
            cout << endl;
        }
        for(int i = 0; i < ans.size()-1; ++i){
            if(ans[i][0] == ans[i+1][0]){ //x values same
                if(ans[i][1] > ans[i+1][1]){
                    ans.erase(ans.begin()+i+1);
                }
                else{
                    ans.erase(ans.begin()+i);
                    --i;
                }
                i = max(-1, i-2);
                continue;
            }
            if(ans[i][1] == ans[i+1][1]){ //y values same
                ans.erase(ans.begin()+i+1);
                i = max(-1, i-2);
                continue;
            }
        }
        return ans;
        //go through ans, remove duplicate x values
        
    }
};
