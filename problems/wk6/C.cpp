#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#include <string.h>
using namespace std;
typedef long long ll;

const int maxn = 1500;
const ll INF = 1ll << 55;
int N , M , X;
vector<pair<int , ll>> p[maxn];

/*
binary search the weight that each bear can carry
build the graph by setting w(i , j) to be floor(w(i , j) / mid),
so each edge's capacity represents the number of bears that can pass through
at the end , check if max flow >= X
be careful of precision issue , use long long , as divde by small number can
result in very large number
*/

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

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> M >> X;
  for(int i = 1; i <= M; ++i){
    int x , y;
    ll c;
    cin >> x >> y >> c;
    p[x].push_back(make_pair(y , c));
  }
  double l = 0 , r = 1e18 , ans = r;
  Dinic g;
  for(int i = 0; i < 100; ++i){ //100 times binary search
    double mid = (l + r) / 2.0;
    g.init(N + 1);
    for(int i = 1 ; i <= N; ++i){
      for(int j = 0; j < p[i].size(); ++j){
        g.add(i , p[i][j].first , p[i][j].second / mid);
      }
    }
    if(g.maxFlow(1 , N) >= X){
      ans = mid;
      l = mid;
    }
    else{
      r = mid;
    }
  }
  printf("%.10f\n" , ans * X);
}
