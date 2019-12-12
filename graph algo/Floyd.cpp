#include <iostream>
#include <algorithm>
using namespace std;

const int inf = 1e9;
int N , M;
int dp[500][500];

int main(){
  cin >> N >> M;
  for(int i = 1; i <= N; ++i)
    for(int j = 1; j <= N; ++j)
      dp[i][j] = inf;
  for(int i = 1; i <= M; ++i){
    int x , y , w; cin >> x >> y >> w;
    dp[x][y] = dp[y][x] = w;
  }
  for(int i = 1; i <= N; ++i)dp[i][i] = 0;
  for(int k = 1; k <= N; ++k)
    for(int i = 1; i <= N; ++i)
      for(int j = 1; j <= N; ++j)
        dp[i][j] = min(dp[i][j] , dp[i][k] + dp[k][j]);
  for(int i = 1; i <= N; ++i)
    for(int j = 1; j <= N; ++j)
      printf("dp[%d][%d] = %d\n" , i , j , dp[i][j]);
}
