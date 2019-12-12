#include <iostream>
#include <cstdio>
using namespace std;
typedef long long ll;

const ll mod = 1e9 + 7;
ll N , M;
const int maxn = 1e8;
int dp[maxn];
/*
  if N is small , dp[N] = # of ways to get to size N , where 1 magic gem can split to M normal
  dp[N] = dp[N - 1] + dp[N - M]

*/
int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> M;
  for(int i = 0; i < M; ++i)dp[i] = 1;
  for(int i = M; i <= N; ++i){
    dp[i % M] = (dp[(i - 1) % M] + dp[(i - M) % M]) % mod;
    printf("dp[%d] = %d\n" , i , dp[i % M]);
  }
  cout << (dp[N % M] + mod) % mod << endl;
}
