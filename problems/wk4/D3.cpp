#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <unordered_map>
using namespace std;
typedef long long ll;

const int maxn = 2e5 + 10;
const ll mod = 1e9 + 7;
ll val[maxn][2];
vector<ll> B;
int N;
ll ret;
ll tree[maxn << 2][2];
ll lazy[maxn << 2][2];
//tree[l , r][0] = sum of Bi * 2 ^ (# <= Bi) , l <= i <= r
//tree[l , r][1] = sum of Bi * 2 ^ (# < Bi) , l <= i <= r
unordered_map<ll , int> mp; //point compression
unordered_map<int , ll> imp; //inverse point compression

/*
  Bi * 2 ^ (# <= Bi)
  Bj * (2 ^ (# <= Bj) - 2 ^ (# < Bj))
  need segment tree to main range sum
  when encounter Bi
  query tree[Bi , N][0] - tree[Bi + 1 , N][1]
  update tree[Bi , N][0] , tree[Bi + 1 , N][1] -> those range should be multiplied by 2
*/

void build(int l , int r , int id){
  if(l > r)return;
  if(l == r){
    tree[id][0] = imp[l];
    tree[id][1] = imp[l];
    lazy[id][0] = lazy[id][1] = 1;
  }
  else{
    int m = (l + r) >> 1;
    build(l , m , id << 1);
    build(m + 1 , r , id << 1 | 1);
    for(int i = 0; i < 2; ++i)
      tree[id][i] = (tree[id << 1][i] + tree[id << 1 | 1][i]) % mod;
    lazy[id][0] = lazy[id][1] = 1;
  }
}

ll query1(int l , int r , int x , int y , int id){
  if(l > r || r < x || y < l)return 0;
  if(l <= x && y <= r){
    return tree[id][0];
  }
  else{
    int m = (x + y) >> 1;
    //lazy propogate
    if(lazy[id][0] > 1){
      lazy[id << 1][0] = lazy[id << 1][0] * lazy[id][0] % mod;
      lazy[id << 1 | 1][0] = lazy[id << 1 | 1][0] * lazy[id][0] % mod;
      tree[id << 1][0] = lazy[id][0] * tree[id << 1][0] % mod;
      tree[id << 1 | 1][0] = lazy[id][0] * tree[id << 1 | 1][0] % mod;
      lazy[id][0] = 1;
    }
    ll ret = 0;
    if(m >= l)ret = (ret + query1(l , r , x , m , id << 1)) % mod;
    if(m <= r)ret = (ret + query1(l , r , m + 1 , y , id << 1 | 1)) % mod;
    tree[id][0] = (tree[id << 1][0] + tree[id << 1 | 1][0]) % mod;
    return ret;
  }
}

ll query2(int l , int r , int x , int y , int id){
  if(l > r || r < x || y < l)return 0;
  if(l <= x && y <= r){
    return tree[id][1];
  }
  else{
    int m = (x + y) >> 1;
    //lazy propogate
    if(lazy[id][1] > 1){
      lazy[id << 1][1] = lazy[id << 1][1] * lazy[id][1] % mod;
      lazy[id << 1 | 1][1] = lazy[id << 1 | 1][1] * lazy[id][1] % mod;
      tree[id << 1][1] = lazy[id][1] * tree[id << 1][1] % mod;
      tree[id << 1 | 1][1] = lazy[id][1] * tree[id << 1 | 1][1] % mod;
      lazy[id][1] = 1;
    }
    ll ret = 0;
    if(m >= l)ret = (ret + query2(l , r , x , m , id << 1)) % mod;
    if(m <= r)ret = (ret + query2(l , r , m + 1 , y , id << 1 | 1)) % mod;
    tree[id][1] = (tree[id << 1][1] + tree[id << 1 | 1][1]) % mod;
    return ret;
  }
}

void update1(int l , int r , int x , int y , int id){
  if(l > r || r < x || y < l)return;
  if(l <= x && y <= r){
    lazy[id][0] = 2ll * lazy[id][0] % mod;
    tree[id][0] = 2ll * tree[id][0] % mod;
  }
  else{
    int m = (x + y) >> 1;
    //lazy propogate
    if(lazy[id][0] > 1){
      lazy[id << 1][0] = lazy[id << 1][0] * lazy[id][0] % mod;
      lazy[id << 1 | 1][0] = lazy[id << 1 | 1][0] * lazy[id][0] % mod;
      tree[id << 1][0] = lazy[id][0] * tree[id << 1][0] % mod;
      tree[id << 1 | 1][0] = lazy[id][0] * tree[id << 1 | 1][0] % mod;
      lazy[id][0] = 1;
    }
    if(m >= l)update1(l , r , x , m , id << 1);
    if(m <= r)update1(l , r , m + 1 , y , id << 1 | 1);
    tree[id][0] = (tree[id << 1][0] + tree[id << 1 | 1][0]) % mod;
  }
}

void update2(int l , int r , int x , int y , int id){
  if(l > r || r < x || y < l)return;
  if(l <= x && y <= r){
    lazy[id][1] = 2ll * lazy[id][1] % mod;
    tree[id][1] = 2ll * tree[id][1] % mod;
  }
  else{
    int m = (x + y) >> 1;
    //lazy propogate
    if(lazy[id][1] > 1){
      lazy[id << 1][1] = lazy[id << 1][1] * lazy[id][1] % mod;
      lazy[id << 1 | 1][1] = lazy[id << 1 | 1][1] * lazy[id][1] % mod;
      tree[id << 1][1] = lazy[id][1]* tree[id << 1][1] % mod;
      tree[id << 1 | 1][1] = lazy[id][1] * tree[id << 1 | 1][1] % mod;
      lazy[id][1] = 1;
    }
    if(m >= l)update2(l , r , x , m , id << 1);
    if(m <= r)update2(l , r , m + 1 , y , id << 1 | 1);
    tree[id][1] = (tree[id << 1][1] + tree[id << 1 | 1][1]) % mod;
  }
}

int main(){
  int T;
  scanf("%d" , &T);
  for(int t = 1; t <= T; ++t){
    scanf("%d" , &N);
    vector<int> id;
    for(int i = 0; i < N; ++i)id.push_back(i);
    for(int i = 0; i < N; ++i){
      scanf("%lld" , &val[i][0]);
    }
    for(int i = 0; i < N; ++i){
      scanf("%lld" , &val[i][1]);
    }
    sort(id.begin() , id.end() , [&](int x , int y){
      return val[x][0] < val[y][0];
    });
    B.clear();
    for(int i = 0; i < N; ++i){
      B.push_back(val[id[i]][1]);
    }
    sort(B.begin() , B.end());
    mp.clear();
    imp.clear();
    int cnt = 0;
    mp[B[0]] = cnt;
    imp[cnt] = B[0];
    for(int i = 1; i < N; ++i){
      if(B[i] != B[i - 1]){
        ++cnt;
        mp[B[i]] = cnt;
        imp[cnt] = B[i];
      }
    }
    build(0 , cnt , 1);
    ret = 0;
    for(int i = 0; i < N; ++i){
      ll qq = (query1(mp[val[id[i]][1]] , cnt , 0 , cnt , 1) - query2(mp[val[id[i]][1]] + 1 , cnt , 0 , cnt , 1) + mod ) % mod;
      ret = (ret + val[id[i]][0] * qq % mod ) % mod;
      update1(mp[val[id[i]][1]] , cnt , 0 , cnt , 1);
      update2(mp[val[id[i]][1]] + 1 , cnt , 0 , cnt , 1);
    }
    printf("%lld\n" , (ret + mod) % mod);
  }
  return 0;
}
