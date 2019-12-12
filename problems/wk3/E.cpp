#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <cmath>
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;
const int maxn = 2e5 + 10;
const ll inf = 1ll << 50;
int N , M;
ll ret[maxn];
int nid[maxn];
vector<ii> g[maxn];
int up[maxn][22]; // up[v][i] = v's 2^i th ancestor
ll dp[maxn][22]; // dp[v][i] = largest edge on v's way to it's 2^i th ancestor
int tin[maxn];
int tout[maxn];
int L , timmer;

int find(int i){
  return nid[i] == i ? i : nid[i] = find(nid[i]);
}

void add(int i , int j){
  i = find(i);
  j = find(j);
  if(i != j)nid[i] = j;
}

ll MST(vector<vector<int>>& edges , vector<int>& id){
  ll sum = 0;
  vector<int> vis;
  for(int i = 0; i < M; ++i){ // build one minimal spanning tree
    int x = id[i];
    int u = edges[x][0] , v = edges[x][1];
    if(find(u) != find(v)){
      add(u , v);
      sum += edges[x][2];
      vis.push_back(x);
      g[u].emplace_back(v , edges[x][2]);
      g[v].emplace_back(u , edges[x][2]);
    }
  }
  for(int x : vis)ret[x] = sum; // edges used in our first spanning tree must have sum as their solution
  return sum;
}

bool isAncestor(int u , int v){
  return tin[u] <= tin[v] && tout[u] >= tout[v];
}

ll findMax(int u , int v){ // return the maximal edge from u and v to their common ancestor
  ll ans = 0;
  if(isAncestor(u , v)){
    //u is v's ancestor
    for(int i = L; i >= 0; --i){
      if(!isAncestor(up[v][i] , u)){
        ans = max(ans , dp[v][i]);
        v = up[v][i];
      }
    }
    ans = max(ans , dp[v][0]);
  }
  else if(isAncestor(v , u)){
    // v is u's ancestor
    for(int i = L; i >= 0; --i){
      if(!isAncestor(up[u][i] , v)){
        ans = max(ans , dp[u][i]);
        u = up[u][i];
      }
    }
    ans = max(ans , dp[u][0]);
  }
  else{
    int x = u , y = v;
    for(int i = L; i >= 0; --i){
      if(!isAncestor(up[x][i] , v)){
        ans = max(ans , dp[x][i]);
        x = up[x][i];
      }
    }
    ans = max(ans , dp[x][0]);
    for(int i = L; i >= 0; --i){
      if(!isAncestor(up[y][i] , u)){
        ans = max(ans , dp[y][i]);
        y = up[y][i];
      }
    }
    ans = max(ans , dp[y][0]);
  }
  return ans;
}

void DFS(int v , int p , int cc){
  tin[v] = ++timmer;
  up[v][0] = p;
  dp[v][0] = (ll)cc;
  for(int i = 1; i <= L; ++i){
    up[v][i] = up[up[v][i - 1]][i - 1]; // v's 2^i th father = v's 2^(i-1) 's 2^(i-1) th father
    dp[v][i] = max(dp[v][i - 1] , dp[up[v][i - 1]][i - 1]);
  }
  for(auto j : g[v]){
    if(j.first != p){
      DFS(j.first , v , j.second);
    }
  }
  tout[v] = ++timmer;
}

void preprocess(){
  for(int i = 1; i <= N; ++i){
    tin[i] = 0;
    tout[i] = 0;
  }
  L = ceil(log2(N));
  timmer = 0;
  for(int i = 1; i <= N; ++i){
    for(int j = 0; j <= L; ++j){
      dp[i][j] = 0;
      up[i][j] = 0;
    }
  }
  DFS(1 , 1 , 0);
}

int main(){
  cin >> N >> M;
  vector<vector<int>> edges;
  vector<int> id;
  for(int i = 0; i < M; ++i){
    vector<int> a(3);
    cin >> a[0] >> a[1] >> a[2];
    edges.push_back(a);
    ret[i] = inf;
    id.push_back(i);
  }
  for(int i = 1; i <= N; ++i){
    nid[i] = i;
    g[i].clear();
  }
  sort(id.begin() , id.end() , [&](int x , int y){
    return edges[x][2] < edges[y][2];
  });
  ll cost = MST(edges , id); // compute the minimal spanning tree
  preprocess();
  for(int i = 0; i < M; ++i){
    int x = id[i];
    if(ret[x] >= inf){ // for edges that have not been included in our tree
      int u = edges[x][0];
      int v = edges[x][1];
      // need to find the common ancestor of u and v , and the edge with largest weight on the way up
      ll rr = findMax(u , v);
      ret[x] = cost - rr + (int)edges[x][2];
    }
  }
  for(int i = 0; i < M; ++i)cout << ret[i] << endl;
  return 0;
}
