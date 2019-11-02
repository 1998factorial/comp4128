#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
const int inf = 1 << 28;
const int maxn = 500;

struct Edge{
  int from , to , cap , flow;
  Edge(int u , int v , int c , int f):from(u) , to(v) , cap(c) , flow(f){}
};

struct Dinic{
  int n , m , s , t;
  vector<Edge> edges;
  vector<int> G[maxn];
  int d[maxn] , cur[maxn];
  bool vis[maxn];

  void init(int n){
    for(int i = 0; i < n; ++i){
      G[i].clear();
    }
    edges.clear();
  }

  void add(int from , int to , int cap){
    edges.push_back(Edge(from , to , cap , 0));
    edges.push_back(Edge(to , from , 0 , 0));
    m = edges.size();
    G[from].push_back(m - 2);
    G[to].push_back(m - 1);
  }

  bool BFS(){
    memset(vis , 0 , sizeof(vis));
    queue<int> q;
    q.push(s);
    d[s] = 0;
    vis[s] = true;
    while(!q.empty()){
      int x = q.front();
      q.pop();
      for(int i = 0; i < G[x].size(); ++i){
        Edge& e = edges[G[x][i]];
        if(!vis[e.to] && e.cap > e.flow){
          vis[e.to] = true;
          d[e.to] = d[x] + 1;
          q.push(e.to);
        }
      }
    }
    return vis[t];
  }

  int DFS(int x , int a){
    if(x == t || a == 0)return a;
    int flow = 0 , f;
    for(int& i = cur[x]; i < G[x].size(); ++i){
      Edge& e = edges[G[x][i]];
      if(d[x] + 1 == d[e.to] && (f = DFS(e.to , min(a , e.cap - e.flow))) > 0){
        e.flow += f;
        edges[G[x][i] ^ 1].flow -= flow;
        flow += f;
        a -= f;
        if(a == 0)break;
      }
    }
    return flow;
  }

  int maxFlow(int src , int sink){
    this->s = src;
    this->t = sink;
    int flow = 0;
    while(BFS()){
      memset(cur , 0 , sizeof(cur));
      flow += DFS(s , inf);
    }
    return flow;
  }

};

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  Dinic g;
  g.init(6);
  g.add(1 , 2 , 7);
  g.add(1 , 3 , 4);
  g.add(3 , 2 , 3);
  g.add(2 , 4 , 5);
  g.add(2 , 5 , 3);
  g.add(3 , 5 , 2);
  g.add(5 , 4 , 3);
  g.add(4 , 6 , 8);
  g.add(5 , 6 , 5);
  cout << g.maxFlow(1 , 6) << endl;
}
