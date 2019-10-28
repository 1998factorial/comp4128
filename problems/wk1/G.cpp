#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
typedef long long ll;

ll n , k;

int main(){
  string s , t;
  cin >> n >> k;
  cin >> s;
  cin >> t;
  ll cnt = 1ll;
  cnt = min(cnt , k);
  ll ret = 0ll;
  for(int i = 0; i < n; ++i){
    if(cnt >= k){
      ret += k;
      continue;
    }
    if(s[i] == 'a' && t[i] == 'a'){
      cnt = 2 * cnt - 1;
    }
    if(s[i] == 'a' && t[i] == 'b'){
      cnt = 2 * cnt;
    }
    if(s[i] == 'b' && t[i] == 'a'){
      cnt = 2 * cnt - 2;
    }
    if(s[i] == 'b' && t[i] == 'b'){
      cnt = 2 * cnt - 1;
    }
    ret += min(cnt , k);
  }
  cout << ret << endl;
}
