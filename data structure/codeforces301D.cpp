#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>
using namespace std;
typedef long long ll;
/*
segment tree will TLE
*/
const int maxn = 2e5 + 10;
int p[maxn];
ll sum[maxn << 2];
ll ans[maxn];
int pos[maxn];
bool vis[maxn];
int N , Q;
struct query{
  int l , r , id;
  query(){}
  query(int l_ , int r_ , int id_):l(l_) , r(r_) , id(id_){}
}qs[maxn];
vector<int> g[maxn];

void preprocess(){
  for(int i = 1; i <= N; ++i){
    for(int j = i; j <= N; j += i){
      g[i].push_back(j);
    }
  }
}

void update(int x , int l , int r , int id , int val){
  if(x < l || x > r)return;
  if(x == l && r == x){
    sum[id] += val;
  }
  else{
    int m = (l + r) >> 1;
    if(x <= m)
      update(x , l , m , id << 1 , val);
    else
      update(x , m + 1 , r , id << 1 | 1 , val);
    sum[id] = sum[id << 1] + sum[id << 1 | 1];
  }
}

ll ask(int l , int r , int x , int y , int id){
  if(l <= x && y <= r){
    return sum[id];
  }
  int m = (x + y) >> 1;
  if(m < l)
    return ask(l , r , m + 1 , y , id << 1 | 1);
  if(m >= r)
    return ask(l , r , x , m , id << 1);
  return ask(l , r , m + 1 , y , id << 1 | 1) + ask(l , r , x , m , id << 1);
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> Q;
  for(int i = 1; i <= N; ++i)cin >> p[i] , pos[p[i]] = i;
  for(int i = 0; i < Q; ++i){
    cin >> qs[i].l >> qs[i].r;
    qs[i].id = i;
  }
  sort(qs , qs + Q , [&](query& a , query& b){
    return a.r < b.r;
  });
  memset(vis , false , sizeof(vis));
  preprocess();
  memset(sum , 0 , sizeof(sum));
  int i = 1;
  for(int q = 0; q < Q; ++q){
    while(i <= N && i <= qs[q].r){
      vis[p[i]] = true;
      for(int j : g[p[i]]){
        if(vis[j])update(pos[j] , 1 , N , 1 , 1);
      }
      ++i;
    }
    ans[qs[q].id] = ask(qs[q].l , qs[q].r , 1 , N , 1);
  }
  sort(qs , qs + Q , [&](query& a,  query& b){
    return a.l > b.l;
  });
  i = N;
  memset(vis , false , sizeof(vis));
  memset(sum , 0 , sizeof(sum));
  for(int q = 0; q < Q; ++q){
    while(i > 0 && i >= qs[q].l){
      vis[p[i]] = true;
      for(int j : g[p[i]]){
        if(vis[j])update(pos[j] , 1 , N , 1 , 1);
      }
      --i;
    }
    ans[qs[q].id] += ask(qs[q].l , qs[q].r , 1 , N , 1);
    ans[qs[q].id] -= (qs[q].r - qs[q].l + 1);
  }
  for(int j = 0; j < Q; ++j){
    cout << ans[j] << endl;
  }
}
