#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
const int inf = 1 << 28;
const int maxn = 500;
/*
Edmond-Karp algo for max-flow
*/
struct Edge{
  int from , to , cap , flow;
  Edge(int u , int v , int c , int f):from(u) , to(v) , cap(c) , flow(f){}
};

struct EK{
  int n , m;
  vector<Edge> edges;
  vector<int> G[maxn];
  int a[maxn] , p[maxn];

  void init(int n){
    for(int i = 0; i < n; ++i){
      G[i].clear();
    }
    edges.clear();
  }

  void add(int from , int to , int cap){
    edges.push_back(Edge(from , to , cap , 0));
    edges.push_back(Edge(to , from , 0 , 0)); //reverse edge
    m = edges.size();
    G[from].push_back(m - 2);
    G[to].push_back(m - 1);
  }

  int maxFlow(int s , int t){
    int flow = 0;
    for(;;){
      memset(a , 0 , sizeof(a));
      queue<int> q;
      q.push(s);
      a[s] = inf;
      while(!q.empty()){
        int x = q.front();
        q.pop();
        for(int i = 0; i < G[x].size(); ++i){
          Edge& e = edges[G[x][i]];
          if(!a[e.to] && e.cap > e.flow){
            p[e.to] = G[x][i];
            a[e.to] = min(a[x] , e.cap - e.flow);
            q.push(e.to);
          }
        }
        if(a[t])break;
      }
      if(!a[t])break;
      for(int u = t; u != s; u = edges[p[u]].from){
        edges[p[u]].flow += a[t];
        edges[p[u] ^ 1].flow -= a[t];
      }
      flow += a[t];
    }
    return flow;
  }
};


int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  EK g;
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
