#include <iostream>
#include <cstring>
#include <string.h>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

const int maxn = 1e3 + 10;
const double inf = 1e18;
int N , M;
int g[maxn][maxn];
double dp[maxn][maxn][2];
int path[maxn][maxn][2];

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
      g[i][j] = 0 , dp[i][j][0] = dp[i][j][1] = inf;
  for(int i = 1; i <= M; ++i){
    int x , y; cin >> x >> y;
    g[x][y] = g[y][x] = 1;
  }
  for(int i = 1; i <= N; ++i)
    for(int j = 0; j < 2; ++j)
      dp[i][i][j] = (double)(N - 1) * log(N * i);
  for(int len = 2; len <= N; ++len){
    for(int i = 1; i <= N; ++i){
      int j = (i + len - 2) % N + 1;
      int i1 = add(i);
      int j1 = sub(j);
      //compute dp[i][j][0]
      if(dp[i1][j][0] < inf && g[i1][i]){
        double val = (double)(N - len) * log(N * i);
        if(dp[i][j][0] > dp[i1][j][0] + val){
          dp[i][j][0] = dp[i1][j][0] + val;
          path[i][j][0] = i1;
        }
      }
      if(dp[i1][j][1] < inf && g[j][i]){
        double val = (double)(N - len) * log(N * i);
        if(dp[i][j][0] > dp[i1][j][1] + val){
          dp[i][j][0] = dp[i1][j][1] + val;
          path[i][j][0] = j;
        }
      }
      //compute dp[i][j][1]
      if(dp[i][j1][0] < inf && g[i][j]){
        double val = (double)(N - len) * log(N * j);
        if(dp[i][j][1] > dp[i][j1][0] + val){
          dp[i][j][1] = dp[i][j1][0] + val;
          path[i][j][1] = i;
        }
      }
      if(dp[i][j1][1] < inf && g[j1][j]){
        double val = (double)(N - len) * log(N * j);
        if(dp[i][j][1] > dp[i][j1][1] + val){
          dp[i][j][1] = dp[i][j1][1] + val;
          path[i][j][1] = j1;
        }
      }
      for(int k = 0; k < 2; ++k)
        printf("dp[%d][%d][%d] = %f\n" , i , j , k , dp[i][j][k]);
    }
  }
}
