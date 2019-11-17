#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;

const int maxn = 1e6 + 10;
const ll mod = 1e9 + 7;
ll fac[maxn] , ifac[maxn];
ll cnt[maxn];
ll dp[maxn];
int N;

ll qpow(ll x , ll n){
  if(n <= 0)return 1;
  ll ret = qpow(x , n / 2);
  if(n % 2 == 0)return ret * ret % mod;
  return (ret * ret) % mod * x % mod;
}

ll C(int n , int r){
  return (fac[n] * ifac[r]) % mod * ifac[n - r] % mod;
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N;
  fac[0] = 1;
  for(int i = 1; i <= N; ++i)cin >> cnt[i];
  for(int i = 1; i < maxn; ++i){
    fac[i] = fac[i - 1] * i % mod;
  }
  ifac[maxn - 1] = qpow(fac[maxn - 1] , mod - 2);
  for(int i = maxn - 2; i >= 0; --i){
    ifac[i] = ifac[i + 1] * (i + 1) % mod;
  }
  ll sum = cnt[1];
  dp[1] = 1;
  for(int i = 2; i <= N; ++i){
    dp[i] = C(sum + cnt[i] - 1 , cnt[i] - 1) * dp[i - 1] % mod;
    sum += cnt[i];
  }
  cout << (dp[N] + mod) % mod << endl;
}
