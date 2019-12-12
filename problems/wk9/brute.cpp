#include <iostream>
#include <string.h>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

const int maxn = 1e6 + 10;
int T , K , N;
int p[15];
bool vis[maxn];

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> T;
  memset(vis , false , sizeof(vis));
  set<int> primes;
  primes.insert(1);
  for(int i = 2; i < maxn; ++i){
    if(!vis[i]){
      primes.insert(i);
      for(int j = i; j < maxn; j += i){
        vis[j] = 1;
      }
    }
  }
  for(int t = 1; t <= T; ++t){
    cin >> N >> K;
    for(int i = 0; i < K; ++i)cin >> p[i];
    int ret = 0;
    for(int i = 1; i <= N; ++i){
      if(primes.count(i) == 0){
        bool c = true;
        for(int j = 0; j < K; ++j)
          if(i % p[j] == 0)c = false;
        ret += c;
      }
    }
    cout << "Case " << t << ": " << ret << endl;
  }
}
