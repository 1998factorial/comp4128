#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <string.h>
#include <cstdio>
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

const int maxn = 2e5 + 10;
const ll inf = 1e18;
int N , M;
vector<ii> g[maxn]; //minimum spanning tree
ll ans[maxn];
int a[maxn];
int up[maxn][22];
ll MAX[maxn][22];
ll minval;
int L , timmer , tin[maxn] , tout[maxn];
struct Edge{
  int x , y;
  ll w;
  int id;
  Edge(){}
  Edge(int x_ , int y_ , ll w_ , int id_) : x(x_) , y(y_) , w(w_) , id(id_) {}
  bool operator < (const Edge& other) const {
    return w < other.w;
  }
} edges[maxn];

int find(int x){
  return a[x] == x ? x : a[x] = find(a[x]);
}

void add(int x , int y){
  x = find(x);
  y = find(y);
  if(x != y)
    a[x] = y;
}

void MST(){
  minval = 0;
  vector<int> ids;
  for(int k = 0; k < M; ++k){
    int i = edges[k].x , j = edges[k].y;
    if(find(i) != find(j)){
      add(i , j);
      ids.push_back(edges[k].id);
      minval += edges[k].w;
      g[edges[k].x].emplace_back(edges[k].y , edges[k].w);
      g[edges[k].y].emplace_back(edges[k].x , edges[k].w);
    }
  }
  for(int i : ids)ans[i] = minval;
}

void DFS(int v , int p , ll cost){
  tin[v] = ++timmer;
  up[v][0] = p;
  MAX[v][0] = cost;
  for(int i = 1; i <= L; ++i){
    up[v][i] = up[up[v][i - 1]][i - 1];
    MAX[v][i] = max(MAX[v][i - 1] , MAX[up[v][i - 1]][i - 1]);
  }
  for(auto& e : g[v]){
    if(e.first != p){
      DFS(e.first , v , e.second);
    }
  }
  tout[v] = ++timmer;
}

void preprocess(){
  L = ceil(log2(N));
  for(int i = 1; i <= N; ++i)
    for(int j = 0; j <= L; ++j)
      MAX[i][j] = up[i][j] = 0;
  timmer = 0;
  DFS(1 , 1 , 0);
}

bool isAncestor(int u , int v){ //u is v's ancestor
  return tin[u] <= tin[v] && tout[u] >= tout[v];
}

ll solve(int x , int y){ //return the largest edge on their way to their lca
  ll ret = 0;
  if(isAncestor(x , y)){
    for(int i = L; i >= 0; --i){
      if(!isAncestor(up[y][i] , x)){
        ret = max(ret , MAX[y][i]);
        y = up[y][i];
      }
    }
    ret = max(ret , MAX[y][0]);
  }
  else if(isAncestor(y , x)){
    for(int i = L; i >= 0; --i){
      if(!isAncestor(up[x][i] , y)){
        ret = max(ret , MAX[x][i]);
        x = up[x][i];
      }
    }
    ret = max(ret , MAX[x][0]);
  }
  else{
    int u = x , v = y;
    for(int i = L; i >= 0; --i){
      if(!isAncestor(up[u][i] , y)){
        ret = max(ret , MAX[u][i]);
        u = up[u][i];
      }
    }
    ret = max(ret , MAX[u][0]);
    for(int i = L; i >= 0; --i){
      if(!isAncestor(up[v][i] , x)){
        ret = max(ret , MAX[v][i]);
        v = up[v][i];
      }
    }
    ret = max(ret , MAX[v][0]);
  }
  return ret;
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> M;
  for(int i = 0; i < M; ++i){
    cin >> edges[i].x >> edges[i].y >> edges[i].w;
    edges[i].id = i;
    ans[i] = inf;
  }
  for(int i = 1; i <= N; ++i)a[i] = i;
  sort(edges , edges + M);
  MST();
  preprocess();
  for(int i = 0; i < M; ++i){
    if(ans[edges[i].id] >= inf){
      ans[edges[i].id] = minval - solve(edges[i].x , edges[i].y) + edges[i].w;
    }
  }
  for(int i = 0; i < M; ++i){
    cout << ans[i] << endl;
    //printf("%lld\n" , ans[i]);
  }
}
