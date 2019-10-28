#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
typedef long long ll;

const int maxn = 1e5 + 10;
const ll inf = 1ll << 50;
int N , Q , s;
int cnt;

bool seen[maxn * 8];

struct edge{
  int to;
  ll w;
  edge(int tt , ll ww){
    to = tt;
    w = ww;
  }
};

vector<edge> g[maxn * 8]; // graph
ll dis[maxn * 8];
bool vis[maxn * 8];
int tree[2][maxn << 2];
// the vertice id for [l , r] for incoming node
// the vertice id for [l , r] for outgoing node

void dijstra(int src){
  for(int i = 1; i < cnt; ++i){
    vis[i] = false;
    dis[i] = inf;
  }
  dis[src] = 0;
  priority_queue<pair<ll , int> , vector<pair<ll , int>> , greater<pair<ll , int>>> pq;
  pq.push(make_pair(dis[src] , src));
  while(!pq.empty()){
    auto cur = pq.top();
    pq.pop();
    int v = cur.second;
    if(vis[v])continue;
    vis[v] = true;
    for(auto e : g[v]){
      if(!vis[e.to] && dis[e.to] > dis[v] + e.w){
        dis[e.to] = dis[v] + e.w;
        pq.push(make_pair(dis[e.to] , e.to));
      }
    }
  }
}

void build(int l , int r , int id , int in){
  if(l > r)return;
  tree[in][id] = cnt;
  ++cnt;
  if(l == r){
    if(in == 1) g[tree[in][id]].push_back(edge(l , 0));
    else g[l].push_back(edge(tree[in][id] , 0));
  }
  else{
    int m = (l + r) >> 1;
    build(l , m , id << 1 , in);
    build(m + 1 , r , id << 1 | 1 , in);
    if(in == 1){
      g[tree[in][id]].push_back(edge(tree[in][id << 1] , 0));
      g[tree[in][id]].push_back(edge(tree[in][id << 1 | 1] , 0));
    }
    else{
      g[tree[in][id << 1]].push_back(edge(tree[in][id] , 0));
      g[tree[in][id << 1 | 1]].push_back(edge(tree[in][id] , 0));
    }
  }
}

void update(int v , ll w , int l , int r , int x , int y , int id , int in){
  if(x > y || r < x || l > y)return;
  if(l <= x && r >= y){
    if(in)g[v].push_back(edge(tree[in][id] , w));
    else g[tree[in][id]].push_back(edge(v , w));
  }
  else{
    int m = (x + y) >> 1;
    update(v , w , l , r , x , m , id << 1 , in);
    update(v , w , l , r , m + 1 , y , id << 1 | 1 , in);
  }
}

int main(){
  cin >> N >> Q >> s;
  cnt = N + 1;
  build(1 , N , 1 , 1);
  build(1 , N , 1 , 0);
  // for each incoming node [l , r] , it must be connected to each outgoing node [x , y] if [x , y] is included by [l , r]
  for(int q = 1; q <= Q; ++q){
    int t;
    cin >> t;
    if(t == 1){
      int v , u , w;
      cin >> v >> u >> w;
      g[v].push_back(edge(u , w));
    }
    else if(t == 2){
      int v , l , r;
      ll w;
      cin >> v >> l >> r >> w;
      // add incoming links from v with w
      update(v , w , l , r , 1 , N , 1 , 1);
    }
    else{
      int v , l , r , w;
      cin >> v >> l >> r >> w;
      // add outgoing links to v with w
      update(v , w , l , r , 1 , N , 1 , 0);
    }
  }
  dijstra(s);
  for(int i = 1; i <= N; ++i){
    if(dis[i] < inf)cout << dis[i] << " ";
    else cout << -1 << " ";
  }
  cout << endl;
  return 0;
}
