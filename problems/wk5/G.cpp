#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;
int N , K;
ll a[205];
int dp[205][205][1005];
/*
  dp[i][j][k] = # of ways to use first i people to form j "good groups" where the
  total imbalance is at least k
  good group means a group that has not yet found its maximal
*/

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> K;
  for(int i = 1; i <= N; ++i)cin >> a[i];
  sort(a + 1 , a + N + 1);
  a[0] = 0;
  for(int i = 0; i <= N; ++i)
    for(int j = 0; j <= N; ++j)
      for(int k = 0; k <= K; ++k)
        dp[i][j][k] = 0;
  dp[0][0][0] = 1;
  for(int i = 0; i < N; ++i){
    for(int j = 0; j <= i; ++j){
      for(int k = 0; k <= K; ++k){
        ll ctbn = (a[i + 1] - a[i]) * j;
        if(ctbn + k > K)continue;
        // a[i + 1] is by itself
        dp[i + 1][j][k + ctbn] = (dp[i + 1][j][k + ctbn] + dp[i][j][k]) % mod;
        // a[i + 1] is going to be the end point in one of the j good groups
        if(j > 0)dp[i + 1][j - 1][k + ctbn] = (dp[i + 1][j - 1][k + ctbn] + (ll)dp[i][j][k] * j % mod) % mod;
        // a[i + 1] is going to be one good group
        dp[i + 1][j + 1][k + ctbn] = (dp[i + 1][j + 1][k + ctbn] + dp[i][j][k]) % mod;
        // a[i + 1] is going to be in one group but not as end point
        dp[i + 1][j][k + ctbn] = (dp[i + 1][j][k + ctbn] + (ll)dp[i][j][k] * j % mod) % mod;
      }
    }
  }
  ll ret = 0;
  for(int i = 0; i <= K; ++i){
    ret = (ret + dp[N][0][i]) % mod;
  }
  cout << (ret + mod) % mod << endl;
  return 0;
}
