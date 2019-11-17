#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;

const ll mod = 1e9 + 7;
const int maxn = 1e5 + 10;
ll fac[maxn];
ll a[maxn];
int N;

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  fac[0] = 1;
  for(int i = 1; i < maxn; ++i){
    fac[i] = fac[i - 1] * 2 % mod;
  }
  int T;
  cin >> T;
  while(T--){
    cin >> N;
    for(int i = 1; i <= N; ++i)cin >> a[i];
    sort(a + 1 , a + 1 + N);
    ll ret = 0;
    for(int i = 1; i <= N; ++i){
      ll tmp = (fac[i - 1] - fac[N - i]) % mod;
      tmp = tmp * a[i] % mod;
      ret = (ret + tmp) % mod;
    }
    cout << (ret + mod) % mod << endl;
  }
}
