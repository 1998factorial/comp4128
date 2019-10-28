#include <iostream>
#include <cstring>
using namespace std;

int T , n , t , m , a[1500];
int dp[1500][2];
int main(){
  cin >> T;
  for(int c = 1; c <= T; ++c){
    cin >> n >> t >> m;
    for(int i = 1; i <= m; ++i){
      cin >> a[i];
    }
    dp[0][0] = dp[0][1] = 0;
    for(int i = 1; i <= m; ++i)dp[i][0] = 1 << 28 , dp[i][1] = 0;
    for(int i = 1; i <= m; ++i){
      for(int j = i - 1; j >= 0 && i - j <= n; --j){
        if(dp[i][0] > max(dp[j][0] , a[i]) + 2 * t){
          dp[i][0] = max(dp[j][0] , a[i]) + 2 * t;
          dp[i][1] = dp[j][1] + 1;
        }
        else if(dp[i][0] == max(dp[j][0] , a[i]) + 2 * t){
          dp[i][1] = min(dp[i][1] , dp[j][1] + 1);
        }
      }
    }
    cout << dp[m][0] - t << " " << dp[m][1] << endl;
  }
}
