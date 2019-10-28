#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;
typedef long long ll;

const int maxn = 2e5 + 10;
const ll mod = 1e9 + 7;
vector<ll> val[maxn];
int N;
ll ret;
ll p[maxn]; //power of 2s
/*

sort A st

A1 <= ... <= AN
B1 <= ... <= B1

for i = 1 ... N:
  calculate the contributions Ai is in

(Ai , Bi) must be included , so the Bs that will be in the unordered pair
must be at least Bi

for (Ai , Bi) , the contribution will be Ai * Bi * 2 ^ (# Bk , 1 <= k < i , st Bk <= Bi)
for (Ai , Bk) , Bk > Bi , the contribution will be Ai * Bk * 2 ^ (# Bj , 1 <= j < i , st Bj <= Bk)

store number of elements in 1 .. i - 1 not greater than Bi
if Bj = Bi : Ai * Bj * 2 ^ (#Bk , st , Bk <= Bj)
if Bj > Bi : Ai * Bj * (2 ^ (#Bk , st , Bk <= Bj) - 1)
-1 for the case when we do not select any of them including Bj itself

example :
1 2 3 4
4 4 3 5

S1 = 4
S2 = 4 * 2 = 8
S3 = 3 + 4 * (2 ^ 2 - 1) = 3 + 4 * 3 = 15
S4 = 5 * 2 ^ 3 = 40

tot = 4 + 16 + 45 + 160 = 225

*/


int main(){
  int T;
  scanf("%d" , &T);
  p[0] = 1;
  for(int i = 1; i < maxn; ++i){
    p[i] = p[i - 1] * 2ll % mod;
  }
  for(int t = 1; t <= T; ++t){
    scanf("%d" , &N);
    for(int i = 0; i < N; ++i)val[i].clear();
    for(int i = 0; i < N; ++i){
      ll x;
      scanf("%lld" , &x);
      val[i].push_back(x);
    }
    for(int i = 0; i < N; ++i){
      ll x;
      scanf("%lld" , &x);
      val[i].push_back(x);
    }
    ret = 0;
    sort(val , val + N , [](vector<ll> x , vector<ll> y){
      return x[0] < y[0];
    });
    /*for(int i = 0; i < N; ++i){
      cout << val[i][0] << " ";
    }
    cout << endl;
    for(int i = 0; i < N; ++i){
      cout << val[i][1] << " ";
    }
    cout << endl;*/
    map<ll , ll> cnt;
    for(int i = 0; i < N; ++i){
      int c = 0;
      ll sum = 0;
      for(auto& j : cnt){ // find B[0 , i - 1] <= val[i][1]
        if(j.first <= val[i][1]){
          c += j.second;
        }
      }
      sum = (sum + val[i][1] * p[c] % mod) % mod;
      for(auto& i1 : cnt){
        int c1 = 0 , c2 = 0;
        if(i1.first <= val[i][1])continue;
        for(auto& i2 : cnt){
          if(i1.first >= i2.first){
            c1 += i2.second;
          }
          if(i1.first > i2.first){
            c2 += i2.second;
          }
        }
        sum = (sum + i1.first * (p[c1] - p[c2]) % mod);
      }
      ++cnt[val[i][1]];
      //cout << "sum = " << sum << endl;
      ret = (ret + sum * val[i][0] % mod) % mod;
    }
    cout << ret << endl;
  }
  return 0;
}




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
/*
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

ll query(int l , int r , int x , int y , int id , int f){
  if(l > r || r < x || y < l)return 0;
  if(l <= x && y <= r){
    return tree[id][f];
  }
  else{
    int m = (x + y) >> 1;
    //lazy propogate
    if(lazy[id][f] > 1){
      lazy[id << 1][f] = lazy[id << 1][f] * lazy[id][f] % mod;
      lazy[id << 1 | 1][f] = lazy[id << 1 | 1][f] * lazy[id][f] % mod;
      tree[id << 1][f] = lazy[id][0] * tree[id << 1][f] % mod;
      tree[id << 1 | 1][f] = lazy[id][f] * tree[id << 1 | 1][f] % mod;
      lazy[id][f] = 1;
    }
    ll ret = 0;
    if(m >= l)ret = (ret + query(l , r , x , m , id << 1 , f)) % mod;
    if(m <= r)ret = (ret + query(l , r , m + 1 , y , id << 1 | 1 , f)) % mod;
    tree[id][f] = (tree[id << 1][f] + tree[id << 1 | 1][f]) % mod;
    return ret;
  }
}

void update(int l , int r , int x , int y , int id , int f){
  if(l > r || r < x || y < l)return;
  if(l <= x && y <= r){
    lazy[id][f] = 2ll * lazy[id][f] % mod;
    tree[id][f] = 2ll * tree[id][f] % mod;
  }
  else{
    int m = (x + y) >> 1;
    //lazy propogate
    if(lazy[id][f] > 1){
      lazy[id << 1][f] = lazy[id << 1][f] * lazy[id][f] % mod;
      lazy[id << 1 | 1][f] = lazy[id << 1 | 1][f] * lazy[id][f] % mod;
      tree[id << 1][f] = lazy[id][f] * tree[id << 1][f] % mod;
      tree[id << 1 | 1][f] = lazy[id][f] * tree[id << 1 | 1][f] % mod;
      lazy[id][f] = 1;
    }
    if(m >= l)update(l , r , x , m , id << 1 , f);
    if(m <= r)update(l , r , m + 1 , y , id << 1 | 1 , f);
    tree[id][f] = (tree[id << 1][f] + tree[id << 1 | 1][f]) % mod;
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
      ll qq = (query(mp[val[id[i]][1]] , cnt , 0 , cnt , 1 , 0) - query(mp[val[id[i]][1]] + 1 , cnt , 0 , cnt , 1 , 1) + mod ) % mod;
      ret = (ret + val[id[i]][0] * qq % mod ) % mod;
      update(mp[val[id[i]][1]] , cnt , 0 , cnt , 1 , 0);
      update(mp[val[id[i]][1]] + 1 , cnt , 0 , cnt , 1 , 1);
    }
    printf("%lld\n" , (ret + mod) % mod);
  }
  return 0;
}
*/
