#include <iostream>
#include <cstring>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;

const int maxn = 1e3 + 10;
int N , M;
int g[maxn][maxn];

vector<int> dp[maxn][maxn][2]; // [1000] [1000] [2]

int add(int x){
  return x % N + 1;
}

int sub(int x){
  return (x - 2 + N) % N + 1;
}

int main(){
  cin >> N >> M;
  for(int i = 1; i <= N; ++i)
    for(int j = 1; j <= N; ++j)
      g[i][j] = 0 , dp[i][j][0].clear() , dp[i][j][1].clear();
  for(int i = 1; i <= M; ++i){
    int x , y; cin >> x >> y;
    g[x][y] = g[y][x] = 1;
  }
  for(int i = 1; i <= N; ++i)dp[i][i][0].push_back(i) , dp[i][i][1].push_back(i);
  for(int len = 2; len <= N; ++len){
    for(int i = 1; i <= N; ++i){
      int j = (i + len - 2) % N + 1;
      int i1 = add(i);
      int j1 = sub(j);
      if(dp[i1][j][0] < dp[i1][j][1]){
        if(dp[i1][j][0].size() == len - 1 && g[dp[i1][j][0].back()][i])
          dp[i][j][0] = dp[i1][j][0] , dp[i][j][0].push_back(i);
        else if(dp[i1][j][1].size() == len - 1 && g[dp[i1][j][1].back()][i])
          dp[i][j][0] = dp[i1][j][1] , dp[i][j][0].push_back(i);
      }
      else{
        if(dp[i1][j][1].size() == len - 1 && g[dp[i1][j][1].back()][i])
          dp[i][j][0] = dp[i1][j][1] , dp[i][j][0].push_back(i);
        else if(dp[i1][j][0].size() == len - 1 && g[dp[i1][j][0].back()][i])
          dp[i][j][0] = dp[i1][j][0] , dp[i][j][0].push_back(i);
      }
      if(dp[i][j1][0] < dp[i][j1][1]){
        if(dp[i][j1][0].size() == len - 1 && g[dp[i][j1][0].back()][j])
          dp[i][j][1] = dp[i][j1][0] , dp[i][j][1].push_back(j);
        else if(dp[i][j1][1].size() == len - 1 && g[dp[i][j1][1].back()][j])
          dp[i][j][1] = dp[i][j1][1] , dp[i][j][1].push_back(j);
      }
      else{
        if(dp[i][j1][1].size() == len - 1 && g[dp[i][j1][1].back()][j])
          dp[i][j][1] = dp[i][j1][1] , dp[i][j][1].push_back(j);
        else if(dp[i][j1][0].size() == len - 1 && g[dp[i][j1][0].back()][j])
          dp[i][j][1] = dp[i][j1][0] , dp[i][j][1].push_back(j);
      }
      //for(int k = 0; k < 2; ++k)
        //dp[i1][j][k].clear() , dp[i][j1][k].clear();
    }
    for(int i = 1; i <= N; ++i){
      int j = (i + len - 3) % N + 1;
      for(int k = 0; k < 2; ++k)dp[i][j][k].clear();
    }
  }
  vector<vector<int>> path;
  for(int i = 1; i <= N; ++i){
    for(int j = 0; j < 2; ++j)
    if(dp[i][sub(i)][j].size())path.push_back(dp[i][sub(i)][j]);
  }
  if(path.size() == 0)cout << -1 << endl;
  else {
    sort(path.begin() , path.end());
    for(int i = 0; i < path[0].size(); ++i)cout << path[0][i] << endl;
  }
}
