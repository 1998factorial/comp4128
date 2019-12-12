#include <vector>
#include <algorithm>
#include <iostream>
#include <string.h>
#include <queue>
using namespace std;
typedef pair<int , int> ii;
const int maxn = 1e3 + 10;
const int inf = 1e9;
int N , M;
int from , to;
vector<ii> g[maxn];
int dis[maxn];
bool vis[maxn];

void dijkstra(int from , int to){
  for(int i = 1; i <= N; ++i)
    vis[i] = false , dis[i] = inf;
  priority_queue<ii , vector<ii> , greater<ii>> q;
  dis[from] = 0;
  q.push(make_pair(0 , from));
  while(!q.empty()){
    auto cur = q.top();
    q.pop();
    if(vis[cur.second])continue;
    vis[cur.second] = true;
    for(auto e : g[cur.second]){
      int to = e.first , w = e.second;
      if(!vis[to] && dis[to] > dis[cur.second] + w){
        dis[to] = dis[cur.second] + w;
        q.push(make_pair(dis[to] , to));
      }
    }
  }
}

int main(){
  cin >> N >> M;
  for(int i = 1; i <= M; ++i){
    int x , y , w; cin >> x >> y >> w;
    g[x].emplace_back(y , w);
    g[y].emplace_back(x , w);
  }
  cin >> from >> to;
  dijkstra(from , to);
  cout << dis[to] << endl;
}
