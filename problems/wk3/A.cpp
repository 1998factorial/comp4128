#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;
typedef pair<int , int> ii;
const int maxn = 1005;
const int inf = 1 << 28;
int a[maxn][maxn];
int dis[maxn][maxn];
bool vis[maxn][maxn];
int N , M;
int dx[4] = {0 , 1 , 0 , -1}, dy[4] = {1 , 0 , -1 , 0};

struct state{
  int x , y , dis;
  state(int xx , int yy , int d){
    x = xx;
    y = yy;
    dis = d;
  }
  bool operator>(const struct state& o) const {
    return dis > o.dis;
  }
};

int main(){
  int T;
  cin >> T;
  for(int q = 1; q <= T; ++q){
    cin >> N;
    cin >> M;
    for(int i = 1; i <= N; ++i){
      for(int j = 1; j <= M; ++j){
        cin >> a[i][j];
        dis[i][j] = inf;
        vis[i][j] = false;
      }
    }
    dis[1][1] = a[1][1];
    priority_queue<state , vector<state> , greater<state>> pq;
    pq.push(state(1 , 1 , a[1][1]));
    while(!pq.empty()){
      state cur = pq.top();
      pq.pop();
      if(vis[cur.x][cur.y])continue;
      vis[cur.x][cur.y] = true;
      for(int i = 0; i < 4; ++i){
        int xx = cur.x + dx[i];
        int yy = cur.y + dy[i];
        if(xx < 1 || xx > N || yy < 1 || yy > M)continue;
        if(!vis[xx][yy] && dis[xx][yy] > dis[cur.x][cur.y] + a[xx][yy]){
          dis[xx][yy] = dis[cur.x][cur.y] + a[xx][yy];
          pq.push(state(xx , yy , dis[xx][yy]));
        }
      }
    }
    cout << dis[N][M] << endl;
  }
  return 0;
}
