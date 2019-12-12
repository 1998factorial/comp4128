#include <iostream>
#include <vector>
#include <string.h>
using namespace std;

/*
  build segment tree over a tree
  use DFS order to complete this
  Problem Statement :
    Given a tree rooted at node 0, each
    node has a value, all values are initially 0. Support the
    following 2 operations.
    Update: Of the form U ai wi. Change the value of node
    ai to wi.
    Query: Of the form Q ai. What is the sum of values in
    the subtree rooted at vertex ai?

    Input First line, V, Q, number of vertices and operations.
    1 ≤ V, Q ≤ 100, 000. The next line specifies the tree.
    V − 1 integers, pi
    , the parent of vertex i (1-indexed).
    The following Q lines describe the updates and queries.
    1 ≤ V, Q ≤ 100, 000.
*/
const int maxn = 1e5 + 10;
vector<int> g[maxn]; // tree
int sum[maxn << 2]; // sum[id] = a[l] + .. + a[r]
int dfn[maxn]; // DFS order
int idfn[maxn]; // inverse DFS order
int L[maxn]; // bound
int tot; // # nodes visited
int N , Q;

void DFS(int v , int p){
  dfn[v] = tot++;
  idfn[tot - 1] = v;
  for(int u : g[v]){
    if(u != p){
      DFS(u , v);
    }
  }
  L[dfn[v]] = tot - 1;
}

void update(int pos , int l , int r , int id , int val){
  if(pos < l || pos > r)return;
  if(pos == l && pos == r){
    sum[id] = val;
  }
  else{
    int m = (l + r) >> 1;
    if(pos <= m)
      update(pos , l , m , id << 1 , val);
    else
      update(pos , m + 1 , r , id << 1 | 1 , val);
    sum[id] = sum[id << 1] + sum[id << 1 | 1];
  }
}

int query(int l , int r , int x , int y , int id){
  if(l <= x && y <= r){
    return sum[id];
  }
  int m = (x + y) >> 1;
  if(m >= r)
    return query(l , r , x , m , id << 1);
  if(m < l)
    return query(l , r , m + 1 , y , id << 1 | 1);
  return query(l , r , x , m , id << 1) + query(l , r , m + 1 , y , id << 1 | 1);
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
  DFS(0 , 0); //construct tree by DFS-order
  memset(sum , 0 , sizeof(sum));
  for(int q = 1; q <= Q; ++q){
    char op; cin >> op;
    if(op == 'U'){
      int node , val; cin >> node >> val;
      update(dfn[node] , 0 , N - 1 , 1 , val);
    }
    if(op == 'Q'){
      int node; cin >> node;
      cout << query(dfn[node] , L[dfn[node]] , 0 , N - 1 , 1) << endl;
    }
  }
}
