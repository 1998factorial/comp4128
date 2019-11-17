#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>
#include <string.h>
#include <unordered_map>
#include <unordered_set>
using namespace std;
typedef long long ll;

const ll INF = 1e18;
const int maxn = 2e4 + 10;
const int maxlen = 1e4 + 10;
int N , T;
unordered_set<string> vec[205];
char a[maxlen];

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
  int len;

  void init(int n) {
    len = n;
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

  void show(){
    //int cnt = 0;
    for(int i = 0; i < edges.size(); ++i){
      printf("(%d -> %d) =>  cap = %lld , flow = %lld\n" , edges[i].from , edges[i].to , edges[i].cap , edges[i].flow);
      if(edges[i].from < edges[i].to && edges[i].cap == edges[i].flow){
        //printf("(%d -> %d) =>  cap = %lld , flow = %lld\n" , edges[i].from , edges[i].to , edges[i].cap , edges[i].flow);
        //cnt += edges[i].cap;
      }
    }
    //cout << cnt << endl;
  }


};


int main(){
  scanf("%d " , &T);
  for(int q = 1; q <= T; ++q){
    scanf("%d " , &N);
    for(int i = 1; i <= N; ++i)vec[i].clear();
    int cnt = 1;
    while(cnt <= N && fgets(a , maxlen , stdin) != NULL){
      string t = "";
      for(int i = 0; a[i] ; ++i){
        if(a[i] == ' '){
          vec[cnt].insert(t);
          t = "";
        }
        else if(a[i] != '\n')t += a[i];
      }
      vec[cnt].insert(t);
      ++cnt;
    }
    unordered_map<string , int> id;
    int tot = 0;
    for(int i = 1; i <= N; ++i){
      for(string k : vec[i]){
        if(id[k])continue;
        id[k] = ++tot;
      }
    }
    ll infinity = tot + 1;
    Dinic g;
    g.init(2 * N + 2 * tot + 2);
    int src = 0 , sink = 2 * N + 2 * tot + 1;
    for(int i = 1; i <= N; ++i){
      if(i == 1){ //english sentence
        g.add(src , i , infinity);
        g.add(i , N + 2 * tot + i , infinity * infinity);
        g.add(N + 2 * tot + i , sink , infinity * infinity);
      }
      else if(i == 2){ //french sentence
        g.add(src , i , infinity * infinity);
        g.add(i , N + 2 * tot + i , infinity * infinity);
        g.add(N + 2 * tot + i , sink , infinity);
      }
      else{ //not decided
        g.add(src , i , infinity);
        g.add(i , N + 2 * tot + i , infinity * infinity);
        g.add(N + 2 * tot + i , sink , infinity);
      }
    }
    for(int i = 1; i <= tot; ++i){ //for words
      g.add(N + i , N + tot + i , 1);
    }
    for(int i = 1; i <= N; ++i){
      for(string k : vec[i]){
        int v = id[k];
        g.add(i , N + v , 1);
        g.add(N + tot + v , N + tot * 2 + i , 1);
      }
    }
    cout << "Case #" << q << ": ";
    cout << g.maxFlow(src , sink) - N * infinity << endl;
    //g.show();
  }
}
