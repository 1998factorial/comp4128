#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
typedef long long ll;
typedef pair<ll , ll> ii;

const int maxn = 3e5 + 10;
const ll inf = 1e18;
int N , M;
ll pcost[maxn];
vector<ii> g[maxn];
ll dis[maxn][2];
bool vis[maxn][2];

struct state{
  ll cost , city , p;
  state(){}
  state(ll co , ll ci , ll p_) : cost(co) , city(ci) , p(p_) {}
  bool operator < (const state& other) const {
    return cost < other.cost;
  }
  bool operator > (const state& other) const {
    return cost > other.cost;
  }
};

void dijstra(int src){
  for(int i = 1; i <= N; ++i)for(int j = 0; j < 2; ++j)
    dis[i][j] = inf ,vis[i][j] = 0;
  dis[src][0] = 0;
  dis[src][1] = pcost[1];
  priority_queue<state , vector<state> , greater<state>> q;
  q.push(state(dis[src][0] , src , 0));
  q.push(state(dis[src][1] , src , 1));
  while(!q.empty()){
    auto cur = q.top(); q.pop();
    ll v = cur.city , p = cur.p , d = cur.cost;
    if(vis[v][p])continue;
    vis[v][p] = 1;
    for(auto& e : g[v]){
      int to = e.first , cost = e.second;
      if(cost > 0){ // road
        if(!vis[to][0] && dis[to][0] > d + cost){
          dis[to][0] = d + cost;
          q.push(state(dis[to][0] , to , 0));
        }
      }
      else{ // air line
        if(p){
          if(!vis[to][1] && dis[to][1] > d){
            dis[to][1] = d;
            q.push(state(dis[to][1] , to , 1));
          }
        }
        else{
          if(!vis[to][1] && dis[to][1] > d + pcost[v]){
            dis[to][1] = d + pcost[v];
            q.push(state(dis[to][1] , to , 1));
          }
        }
      }
    }
  }
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> M;
  for(int i = 1; i <= N; ++i)cin >> pcost[i];
  for(int i = 1; i <= M; ++i){
    ll x , y , z; cin >> x >> y >> z;
    g[x].emplace_back(y , z);
    g[y].emplace_back(x , z);
  }
  dijstra(1);
  ll ret = min(dis[N][0] , dis[N][1]);
  if(ret < inf)cout << ret << endl;
  else cout << -1 << endl;
}
