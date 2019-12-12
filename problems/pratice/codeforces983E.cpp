#include <iostream>
#include <vector>
#include <string.h>
using namespace std;
typedef long long ll;
/*
codeforces 983 E
*/
const ll mod = 1e9 + 7;
const int maxn = 2e5 + 10;
int N;
vector<int> g[maxn];
ll dp[maxn];
ll ans[maxn];

ll inverse(ll x , ll n){
  if(n <= 0){
    return 1;
  }
  ll ret = inverse(x , n / 2);
  if(n % 2 == 0){
    return ret * ret % mod;
  }
  return ((ret * ret) % mod ) * x % mod;
}

void DFS1(int v , int p){
  dp[v] = 1;
  int cnt = 0;
  for(int u : g[v]){
    if(u != p){
      DFS1(u , v);
      ++cnt;
      dp[v] = dp[v] * ((dp[u] + 1) % mod) % mod;
    }
  }
}

void DFS2(int v , int p){
  if(v == p){
    ans[v] = dp[v];
  }
  else{
    ans[v] = dp[p] * inverse(dp[v] + 1 , mod - 2) % mod;
    ans[v] = (ans[v] + 1) % mod;
  }
  for(int u : g[v]){
    if(u != p){
      DFS2(u , v);
    }
  }
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N;
  for(int i = 2; i <= N; ++i){
    int p;
    cin >> p;
    g[i].push_back(p);
    g[p].push_back(i);
  }
  memset(dp , 0 , sizeof(dp));
  DFS1(1 , 1);
  DFS2(1 , 1);
  for(int i = 1; i <= N; ++i){
    cout << (ans[i] + mod) % mod << " ";
  }
  cout << endl;
}
