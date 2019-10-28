#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <deque>
using namespace std;
typedef long long ll;
const ll inf = 1ll << 50;
const int maxn = 2e5 + 10;
string s;
int N , K;
ll dp[maxn];
ll tree[maxn << 2];

//tree[l .. r] = min cost to cover room[l .. r]
//dp[i] = min cost to cover room[1 .. i]

void build(int l , int r , int id){
  if(l > r)return;
  if(l == r){
    tree[id] = inf;
  }
  else{
    int m = (l + r) >> 1;
    build(l , m , id << 1);
    build(m + 1 , r , id << 1 | 1);
    tree[id] = min(tree[id << 1] , tree[id << 1 | 1]);
  }
}

void update(int pos, int x , int y , ll val , int id){
  if(pos < x || pos > y)return;
  if(x == pos && y == pos){
    tree[id] = min(tree[id] , val);
  }
  else{
    int m = (x + y) >> 1;
    if(pos <= m)
      update(pos , x , m , val , id << 1);
    else
      update(pos , m + 1 , y , val , id << 1 | 1);
    tree[id] = min(tree[id << 1] , tree[id << 1 | 1]);
  }
}

ll query(int l , int r , int x , int y , int id){
  if(l > r || x > r || y < l)return inf;
  if(l <= x && y <= r){
    return tree[id];
  }
  int m = (x + y) >> 1;
  ll ret = inf;
  if(m < l)
    return query(l , r , m + 1 , y , id << 1 | 1);
  if(m >= r)
    return query(l , r , x , m , id << 1);
  ret = min(query(l , r , x , m , id << 1) , query(l , r , m + 1 , y , id << 1 | 1));
  return ret;
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> K;
  cin >> s;
  for(int i = 1; i <= N; ++i)dp[i] = inf;
  dp[0] = 0;
  build(0 , N , 1);
  update(0 , 0 , N , 0 , 1);
  for(int i = 1; i <= N; ++i){
    dp[i] = dp[i - 1] + i;
    if(s[i - 1] == '1'){
      int l = max(0 , i - K - 1);
      int r = min(N , i + K);
      ll ret = query(l , N , 0 , N , 1) + i;
      dp[r] = min(dp[r] , ret);
      update(r , 0 , N , dp[r] , 1);
    }
    dp[i] = min(dp[i] , query(i , N , 0 , N , 1));
    update(i , 0 , N , dp[i] , 1);
  }
  cout << dp[N] << endl;
  return 0;
}
