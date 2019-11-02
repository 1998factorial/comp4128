#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <queue>
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1500;
const ll INF = 1ll << 50;

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
    for (int i = 0; i < n; i++) G[i].clear();
    edges.clear();
  }

  void add(int from, int to, ll cap) {
    edges.push_back(Edge(from, to, cap, 0));
    edges.push_back(Edge(to, from, 0, 0));
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
};

int N , M;

// 2i is incoming , 2i + 1 is outgoing

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  while(cin >> N){
    Dinic g;
    int s = 0 , t = 2 * N + 2;
    g.init(t + 1);
    for(int i = 1; i <= N; ++i){
      ll C;
      cin >> C;
      g.add(2 * i , 2 * i + 1 , C);
    }
    cin >> M;
    for(int i = 1; i <= M; ++i){
      int x , y;
      ll C;
      cin >> x >> y >> C;
      g.add(2 * x + 1 , 2 * y , C);
    }
    int B , D;
    cin >> B >> D;
    for(int i = 1; i <= B; ++i){
      int x;
      cin >> x;
      g.add(s , 2 * x , INF);
    }
    for(int i = 1; i <= D; ++i){
      int x;
      cin >> x;
      g.add(2 * x + 1 , t , INF);
    }
    cout << g.maxFlow(s , t) << endl;
  }
  return 0;
}
