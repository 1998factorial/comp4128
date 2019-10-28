#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
#include <set>
#include <map>
using namespace std;
typedef long long ll;
//Pi <= 10^5 , might go over long long
//union find can not take in account of deletion so we do queries reversly

/*
union find 不支持删除边所以我们要反着做
这题很考验代码能力
*/

const int maxn = 5e5 + 10;
int parent[maxn];
ll comp[maxn];
vector<ll> population[maxn];
int query[maxn][3];
int edges[maxn][2];
bool can[maxn];
map<ll , int> cnt; // component size -> number of time appear
int N , M , Q;

int find(int i){
  return (parent[i] == i) ? i : parent[i] = find(parent[i]);
}

void add(int i , int j){
  int x = find(i);
  int y = find(j);
  if(x != y){
    --cnt[comp[x]];
    if(cnt[comp[x]] <= 0)cnt.erase(comp[x]);
    --cnt[comp[y]];
    if(cnt[comp[y]] <= 0)cnt.erase(comp[y]);
    parent[y] = x;
    comp[x] += comp[y];
    ++cnt[comp[x]];
  }
}

void update(int i , ll val){
  int x = find(i);
  --cnt[comp[x]];
  if(cnt[comp[x]] <= 0)cnt.erase(comp[x]);
  comp[x] -= val;
  population[i].pop_back();
  comp[x] += population[i].back();
  ++cnt[comp[x]];
}

int main(){
  cin >> N >> M >> Q;
  for(int i = 1; i <= N; ++i)population[i].clear();
  for(int i = 1; i <= N; ++i){
    ll p;
    cin >> p;
    population[i].push_back(p); //initial population in town i
    parent[i] = i; // ini for union find
  }
  for(int i = 1; i <= M; ++i){
    cin >> edges[i][0] >> edges[i][1]; // read in edges
    can[i] = true; // means the i-th edge can be used
  }
  for(int q = 1; q <= Q; ++q){
    string o;
    cin >> o;
    if(o == "P"){ // change
      query[q][0] = 1;
      cin >> query[q][1] >> query[q][2];
      population[query[q][1]].push_back(query[q][2]);
    }
    else{
      int x; // destory road
      query[q][0] = 0;
      cin >> query[q][1];
      can[query[q][1]] = false;
    }
  }
  //build our graph at the final state
  map<int , int> vis;
  for(int i = 1; i <= N; ++i){
    comp[i] = population[i].back();
    if(vis[find(i)] == 0){
      ++vis[find(i)];
      ++cnt[comp[i]];
    }
  }
  for(int i = 1; i <= M; ++i){
    if(can[i]){
      add(edges[i][0] , edges[i][1]);
    }
  }
  //process query in reverse order
  vector<ll> ret;
  for(int q = Q; q >= 1; --q){
    ret.push_back(cnt.rbegin()->first);
    if(query[q][0] == 1){ // need to update
      int i = query[q][1];
      int j = query[q][2];
      update(i , (ll)j);
    }
    else{ // add edge
      int x = query[q][1];
      add(edges[x][0] , edges[x][1]);
    }
  }
  reverse(ret.begin() , ret.end());
  for(int i = 0; i < ret.size(); ++i){
    cout << ret[i] << endl;
  }
  return 0;
}
