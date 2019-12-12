#include <iostream>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

const int maxn = 1e6 + 10;
int T , K;
ll N;
int p[15];
bool vis[maxn];

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> T;
  memset(vis , false , sizeof(vis));
  vector<int> primes;
  primes.push_back(1);
  for(int i = 2; i < maxn; ++i){
    if(!vis[i]){
      primes.push_back(i);
      for(int j = i; j < maxn; j += i){
        vis[j] = 1;
      }
    }
  }
  for(int t = 1; t <= T; ++t){
    cin >> N >> K;
    for(int i = 0; i < K; ++i){
      cin >> p[i];
    }
    bool one = false;
    for(int i = 0; i < K; ++i){
      if(p[i] == 1){
        one = true;
      }
    }
    if(one){
      cout << "Case " << t << ": " << 0 << endl;
      continue;
    }
    ll ret = 0;
    for(int i = 1; i < (1 << K); ++i){
      ll c = 1;
      int cnt = 0;
      for(int j = 0; j < K; ++j){
        if(i & (1 << j))c *= p[j] , ++cnt;
      }
      if(cnt % 2 == 0)
        cnt = -1;
      else
        cnt = 1;
      ret += cnt * N / c;
    }
    ret = N - ret;
    for(int i = 0; i < K; ++i)ret += N >= p[i];
    auto it = lower_bound(primes.begin() , primes.end() , N);
    ret -= it - primes.begin();
    if(*it == N)--ret;
    if(N == 0)ret = 0;
    cout << "Case " << t << ": " << ret << endl;
  }
}
