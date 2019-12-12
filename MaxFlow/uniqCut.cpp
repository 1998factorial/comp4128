#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#include <string.h>
#include <cmath>
//#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1500;
const ll INF = 1e12;
const double ep = 1e-8;
int N , M , A , B;
vector<pair<int , int>> E;

struct Edge {
  int from, to;
  ll cap, flow;
  Edge(int u, int v, ll c, ll f) : from(u), to(v), cap(c), flow(f) {}
};

struct Dinic {
  int n, m, s, t;
  vector<Edge> edges;
  vector<int> G[maxn];
  int d[maxn], cur[maxn];
  bool vis[maxn];

  void init(int n) {
    this->n = n - 1;
    for (int i = 0; i < maxn; i++) G[i].clear();
    edges.clear();
  }

  void add(int from, int to, ll cap) {
    edges.push_back(Edge(from, to, cap , 0));
    edges.push_back(Edge(to, from, 0 , 0));
    m = edges.size();
    G[from].push_back(m - 2);
    G[to].push_back(m - 1);
  }

  bool BFS() {
    memset(vis, 0, sizeof(vis));
    queue<int> Q;
    Q.push(s);
    d[s] = 0;
    vis[s] = 1;
    while (!Q.empty()) {
      int x = Q.front();
      Q.pop();
      for (int i = 0; i < G[x].size(); i++) {
        Edge& e = edges[G[x][i]];
        if (!vis[e.to] && e.cap > e.flow) {
          vis[e.to] = 1;
          d[e.to] = d[x] + 1;
          Q.push(e.to);
        }
      }
    }
    return vis[t];
  }

  ll DFS(int x, ll a) {
    if (x == t || a == 0) return a;
    ll flow = 0, f;
    for (int& i = cur[x]; i < G[x].size(); i++) {
      Edge& e = edges[G[x][i]];
      if (d[x] + 1 == d[e.to] && (f = DFS(e.to, min(a, e.cap - e.flow))) > 0) {
        e.flow += f;
        edges[G[x][i] ^ 1].flow -= f;
        flow += f;
        a -= f;
        if (a == 0) break;
      }
    }
    return flow;
  }

  ll maxFlow(int s, int t) {
    this->s = s;
    this->t = t;
    ll flow = 0;
    while (BFS()) {
      memset(cur, 0, sizeof(cur));
      flow += DFS(s, INF);
    }
    return flow;
  }

  void dfs1(int v){
    vis[v] = true;
    for(int i = 0; i < G[v].size(); ++i){
      Edge& e = edges[G[v][i]];
      if(!vis[e.to] && e.cap > e.flow){
        dfs1(e.to);
      }
    }
  }

  void dfs2(int v){
    vis[v] = true;
    for(int i = 0; i < G[v].size(); ++i){
      Edge& e = edges[G[v][i] ^ 1];
      if(!vis[e.from] && e.cap > e.flow){
        dfs2(e.from);
      }
    }
  }

  bool uniq_cut(int s , int t){
    memset(vis , 0 , sizeof(vis));
    dfs1(s);
    dfs2(t);
    for(int i = 1; i <= n; ++i){
      if(!vis[i])return false;
    }
    return true;
  }

  void show(){
    for(auto e : edges){
      printf("(%d - > %d) => cap = %lld , flow = %lld\n" , e.from , e.to , e.cap , e.flow);
    }
  }

};

int main(){
  freopen("attack.in" , "r" , stdin);
  freopen("attack.out" , "w" , stdout);
  while(~scanf("%d %d %d %d", &N , &M , &A , &B)){
    Dinic g;
    g.init(N + 1);
    for(int i = 1; i <= M; ++i){
      int x , y , c;
      scanf("%d %d %d" , &x , &y , &c);
      g.add(x , y , c);
      g.add(y , x , c);
    }
    g.maxFlow(A , B);
    if(g.uniq_cut(A , B))printf("UNIQUE\n");
    else printf("AMBIGUOUS\n");
  }
  fclose(stdin);
  fclose(stdout);
}
