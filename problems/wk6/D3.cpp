#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <queue>
#include <string.h>
//#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 1500;
const ll INF = 1ll << 50;
int N , M , A , B;

/*
  check if min cut is unique
  after Dinics , dfs from src , add when edge is not at it's full usage
  dfs from sink , be careful , we are considering all nodes that can reach
  sink , where reach means the edges between sink and node are not at their
  full usage
*/
struct Edge
{
    ll from , to , cap , flow;
    bool operator <(const Edge e) const
    {
        if(e.from != from)  return from < e.from;
        else return to < e.to;
    }
    Edge() {}
    Edge(int from , int to , int cap , int flow): from(from) , to(to) , cap(cap) , flow(flow) {}
};

struct Dinic{
    vector<Edge> edges;
    vector<int> G[MAXN];
    bool vis[MAXN];
    int d[MAXN];
    int cur[MAXN];
    int n,m,s,t,maxflow;
    int cnt1,cnt2;
    bool vis1[MAXN];

    void init(int n){
        this->n = n;
        for(int i = 0; i <= n; i++)
            G[i].clear();
        edges.clear();
    }

    void addedge(int from,int to,int cap){
      edges.push_back(Edge(from , to , cap , 0));
      edges.push_back(Edge(to , from , cap , 0));
      m = edges.size();
      G[from].push_back(m - 2);
      G[to].push_back(m - 1);
    }

    void dfs1(int u){
      cnt1++;
      vis1[u] = 1;
      for(int i = 0; i < G[u].size(); i++){
        Edge e = edges[G[u][i]];
          if(!vis1[e.to] && e.cap > e.flow)
            dfs1(e.to);
      }
    }

    void dfs2(int u){
      cnt2++;
      vis1[u] = 1;
      for(int i=0;i<G[u].size();i++){
        Edge e = edges[G[u][i]^1];
          if(!vis1[e.from] && e.cap > e.flow)
            dfs2(e.from);
      }
    }

    bool bfs(){
      memset(vis , 0 , sizeof(vis));
      memset(d , -1 , sizeof(d));
      queue<int> q;
      q.push(s);
      d[s] = maxflow = 0;
      vis[s] = 1;
      while(!q.empty()){
        int u = q.front();
        q.pop();
        int sz = G[u].size();
        for(int i = 0; i < sz; i++){
          Edge e = edges[G[u][i]];
          if(!vis[e.to] && e.cap > e.flow){
            d[e.to] = d[u] + 1;
            vis[e.to] = 1;
            q.push(e.to);
          }
        }
      }
      return vis[t];
    }

    ll dfs(int u , ll a){
      if(u == t || a == 0)return a;
      int sz = G[u].size();
      ll flow = 0, f;
      for(int &i = cur[u]; i < sz; i++){
        Edge &e = edges[G[u][i]];
        if(d[u] + 1 == d[e.to] && (f = dfs(e.to,min(a , e.cap - e.flow))) > 0){
          e.flow += f;
          edges[G[u][i] ^ 1].flow -= f;
          flow += f;
          a -= f;
          if(a == 0)break;
        }
      }
      return flow;
    }

    int Maxflow(int s,int t){
      this->s = s;
      this->t = t;
      int flow = 0;
      while(bfs()){
        memset(cur , 0 , sizeof(cur));
        flow += dfs(s,INF);
      }
      return flow;
    }

};

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  while(cin >> N >> M >> A >> B){
    if(N == 0 && M == 0 && A == 0 && B == 0)break;
    Dinic g;
    g.init(N);
    for(int i = 1; i <= M; ++i){
      int x , y , c;
      cin >> x >> y >> c;
      g.addedge(x , y , c);
    }
    g.cnt1 = 0;
    g.cnt2 = 0;
    memset(g.vis1 , 0 , sizeof(g.vis1));
    g.Maxflow(A , B);
    g.dfs1(A);
    g.dfs2(B);
    if(g.cnt1 + g.cnt2 == N)cout << "UNIQUE\n";
    else cout << "AMBIGUOUS\n";
  }
  return 0;
}
