#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>
#include <string.h>
using namespace std;
typedef long long ll;

const ll INF = 1e18;
const int maxn = 1500;
int N;
int T;
char s[maxn][maxn];
int cnt[maxn][maxn];

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
  cin >> T;
  int dx[4] = {0 , 0 , 1 , -1};
  int dy[4] = {1 , -1 , 0 , 0};
  for(int t = 1; t <= T; ++t){
    cin >> N;
    for(int i = 1; i <= N; ++i){
      cin >> (s[i] + 1);
    }
    memset(cnt , 0 , sizeof(cnt));
    int tot = 0;
    for(int i = 1; i <= N; ++i){
      for(int j = 1; j <= N; ++j){
        if(s[i][j] == '#'){
          ++tot;
          cnt[i][j] = tot;
        }
      }
    }
    Dinic g;
    g.init(2 * tot + 2);
    int src = 0 , sink = 2 * tot + 1;
    for(int i = 1; i <= tot; ++i){
      g.add(src , i , 1);
      g.add(i + tot , sink , 1);
    }
    for(int i = 1; i <= N; ++i){
      for(int j = 1; j <= N; ++j){
        if(s[i][j] == '.')continue;
        for(int k = 0; k < 4; ++k){
          int x = i + dx[k] , y = j + dy[k];
          if(x < 1 || x > N || y < 1 || y > N)continue;
          if(s[x][y] == '#'){
            g.add(cnt[i][j] , tot + cnt[x][y] , 1);
          }
        }
      }
    }
    cout << "Case " << t << ": " << g.maxFlow(src , sink) / 2 << endl;
  }
}
