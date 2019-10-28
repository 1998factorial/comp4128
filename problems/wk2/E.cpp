#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <set>
using namespace std;
typedef pair<int , int> ii;
int N , K;
// K , N <= 2 * 10 ^ 5
/*
贪心思想，将线段先按照s排序再按照f排
显然，对于同一 s ， 若重合数量超过K则删除f最大的线段

证明：若存在最优解在某一s上使用一个f较大的线段，将此线段替换成一个f较小的线段并不会使最优解更差
注意：线段可以重复出现，所以要用multiset
*/
int main(){
  cin >> N >> K;
  vector<vector<int>> events(N , vector<int>(2));
  for(int i = 0; i < N; ++i){
    cin >> events[i][0] >> events[i][1];
  }
  sort(events.begin() , events.end() , [](vector<int>& x , vector<int>& y){
    if(x[0] == y[0])return x[1] < y[1];
    return x[0] < y[0];
  });
  int ret = 0 , overlap = 0;
  multiset<ii> q;
  for(int i = 0; i < N; ++i){
    int s = events[i][0];
    int f = events[i][1];
    while(q.size() && q.begin()->first < s){
      q.erase(q.begin());
      ++ret;
    }
    q.insert(make_pair(f , s));
    if(q.size() > K){
      auto it = prev(q.end());
      q.erase(it);
    }
  }
  ret += q.size();
  cout << ret << endl;
  return 0;
}
