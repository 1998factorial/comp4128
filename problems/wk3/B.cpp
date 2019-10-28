#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;
typedef pair<int , int> ii;
const int inf = 1 << 28;
int N;
int a[105];
int dis[105];
bool vis[105];
bool goodpath[105];
int g[105][105];
vector<ii> edges;

struct state{
  int pos , hp;
  state(int x , int y){
    pos = x;
    hp = y;
  }
};

bool check_good(int to){
  for(int i = 1; i <= N; ++i){
    vis[i] = false;
    goodpath[i] = false;
  }
  goodpath[1] = true;
  queue<state> q;
  q.push(state(1 , 100)); // start pos and hp
  while(!q.empty()){
    state cur = q.front();
    q.pop();
    if(vis[cur.pos])continue;
    vis[cur.pos] = true;
    for(int i = 1; i <= N; ++i){
      if(!vis[i] && g[cur.pos][i] && a[i] + cur.hp > 0){
        q.push(state(i , a[i] + cur.hp));
        goodpath[i] = true;
      }
    }
  }
  return goodpath[to];
}

bool check_bad(int src){
  for(int i = 1; i <= N; ++i){
    vis[i] = false;
  }
  queue<int> q;
  q.push(src);
  while(!q.empty()){
    int cur = q.front();
    q.pop();
    if(vis[cur])continue;
    vis[cur] = true;
    for(int i = 1; i <= N; ++i){
      if(!vis[i] && g[cur][i]){
        q.push(i);
      }
    }
  }
  return vis[N]; // find any path from src to N
}

void relax(){
  for(int i = 0; i < edges.size(); ++i){
    int from = edges[i].first;
    int to = edges[i].second;
    if(dis[to] < dis[from] + a[to] && dis[from] > 0){
      dis[to] = dis[from] + a[to];
    }
  }
}

bool check_cycle(){ // find positive cycle
  for(int i = 1; i <= N; ++i){
    dis[i] = 0;
  }
  dis[1] = 100;
  for(int i = 1; i <= N - 1; ++i){
    relax();
  }
  bool ret = false;
  for(int i = 0; i < edges.size(); ++i){
    int from = edges[i].first;
    int to = edges[i].second;
    if(dis[to] < dis[from] + a[to]){
      ret |= check_bad(from) && check_good(from); // good path to from , any path from -> N
    }
  }
  return ret;
}

int main(){
  while(cin >> N && N != -1){
    edges.clear();
    for(int i = 1; i <= N; ++i)
      for(int j = 1; j <= N; ++j)
        g[i][j] = 0;
    for(int i = 1; i <= N; ++i){
      cin >> a[i];
      int m;
      cin >> m;
      for(int j = 1; j <= m; ++j){
        int x;
        cin >> x;
        g[i][x] = 1;
        if(x <= N && x >= 1)edges.push_back(make_pair(i , x));
      }
    }
    if(check_good(N) || check_cycle()){ // one good path from 1 to N
      cout << "winnable\n";
    }
    else{
      cout << "hopeless\n";
    }
  }
  return 0;
}
