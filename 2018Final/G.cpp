#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
typedef long long ll;
typedef pair<int , ll > ii;

const int maxn = 1e5 + 10;
const ll inf = 1e18;
int N , E;
vector<ii> g[maxn];
ll dis[maxn][3];
bool vis[maxn];

void dijstra(int src , int x){
  for(int i = 1; i <= N; ++i)
    dis[i][x] = inf , vis[i] = 0;
  dis[src][x] = 0;
  priority_queue<pair<ll , ll> , vector<pair<ll , ll>> , greater<pair<ll , ll>>> q;
  q.push(make_pair(dis[src][x] , src));
  while(!q.empty()){
    auto cur = q.top(); q.pop();
    int v = cur.second;
    if(vis[v])continue;
    vis[v] = true;
    for(auto& e : g[v]){
      if(!vis[e.first] && dis[e.first][x] > dis[v][x] + e.second){
        dis[e.first][x] = dis[v][x] + e.second;
        q.push(make_pair(dis[e.first][x] , e.first));
      }
    }
  }
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> E;
  for(int i = 1; i <= E; ++i){
    ll x , y , z; cin >> x >> y >> z;
    g[x].emplace_back(y , z);
    g[y].emplace_back(x , z);
  }
  dijstra(N , 0);
  dijstra(1 , 1);
  dijstra(2 , 2);
  ll ret = 0;
  for(int i = 1; i <= N; ++i){
    if(dis[i][1] == dis[i][2] && dis[i][1] + dis[i][0] == dis[1][0] && dis[i][2] + dis[i][0] == dis[2][0]){
      if(ret < dis[i][0])ret = dis[i][0];
    }
  }
  cout << ret << endl;
}
