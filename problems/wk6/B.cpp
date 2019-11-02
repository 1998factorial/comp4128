#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5 + 10;
string s;
int N;
ll xi , yi , xf , yf;
ll sum[maxn][2];

bool check(ll m){ //check if (x , y) is reachable from (0 , 0) in m days
  ll x3 = sum[N][0] * (m / (ll)N) + sum[m % N][0];
  ll y3 = sum[N][1] * (m / (ll)N) + sum[m % N][1];
  return abs(xf - x3) + abs(yf - y3) <= m;
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> xi >> yi;
  cin >> xf >> yf;
  cin >> N;
  cin >> s;
  xf -= xi;
  yf -= yi;
  sum[0][0] = sum[0][1] = 0;
  for(int i = 1; i <= N; ++i){
    sum[i][1] = sum[i - 1][1];
    sum[i][0] = sum[i - 1][0];
    if(s[i - 1] == 'L')--sum[i][0];
    if(s[i - 1] == 'R')++sum[i][0];
    if(s[i - 1] == 'U')++sum[i][1];
    if(s[i - 1] == 'D')--sum[i][1];
  }
  // check if reachable
  ll l = 0 , r = 1e18 , ret = -1;
  while(l <= r){
    ll m = (l + r) >> 1;
    if(check(m)){
      ret = m;
      r = m - 1;
    }
    else{
      l = m + 1;
    }
  }
  cout << ret << endl;
}
