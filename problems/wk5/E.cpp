#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int inf = 1 << 28;
int N , M , dp[1 << 20];
int g[21][21];
string a;
bool vis[1 << 20];

int solve(int state , int pos){
  if(pos <= 0)return 0;
  if(vis[state])return dp[state];
  int ret = inf;
  for(int i = 0; i < M; ++i){
    if((1 << i) & state){
      int nex = state ^ (1 << i);
      int acc = 0;
      for(int j = 0; j < M; ++j){
        if(j == i)continue;
        acc += g[i][j];
        g[i][j] *= -1;
        g[j][i] *= -1;
      }
      ret = min(ret , solve(nex , pos - 1) + pos * acc);
      for(int j = 0; j < M; ++j){
        if(i == j)continue;
        g[i][j] *= -1;
        g[j][i] *= -1;
      }
    }
  }
  vis[state] = true;
  dp[state] = ret;
  return ret;
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> M;
  cin >> a;
  for(int i = 0; i <= M; ++i){
    for(int j = 0; j <= M; ++j){
      g[i][j] = 0;
    }
  }
  for(int i = 1; i < N; ++i){
    int x = a[i] - 'a';
    int y = a[i - 1] - 'a';
    ++g[x][y];
    ++g[y][x];
  }
  for(int i = 0; i < (1 << M); ++i)
    vis[i] = false , dp[i] = inf;
  for(int i = 0; i < M; ++i){
    dp[(1 << i)] = 0;
    vis[(1 << i)] = true;
  }
  cout << solve((1 << M) - 1 , M - 1) << endl;
  return 0;
}
