#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;
const ll inf = 1ll << 50;
int p[105][105];
int c[105];
ll dp[105][105][105];
int n , m , K;

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> n >> m >> K;
  for(int i = 1; i <= n; ++i)cin >> c[i];
  for(int i = 1; i <= n; ++i){
    for(int j = 1; j <= m; ++j){
      cin >> p[i][j];
    }
  }
  for(int i = 0; i <= n; ++i){
    for(int j = 0; j <= n; ++j){
      for(int k = 0; k <= m; ++k){
        dp[i][j][k] = inf;
      }
    }
  }
  for(int i = 0; i <= m; ++i)dp[0][0][i] = 0;
  for(int i = 1; i <= n; ++i){
    for(int j = 1; j <= i; ++j){
      if(c[i] == 0){
        for(int k = 1; k <= m; ++k){
          for(int x = 0; x <= m; ++x){
            if(k != x)dp[i][j][k] = min(dp[i][j][k] , dp[i - 1][j - 1][x] + p[i][k]);
            else dp[i][j][k] = min(dp[i][j][k] , dp[i - 1][j][x] + p[i][k]);
          }
        }
      }
      else{
        for(int x = 0; x <= m; ++x){
          if(x != c[i])dp[i][j][c[i]] = min(dp[i][j][c[i]] , dp[i - 1][j - 1][x]);
          else dp[i][j][c[i]] = min(dp[i][j][c[i]] , dp[i - 1][j][x]);
        }
      }
    }
  }
  ll ret = inf;
  for(int i = 1; i <= m; ++i){
    ret = min(ret , dp[n][K][i]);
  }
  if(ret >= inf)cout << -1 << endl;
  else cout << ret << endl;
  return 0;
}
