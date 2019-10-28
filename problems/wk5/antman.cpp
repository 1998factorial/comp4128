#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;
typedef long long ll;

const ll inf = 1ll << 50;
const int maxn = 5005;
int N;
ll dp[maxn][maxn];
int s , e;
ll X[maxn] , a[maxn] , b[maxn] , c[maxn] , d[maxn];

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> s >> e;
  for(int i = 1; i <= N; ++i)cin >> X[i];
  for(int i = 1; i <= N; ++i)cin >> a[i];
  for(int i = 1; i <= N; ++i)cin >> b[i];
  for(int i = 1; i <= N; ++i)cin >> c[i];
  for(int i = 1; i <= N; ++i)cin >> d[i];
  for(int i = 0; i <= N; ++i){
    for(int j = 0; j <= N; ++j){
      dp[i][j] = inf;
    }
  }
  int tot = 0;
  dp[0][0] = 0;
  for(int i = 1; i <= N; ++i){
    for(int j = 0; j <= i; ++j){
      if(dp[i - 1][j] < inf){
        int S = j , T = tot + S;
        if(i == s){
          if(T)dp[i][j] = min(dp[i][j] , dp[i - 1][j] + c[i] + X[i]);
          dp[i][j + 1] = min(dp[i][j + 1] , dp[i - 1][j] + d[i] - X[i]);
        }
        else if(i == e){
          if(S)dp[i][j - 1] = min(dp[i][j - 1] , dp[i - 1][j] + a[i] + X[i]);
          dp[i][j] = min(dp[i][j] , dp[i - 1][j] + b[i] - X[i]);
        }
        else{
          if(S)dp[i][j] = min(dp[i][j] , dp[i - 1][j] + a[i] + d[i]);
          if(T)dp[i][j] = min(dp[i][j] , dp[i - 1][j] + b[i] + c[i]);
          if(S&&T)dp[i][j - 1] = min(dp[i][j - 1] , dp[i - 1][j] + a[i] + c[i] + 2 * X[i]);
          dp[i][j + 1] = min(dp[i][j + 1] , dp[i - 1][j] + b[i] + d[i] - 2 * X[i]);
        }
      }
    }
    if(i == s)--tot;
    if(i == e)++tot;
    if(i != N && tot == 0)dp[i][0] = inf;
  }
  for(int i = 1; i <= N; ++i){
    for(int j = 0; j <= N; ++j  ){
      printf("dp[%d][%d] = %lld\n" , i , j , dp[i][j]);
    }
  }
  cout << dp[N][0] << endl;
}
