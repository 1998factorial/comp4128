#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>
using namespace std;

int A[1000][1000];
int N , M;
int dp[1000][1000][4];
//0 -> horizontal , 1 -> vertical , 2 -> left-right , 3 -> right -> left


int main(){
  cin >> N >> M;
  for(int i = 1; i <= N; ++i)
    for(int j = 1; j <= M; ++j)
      cin >> A[i][j];
  int ret = 0;
  memset(dp , 0 , sizeof(dp));
  for(int i = 1; i <= N; ++i){ // i -> i + 1
    for(int j = 1; j <= M; ++j){
      if(A[i][j] == 1){
        if(j - 1 >= 1)dp[i][j][0] = dp[i][j - 1][0] + 1;
        dp[i][j][1] = dp[i - 1][j][1] + 1;
        if(j - 1 >= 1)dp[i][j][2] = dp[i - 1][j - 1][2] + 1;
        if(j + 1 <= M)dp[i][j][3] = dp[i - 1][j + 1][3] + 1;
      }
      else{
        for(int k = 0; k < 4; ++k)dp[i][j][0] = 0;
      }
      for(int k = 0; k < 4; ++k)ret = max(ret , dp[i][j][k]);
    }
  }
  cout << ret << endl;
}
