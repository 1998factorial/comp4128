#include <iostream>
#include <unordered_map>
using namespace std;
typedef long long ll;

const ll mod = 1e9 + 7;
const int maxn = 1e6 + 10;
int N;
ll fac[maxn] , ifac[maxn];


ll qpow(ll x , ll n){
  if(n <= 0)return 1;
  ll ret = qpow(x , n / 2);
  ret = ret * ret % mod;
  if(n % 2 == 1)
    ret = ret * x % mod;
  return ret;
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N;
  unordered_map< ll , ll > cnt;
  fac[0] = 1;
  for(int i = 1; i <= N; ++i){
    ll x; cin >> x; ++cnt[x];
    fac[i] = fac[i - 1] * i % mod;
  }
  ifac[N] = qpow(fac[N] , mod - 2);
  for(int i = N - 1; i >= 0; --i){
    ifac[i] = ifac[i + 1] * (i + 1) % mod;
  }
  ll ret = fac[N];
  for(auto& it : cnt){
    ret = ret * ifac[it.second] % mod;
  }
  cout << ret << endl;
}
