#include <iostream>
#include <vector>
#include <set>
using namespace std;
int N , D;
const int maxn = 1e5 + 10;
const int maxd = 1e6 + 10;
vector<int> start_event[maxn];
vector<int> end_event[maxn];
set<pair<int , int>> sub[maxd];
pair<int , int> ppl[maxn];

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> D;
  for(int i = 1; i <= N; ++i){
    int s , e , v , c;
    cin >> s >> e >> v >> c;
    start_event[s].push_back(i);
    end_event[e].push_back(i);
    ppl[i].first = v;
    ppl[i].second = c;
  }
  int ret = 0;
  for(int i = 0; i < D; ++i){
    for(int j : end_event[i]){
      int v = ppl[j].first , c = ppl[j].second;
      if(sub[c].size()){
        ret -= sub[c].rbegin()->first;
        sub[c].erase(make_pair(v , j));
        if(sub[c].size())ret += sub[c].rbegin()->first;
      }
    }
    for(int j : start_event[i]){
      int v = ppl[j].first , c = ppl[j].second;
      if(sub[c].size())ret -= sub[c].rbegin()->first;
      sub[c].insert(make_pair(v , j));
      ret += sub[c].rbegin()->first;
    }
    cout << ret << endl;
  }
}
