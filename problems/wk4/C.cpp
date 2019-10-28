#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;
const int maxn = 3e5 + 10;
int N , Q;
vector<int> g[maxn];
bool vis[maxn];
ll level[maxn]; //shortest distance from 1
int dfn[maxn]; //dfs order
int idfn[maxn];
int R[maxn]; //subtree order
int cnt; //tot
ll tree1[maxn << 2];
ll tree2[maxn << 2];
ll lazy1[maxn << 2];
ll lazy2[maxn << 2];

/*
  tree1 has x + level[v] * k
  tree2 has
  lazy1 maintain x and k
  lazy2 maintain k
  when query v , x + level[v]*k -
*/

void DFS(int v){ // construct tree -> range mapping
  vis[v] = true;
  dfn[v] = cnt;
  idfn[cnt] = v;
  ++cnt;
  for(int i : g[v])
    if(!vis[i])
      DFS(i);
  R[v] = cnt - 1;
}

void BFS(int src){ // compute shortest distance from 1
  for(int i = 1; i <= N; ++i)
    vis[i] = false;
  queue<int> q;
  q.push(src);
  while(!q.empty()){
    int cur = q.front();
    q.pop();
    if(vis[cur])continue;
    vis[cur] = true;
    for(int i : g[cur]){
      if(!vis[i]){
        q.push(i);
        level[i] = level[cur] + 1;
      }
    }
  }
}

void build(int l , int r , int id){
  if(l > r)return;
  tree1[id] = 0;
  tree2[id] = 0;
  lazy1[id] = 0;
  lazy2[id] = 0;
  if(l == r)return;
  else{
    int m = (l + r) >> 1;
    build(l , m , id << 1);
    build(m + 1 , r , id << 1 | 1);
  }
}

void update1(int l , int r , int x , int y , ll xval , ll k , int id){
  if(l > r || l > y || r < x)return;
  if(l <= x && y <= r){
    ll val = (xval + (k * level[idfn[l]]) % mod ) % mod;
    lazy1[id] = (lazy1[id] + val) % mod; //update tag
    tree1[id] = (tree1[id] + val) % mod; //make sure this is good interval
  }
  else{
    int m = (x + y) >> 1;
    if(x < y && lazy1[id]){
      lazy1[id << 1] = (lazy1[id << 1] + lazy1[id]) % mod;
      lazy1[id << 1 | 1] = (lazy1[id << 1 | 1] + lazy1[id]) % mod;
      tree1[id << 1] = (tree1[id << 1] + lazy1[id]) % mod;
      tree1[id << 1 | 1] = (tree1[id << 1 | 1] + lazy1[id]) % mod;
      lazy1[id] = 0;
    }
    if(l <= m)update1(l , r , x , m , xval , k , id << 1);
    if(r >= m)update1(l , r , m + 1 , y , xval , k , id << 1 | 1);
  }
}

void update2(int l , int r , int x , int y , ll k , int id){
  if(l > r || l > y || r < x)return;
  if(l <= x && y <= r){
    lazy2[id] = (lazy2[id] + k) % mod;
    tree2[id] = (tree2[id] + k) % mod;
  }
  else{
    int m = (x + y) >> 1;
    if(x < y && lazy2[id]){
      lazy2[id << 1] = (lazy2[id << 1] + lazy2[id]) % mod;
      lazy2[id << 1 | 1] = (lazy2[id << 1 | 1] + lazy2[id]) % mod;
      tree2[id << 1] = (tree2[id << 1] + lazy2[id]) % mod;
      tree2[id << 1 | 1] = (tree2[id << 1 | 1] + lazy2[id]) % mod;
      lazy2[id] = 0;
    }
    if(l <= m)update2(l , r , x , m , k , id << 1);
    if(r >= m)update2(l , r , m + 1 , y , k , id << 1 | 1);
  }
}

ll query1(int l , int r , int x , int y , int id){
  if(l > r || l > y || r < x)return 0;
  if(l <= x && y <= r){
    return tree1[id];
  }
    int m = (x + y) >> 1;
    if(x < y && lazy1[id]){
      lazy1[id << 1] = (lazy1[id << 1] + lazy1[id]) % mod;
      lazy1[id << 1 | 1] = (lazy1[id << 1 | 1] + lazy1[id]) % mod;
      tree1[id << 1] = (tree1[id << 1] + lazy1[id]) % mod;
      tree1[id << 1 | 1] = (tree1[id << 1 | 1] + lazy1[id]) % mod;
      lazy1[id] = 0;
    }
    ll ret = 0;
    if(l <= m)ret += query1(l , r , x , m , id << 1);
    if(r >= m)ret += query1(l , r , m + 1 , y , id << 1 | 1);
    return ret;
}

ll query2(int l , int r , int x , int y , int id){
  if(l > r || l > y || r < x)return 0;
  if(l <= x && y <= r){
    return tree2[id] * level[idfn[l]] % mod;
  }
    int m = (x + y) >> 1;
    if(x < y && lazy2[id]){
      lazy2[id << 1] = (lazy2[id << 1] + lazy2[id]) % mod;
      lazy2[id << 1 | 1] = (lazy2[id << 1 | 1] + lazy2[id]) % mod;
      tree2[id << 1] = (tree2[id << 1] + lazy2[id]) % mod;
      tree2[id << 1 | 1] = (tree2[id << 1 | 1] + lazy2[id]) % mod;
      lazy2[id] = 0;
    }
    ll ret = 0;
    if(l <= m)ret += query2(l , r , x , m , id << 1);
    if(r >= m)ret += query2(l , r , m + 1 , y , id << 1 | 1);
    return ret;
}

int main(){
  scanf("%d" , &N);
  for(int i = 1; i <= N; ++i)
    g[i].clear() , level[i] = 1 , vis[i] = false;
  for(int i = 2; i <= N; ++i){
    int x;
    scanf("%d" , &x);
    g[x].push_back(i);
    g[i].push_back(x);
  }
  cnt = 1;
  DFS(1);
  BFS(1);
  build(1 , cnt - 1 , 1);
  scanf("%d" , &Q);
  for(int q = 1; q <= Q; ++q){
    int t;
    scanf("%d" , &t);
    if(t == 1){
      ll v , x , k;
      scanf("%lld %lld %lld" , &v , &x , &k);
      update1(dfn[v] , R[v] , 1 , cnt - 1 , x , k , 1);
      update2(dfn[v] , R[v] , 1 , cnt - 1 , k , 1);
    }
    else{
      int v;
      scanf("%d" , &v);
      ll f1 = query1(dfn[v] , dfn[v] , 1 , cnt - 1 , 1);
      ll f2 = query2(dfn[v] , dfn[v] , 1 , cnt - 1 , 1);
      ll ret = (f1 - f2 + mod ) % mod;
      printf("%lld\n" , ret);
    }
  }
  return 0;
}
