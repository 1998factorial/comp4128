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
const double INF = 1e12;
const double ep = 1e-8;
int N , M;
vector<pair<int , int>> E;

/*
  fractional programming + binary search optimal ratio + maxflow verify

*/

struct Edge {
  int from, to;
  double cap, flow;
  Edge(int u, int v, double c, double f) : from(u), to(v), cap(c), flow(f) {}
};

struct Dinic {
  int n, m, s, t;
  vector<Edge> edges;
  vector<int> G[maxn];
  int d[maxn], cur[maxn];
  bool vis[maxn];

  void init(int n) {
    for (int i = 0; i < maxn; i++) G[i].clear();
    edges.clear();
  }

  void add(int from, int to, double cap) {
    edges.push_back(Edge(from, to, cap, 0));
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
        if (!vis[e.to] && e.cap - e.flow > ep) {
          vis[e.to] = 1;
          d[e.to] = d[x] + 1;
          Q.push(e.to);
        }
      }
    }
    return vis[t];
  }

  double DFS(int x, double a) {
    if (x == t || a == 0) return a;
    double flow = 0, f;
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

  double maxFlow(int s, int t) {
    this->s = s;
    this->t = t;
    double flow = 0;
    while (BFS()) {
      memset(cur, 0, sizeof(cur));
      flow += DFS(s, INF);
    }
    return flow;
  }

  void show(){
    for(auto& e : edges){
      printf("(%d -> %d) => cap = %f , flow = %f\n" , e.from , e.to , e.cap , e.flow);
    }
  }

  void DFS2(int v){
    vis[v] = true;
    for(int i = 0; i < G[v].size(); ++i){
      Edge e = edges[G[v][i]];
      if(!vis[e.to] && e.cap - e.flow > ep){
        DFS2(e.to);
      }
    }
  }

};

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  while(cin >> N >> M){
    if(M == 0){
      cout << 1 << endl;
      cout << 1 << endl;
      continue;
    }
    E.clear();
    for(int i = 1; i <= M; ++i){
      int u , v;
      cin >> u >> v;
      E.push_back(make_pair(u , v));
    }
    Dinic g;
    int s = 0 , t = N + M + 1;
    double l = 1.0 / N , r = M * 1.0;
    for(int j = 1; j <= log2(M * N * N * N); ++j){
    //while(r - l >= 1.0 * (1.0 / N) * (1.0 / N)){
      double mid = (l + r) * 0.5;
      g.init(N + M + 2);
      for(int i = 0; i < M; ++i){
        g.add(s , i + 1 , 1);
        g.add(i + 1 , M + E[i].first , INF);
        g.add(i + 1 , M + E[i].second , INF);
      }
      for(int i = 1; i <= N; ++i){
        g.add(M + i , t , mid);
      }
      double f = g.maxFlow(s , t);
      if((double)M - f > ep){
        l = mid;
      }
      else{
        r = mid;
      }
    }
    //}
    //dfs to get all selected nodes
    g.init(N + M + 2);
    for(int i = 0; i < M; ++i){
      g.add(s , i + 1 , 1);
      g.add(i + 1 , M + E[i].first , INF);
      g.add(i + 1 , M + E[i].second , INF);
    }
    for(int i = 1; i <= N; ++i){
      g.add(M + i , t , l);
    }
    g.maxFlow(s , t);
    memset(g.vis , 0 , sizeof(g.vis));
    g.DFS2(s);
    vector<int> ppl;
    for(int i = M + 1; i <= M + N; ++i){
      if(g.vis[i])ppl.push_back(i - M);
    }
    cout << ppl.size() << endl;
    for(int i : ppl)cout << i << endl;
    cout << endl;
  }
}
