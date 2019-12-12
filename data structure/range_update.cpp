#include <iostream>
#include <string.h>
#include <vector>
using namespace std;
/*
Problem Statement:
  Given a weighted tree, all edges
  initially 0. Support Q operations, each one taking one of
  the following forms:
  Update U a b w: Add w to the weight of the edge
  between a and b.
  Query Q a b: Output the shortest distance between a and b.

  lca(a , b) = l
  ans(a , b) = dis(a) + dis(b) - 2 * dis(l)
  dis(i) = shortest distance between root and i

  maintain a sum segtree over the tree , with lazy tags

*/
const int maxn = 1e5 + 10;
int N , Q;
vector<int> g[maxn];
struct node{
  int sum , lazy;
} tree[maxn << 2];
int dfn[maxn] , L[maxn] , depth[maxn];
int tot;

void DFS(int v , int p , int d){
  dfn[v] = tot++;
  depth[v] = d;
  for(int u : g[v]){
    if(u != p){
      DFS(u , v , d + 1);
    }
  }
  L[dfn[v]] = tot - 1;
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> Q;
  for(int i = 0; i < N; ++i)g[i].clear();
  for(int i = 1; i < N; ++i){
    int p; cin >> p;
    g[p].push_back(i);
    g[i].push_back(p);
  }
  tot = 0;
  DFS(0 , 0 , 0);
  memset(tree , 0 , sizeof(tree));
  for(int q = 1; q <= Q; ++q){
    
  }
}
