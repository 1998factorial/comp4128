#include <vector>
#include <algorithm>
#include <iostream>
#include <string.h>
using namespace std;
const int maxn = 1e5 + 10;
vector<int> g[maxn];
int dfn[maxn];
int low[maxn];
vector<pair<int, int>> bridges;
int tot , N , M;

void DFS(int v , int p){
  dfn[v] = low[v] = tot++;
  for(int u : g[v]){
    if(u != p){
      if(dfn[u] != -1)low[v] = min(low[v] , dfn[u]);
      else{
        DFS(u , v);
        low[v] = min(low[v] , low[u]);
        if(dfn[u] == low[u])
          bridges.emplace_back(min(u , v) , max(u , v));
      }
    }
  }
}

int main(){
  cin >> N >> M;
  for(int i = 1; i <= M; ++i){
    int x , y; cin >> x >> y;
    g[x].push_back(y);
    g[y].push_back(x);
  }
  tot = 1;
  memset(dfn , -1 , sizeof(dfn));
  DFS(1 , 1);
  for(auto it : bridges)cout << it.first << " " << it.second << endl;
}
