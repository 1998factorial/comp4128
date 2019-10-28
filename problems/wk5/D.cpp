#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;
const int maxn = 2e5 + 10;

int c[maxn];
vector<int> g[maxn];
int N;
ll dp[maxn][2];

/*
  dp[v][0] = # of ways st v is in a component of no 0
  dp[v][1] = # of ways st v is in a component of one 0
*/

void DFS(int v , int p){
  dp[v][c[v]] = 1;
  dp[v][1 - c[v]] = 0;
  for(int x : g[v]){
    if(x == p)continue;
    DFS(x , v);
    ll dpv0 = dp[v][0] , dpv1 = dp[v][1];
    dp[v][0] = (dpv0 * dp[x][0] % mod + dpv0 * dp[x][1]) % mod;
    dp[v][1] = (dpv1 * dp[x][0] % mod + dpv1 * dp[x][1] % mod + dpv0 * dp[x][1] % mod) % mod;
  }
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N;
  for(int i = 0; i < N; ++i)g[i].clear();
  for(int i = 1; i <= N - 1; ++i){
    int j;
    cin >> j;
    g[j].push_back(i);
    g[i].push_back(j);
  }
  for(int i = 0; i < N; ++i)cin >> c[i];
  DFS(0 , -1);
  cout << (dp[0][1] + mod) % mod << endl;
  return 0;
}
