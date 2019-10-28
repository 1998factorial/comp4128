#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>
#include <set>
#include <unordered_set>
using namespace std;
typedef long long ll;
/*
1. if Bi can reach Bj then Bi can reach all Bs between Bi and Bj
2. if Bi and Bj can reach each other then they can be viewed as a signle bomb

keys :
  1. generate a directed graph that has as least edges as possible
  2. run tarjan to find all SCC
  3. treat each SCC as a single point then dp
*/

const int maxn = 1e5 + 10;
int N;
ll X[maxn] , R[maxn];
vector<int> g[maxn]; //directed graph
unordered_set<int> G[maxn]; //SCC graph
int dfn[maxn] , low[maxn] , cnt , tot;
bool instack[maxn] , vis[maxn];
vector<int> S;
int component[maxn];
ll dp[maxn][2]; // left most and right most
int ans[maxn];

void DFS(int v){
  vis[v] = true;
  for(int u : G[v]){
    if(!vis[u])
      DFS(u);
    dp[v][0] = min(dp[v][0] , dp[u][0]);
    dp[v][1] = max(dp[v][1] , dp[u][1]);
  }
}

void tarjan(int v){
  dfn[v] = low[v] = cnt;
  S.push_back(v);
  instack[v] = true;
  ++cnt;
  for(int u : g[v]){
    if(dfn[u] == -1){
      tarjan(u);
      low[v] = min(low[v] , low[u]);
    }
    if(instack[u]){
      low[v] = min(low[v] , dfn[u]);
    }
  }
  if(low[v] == dfn[v]){
    while(!S.empty()){
      int b = S.back();
      component[b] = tot;
      dp[tot][0] = min(dp[tot][0] , X[b] - R[b]);
      dp[tot][1] = max(dp[tot][1] , X[b] + R[b]);
      S.pop_back();
      instack[b] = false;
      if(b == v)break;
    }
    ++tot;
  }
}

int main(){
  scanf("%d" , &N);
  vector<int> id;
  for(int i = 0; i < N; ++i){
    scanf("%lld %lld" , &X[i] , &R[i]);
    id.push_back(i);
    g[i].clear();
    G[i].clear();
    ans[i] = 0;
  }
  sort(id.begin() , id.end() , [&](int x , int y){
    return X[x] > X[y];
  }); //decreasing

  vector<ll> stack;
  for(int i = 0; i < N; ++i){
    int x = id[i];
    while(!stack.empty() && X[x] + R[x] >= X[stack.back()]){ //construct right edges
      g[x].push_back(stack.back());
      stack.pop_back();
    }
    stack.push_back(x);
  }

  sort(id.begin() , id.end() , [&](int x , int y){
    return X[x] < X[y];
  }); //increasing

  stack.clear();
  for(int i = 0; i < N; ++i){ //construct left edges
    int x = id[i];
    while(!stack.empty() && X[x] - R[x] <= X[stack.back()]){
      g[x].push_back(stack.back());
      stack.pop_back();
    }
    stack.push_back(x);
  }

  cnt = 0;
  tot = 0;
  for(int i = 0; i < N; ++i){
    dfn[i] = -1;
    low[i] = 1 << 28;
    instack[i] = false;
    dp[i][0] = 1ll << 40;
    dp[i][1] = -(1ll << 40);
  }
  for(int i = 0; i < N; ++i){
    if(dfn[i] == -1)
      tarjan(i);
  }
  // collapase each SCC into a point
  stack.clear();
  for(int i = 0; i < N; ++i){
    stack.push_back(X[i]);
    int c = component[i];
    for(int u : g[i]){
      int cc = component[u];
      if(c != cc)G[c].insert(cc);
    }
  }
  for(int i = 0; i < tot; ++i){
    vis[i] = false;
  }
  for(int i = 0; i < tot; ++i){
    if(!vis[i])
      DFS(i);
  }
  sort(stack.begin() , stack.end());
  for(int i = 0; i < tot; ++i){
    auto l = lower_bound(stack.begin() , stack.end() , dp[i][0]);
    auto h = upper_bound(stack.begin() , stack.end() , dp[i][1]);
    --h;
    ans[i] = h - l + 1;
  }
  for(int i = 0; i < N; ++i){
    cout << ans[component[i]] << " ";
  }
  cout << endl;
  return 0;
}
