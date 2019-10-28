#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

const int maxn = 505;
ll v[maxn][maxn];
ll dp[maxn][maxn];
int n;
int a[maxn];
ll inf = 1ll << 55;

//reverse floyd

int main(){
  cin >> n;
  for(int i = 1; i <= n; ++i){
    for(int j = 1; j <= n; ++j){
      cin >> v[i][j];
      dp[i][j] = inf;
    }
  }
  for(int i = 1; i <= n; ++i){
    cin >> a[i];
  }
  vector<ll> ret;
  for(int i = n; i >= 1; --i){
    int k = a[i];
    ll sum = 0;
    for(int x = i; x <= n; ++x){
      int p = a[x]; // add edges connecting k and p , p and k
      dp[k][p] = min(dp[k][p] , v[k][p]);
      dp[p][k] = min(dp[p][k] , v[p][k]);
    }
    // find dp[k][i] , dp[i][k] first
    for(int x = i; x <= n; ++x){
      for(int y = i; y <= n; ++y){
        int p = a[x] , q = a[y];
        dp[k][q] = min(dp[k][q] , dp[k][p] + dp[p][q]);
        dp[q][k] = min(dp[q][k] , dp[q][p] + dp[p][k]);
      }
    }
    // then , use dp[k][i] , dp[i][k] to find new dp[i][j]
    for(int x = i; x <= n; ++x){
      for(int y = i; y <= n; ++y){
        int p = a[x] , q = a[y];
        dp[p][q] = min(dp[p][q] , dp[p][k] + dp[k][q]);
        sum += dp[p][q];
      }
    }
    ret.push_back(sum);
  }
  reverse(ret.begin() , ret.end());
  for(ll x : ret)cout << x << " ";
  cout << endl;
  return 0;
}
