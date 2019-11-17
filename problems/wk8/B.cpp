#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <cmath>
#include <unordered_set>
using namespace std;
typedef long long ll;

int N;

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N;
  unordered_map<int , int > cnt;
  unordered_set<ll> t;
  ll tt = 1;
  t.insert(tt);
  while(tt < N)tt *= 2 , t.insert(tt);
  for(int i = 2; i <= sqrt(N); ++i){
    while(N % i == 0){
      ++cnt[i];
      N /= i;
    }
  }
  if(N > 1)++cnt[N];
  int ret = 1 , mx = 0 , mn = 1e9;
  bool extra = false;
  for(auto& it : cnt){
    ret *= it.first;
    mx = max(mx , it.second);
    mn = min(mn , it.second);
    if(t.count(it.second) == 0)extra = true;
  }
  ll num = 1 , ans = 0;
  if(mx > 1){
    while(num < mx)num *= 2 , ++ans;
  }
  extra |= (mx > mn);
  cout << ret << " " << ans + extra << endl;
}
