#include <iostream>
#include <algorithm>
#include <string.h>
#include <assert.h>
#include <unordered_map>
using namespace std;
typedef long long ll;
const ll inf = 1e18;
const int maxn = 1e5 + 10;
ll dp[maxn][20];
ll cnt[maxn];
ll a[maxn];
ll cost;
int N , K , L , R;

/*
cost[l , r] increases as r increases
so dp optimization using DAC (prove later , no time now)
cost[i] = cost of putting a[1 .. i] into same group
cost[i] = cost[i - 1] + cnt[a[i]]++
cost[i - 1] = cost[i] - --cnt[a[i]]
thus we can use 2 pointers to calculate cost efficiently
plus , for each layer , we move at most O(n) , thus ,
time complexity = O(nklogn) about 10 ^ 7
*/

void query(int l , int r){ // invariant l <= r
  while(L < l){ //pop out
    --cnt[a[L]];
    cost -= cnt[a[L]];
    ++L;
  }
  while(L > l){ //push in
    --L;
    cost += cnt[a[L]];
    ++cnt[a[L]];
  }
  while(R < r){ //push in
    ++R;
    cost += cnt[a[R]];
    ++cnt[a[R]];
  }
  while(R > r){ //pop out
    --cnt[a[R]];
    cost -= cnt[a[R]];
    --R;
  }
}

void solve(int l , int r , int x , int y , int k){
  if(l > r)return;
  int mid = (l + r) >> 1;
  int pos = -1;
  dp[mid][k] = inf;
  for(int i = x; i <= min(y , mid); ++i){
    query(i , mid);
    if(cost + dp[i - 1][k - 1] < dp[mid][k]){
      dp[mid][k] = cost + dp[i - 1][k - 1];
      pos = i;
    }
  }
  solve(l , mid - 1 , x , pos , k);
  solve(mid + 1 , r , pos , y , k);
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> K;
  memset(cnt , 0 , sizeof(cnt));
  dp[0][1] = 0;
  cost = 0;
  for(int i = 1; i <= N; ++i){
    cin >> a[i];
    cost += cnt[a[i]]++;
    dp[i][1] = cost;
  }
  L = 1 , R = N;
  for(int i = 2; i <= K; ++i){
    solve(1 , N , 1 , N , i);
  }
  cout << dp[N][K] << endl;
}
