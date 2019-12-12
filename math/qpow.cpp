#include <iostream>
using namespace std;
typedef long long ll;

ll qpow(ll x , ll n){
  if(n <= 0)return 1;
  ll ret = qpow(x , n / 2);
  ret = ret * ret;
  if(n % 2 == 1)ret *= x;
  return ret;
}

int main(){
  ll a , n;
  cin >> a >> n;
  cout << qpow(a , n) << endl;
}
