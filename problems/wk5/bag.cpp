#include <cstdio>
#include <iostream>
#include <sstream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <complex>
#include <unordered_set>
#include <unordered_map>
#define REP(i,a,b) for(int i=a;i<b;i++)
#define RREP(i,a,b) for(int i=a;i>=b;i--)
#define FILL(a,b) memset(a,b,sizeof(a))
#define PB push_back
using namespace std;
typedef pair<int,int> ii;
typedef long long ll;
const int L=840;
const int N=9;
ll w;
//w<=1e18
ll cnt[N],dp[N][L*N]; 
/*
11994176272990019
0 6395394930893349 0 0 0 0 0 0
*/

int main(){
  cin>>w;
  for(int i=1;i<=8;++i)cin>>cnt[i];
  memset(dp,-1,sizeof(dp));
  dp[0][0]=0ll;
  for(int i=1;i<=8;++i){
    for(int j=0;j<L*N;++j){
      if(dp[i-1][j]!=-1){
        int up=L/i;
        if(up>cnt[i])up=cnt[i];
        for(int k=0;k<=up;++k){
          ll& d=dp[i][j+k*i];
          d=max(d,dp[i-1][j]+(cnt[i]-k)*i/L);
        }
      }
    }
  }
  for(int i = 1; i <= 8; ++i){
    for(int j = 0; j <= 6720; ++j){
      if(dp[i][j] != -1)printf("dp[%d][%d] = %lld\n"  , i , j , dp[i][j]);
    }
  }
  ll ret=0ll;
  for(int i=0;i<L*N;++i){
    if(i<=w&&dp[8][i]!=-1){
      ret=max(ret,i+L*min(dp[8][i],(w-i)/L));
    }
  }
  cout<<ret<<endl;
}
