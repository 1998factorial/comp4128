#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;
typedef long long ll;

const ll inf = 1e18;
const int maxn = 5e4 + 10;

//O(N * N * logN)

struct rec{
  ll x , y;
}R[maxn];
ll dp[maxn];
int N;
ll MAX[maxn << 2];

void build(int l , int r , int id){
  MAX[id] = R[l].y;
  if(l == r)return;
  int mid = (l + r) >> 1;
  build(l , mid , id << 1);
  build(mid + 1 , r , id << 1 | 1);
  MAX[id] = max(MAX[id << 1] , MAX[id << 1 | 1]);
}

ll query(int l , int r , int x , int y , int id){
  if(l <= x && y <= r){
    return MAX[id];
  }
  int mid = (x + y) >> 1;
  if(mid < l)
    return query(l , r , mid + 1 , y , id << 1 | 1);
  if(mid >= r)
    return query(l , r , x , mid , id << 1);
  return max(query(l , r , x , mid , id << 1) , query(l , r , mid + 1 , y , id << 1 | 1));
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N;
  for(int i = 1; i <= N; ++i)cin >> R[i].x >> R[i].y;
  sort(R + 1 , R + N + 1 , [](rec a , rec b){
    return a.x < b.x;
  });
  build(1 , N , 1);
  dp[0] = 0;
  for(int i = 1; i <= N; ++i){
    dp[i] = inf;
    for(int j = 0; j < i; ++j){
      ll ym = query(j + 1 , i , 1 , N , 1);
      dp[i] = min(dp[i] , R[i].x * ym + dp[j]);
    }
  }
  cout << dp[N] << endl;
  return 0;
}
