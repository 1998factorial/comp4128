#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
const int maxn = 1e3 + 10;
const int inf = 1e9;
int g[maxn][maxn];
int N , M;
int dp[maxn][maxn];
//lexicographically smallest end point of the path go through a[i .. j] without crossing (if exist such path)

vector<int> path;
bool vis[maxn];
bool found;

int sub(int x ){
  return (x - 2 + N) % N + 1;
}

int add(int x ){
  return x % N + 1;
}

void DFS(int l , int r , int num , int pos){
  path.push_back(pos);
  if(num >= N){
    if(found)return;
    found = 1;
    for(int i : path)cout << i << endl;
    return;
  }
  int x = sub(l) , y = add(r);
  if(x < y){
    if(g[pos][x] && !found)DFS(x , r , num + 1 , x);
    if(g[pos][y] && !found)DFS(l , y , num + 1 , y);
  }
  else{
    if(g[pos][y] && !found)DFS(l , y , num + 1 , y);
    if(g[pos][x] && !found)DFS(x , r , num + 1 , x);
  }
  path.pop_back();
}

int main(){
  cin >> N >> M;
  for(int i = 1; i <= N; ++i)
    for(int j = 1; j <= N; ++j)
      g[i][j] = 0 , dp[i][j] = inf;
  for(int i = 1; i <= M; ++i){
    int x , y; cin >> x >> y;
    g[x][y] = g[y][x] = 1;
  }
  found = false;
  for(int i = 1; i <= N; ++i){
    DFS(i , i , 1 , i);
  }
  if(!found)cout << -1 << endl;
  return 0;
}
