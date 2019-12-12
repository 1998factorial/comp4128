#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;

const int maxn = 8e3 + 10;
const int maxk = 8e2 + 10;
const ll inf = 1e18;
ll dp[maxk][maxn];
ll sum[maxn] , C[maxn];

int N , K;
//cost of segment (j , i]
ll cost(int i , int j){
  return (ll)(i - j) * (sum[i] - sum[j]);
}
//query range [l , r] , solve for dp[k][x , y)
void solve(int l , int r , int x , int y , int k){
  if(x >= y)return;
  int best = -1;
  int mid = (x + y) >> 1;
  dp[k][mid] = inf;
  for(int i = l; i <= min(r , mid); ++i){
    ll val = dp[k - 1][i] + cost(mid , i);
    if(val < dp[k][mid])dp[k][mid] = val , best = i;
  }
  solve(l , best , x , mid, k);
  solve(best , r , mid + 1 , y , k);
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> K;
  sum[0] = 0;
  for(int i = 1; i <= N; ++i)cin >> C[i] , sum[i] = sum[i - 1] + C[i];
  for(int i = 1; i <= N; ++i)dp[1][i] = cost(i , 0);
  for(int k = 2; k <= K; ++k){
    solve(0 , N , 1 , N + 1 , k);
  }
  cout << dp[K][N] << endl;
}
