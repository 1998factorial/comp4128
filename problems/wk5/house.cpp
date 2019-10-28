#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;

int H , W;
int v[1005][1005];
int dp[1005][1005];

int main(){
  cin >> H >> W;
  for(int i = H; i >= 1; --i){
    for(int j = 1; j <= W; ++j){
      cin >> v[i][j];
    }
  }
  int ret = -(1 << 28);
  for(int i = 0; i < W; ++i)dp[0][i] = 0;
  for(int i = 1; i <= H; ++i){
    for(int j = 1; j <= W; ++j){
      dp[i][j] = 0;
      if(j > 1)dp[i][j] += dp[i][j - 1];
      int mx = 
      for(int k = W; k >= j; --k){
        dp[i][j] = max(dp[i][j] , dp[i - 1][k]);
      }
      dp[i][j] += v[i][j];
      //printf("dp[%d][%d] = %d\n" , i , j , dp[i][j]);
      ret = max(ret , dp[i][j]);
    }
  }
  cout << ret << endl;
  return 0;
}
