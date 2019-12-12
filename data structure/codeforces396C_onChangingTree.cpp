#include <iostream>
#include <vector>
#include <string.h>
using namespace std;

typedef long long ll;
const ll mod = 1e9 + 7;
const int maxn = 3e5 + 10;
int N , Q;
vector<int> g[maxn];
struct Node{
  ll sum , lazy;
} tree[maxn << 2][2]; //val0 = x + k * level[parent] , val1 = k
int level[maxn];
int dfn[maxn];
int L[maxn];
int tot;

void DFS(int v , int p , int d){
  level[v] = d;
  dfn[v] = tot++;
  for(int u : g[v])
    if(u != p)
      DFS(u , v , d + 1);
  L[dfn[v]] = tot - 1;
}

void push_down(int l , int r , int id , int ver){
  if(l < r && tree[id][ver].lazy){
    tree[id << 1][ver].lazy = (tree[id << 1][ver].lazy + tree[id][ver].lazy) % mod;
    tree[id << 1 | 1][ver].lazy = (tree[id << 1 | 1][ver].lazy + tree[id][ver].lazy) % mod;
    tree[id << 1][ver].sum = (tree[id << 1][ver].sum + tree[id][ver].lazy) % mod;
    tree[id << 1 | 1][ver].sum = (tree[id << 1 | 1][ver].sum + tree[id][ver].lazy) % mod;
    tree[id][ver].lazy = 0;
  }
}

void merge(int l , int r , int id , int ver){
  if(l < r){
    tree[id][ver].sum = (tree[id << 1][ver].sum + tree[id << 1 | 1][ver].sum) % mod;
  }
}

void update(int l , int r , int x , int y , int id , ll val , int ver){
  if(l > r || l > y || r < x)return;
  if(l <= x && y <= r){
    tree[id][ver].sum = (tree[id][ver].sum + val) % mod;
    tree[id][ver].lazy = (tree[id][ver].lazy + val) % mod;
  }
  else{
    int m = (x + y) >> 1;
    push_down(x , y , id , ver);
    update(l , r , x , m , id << 1 , val , ver);
    update(l , r , m + 1 , y , id << 1 | 1 , val , ver);
    merge(x , y , id , ver);
  }
}

ll query(int l , int r , int x , int y , int id , int ver){
  if(l <= x && y <= r){
    return tree[id][ver].sum;
  }
  int m = (x + y) >> 1;
  push_down(x , y , id , ver);
  if(m < l)
    return query(l , r , m + 1 , y , id << 1 | 1 , ver);
  if(m >= r)
    return query(l , r , x , m , id << 1 , ver);
  ll ret = 0;
  ret = (ret + query(l , r , x , m , id << 1 , ver)) % mod;
  ret = (ret + query(l , r , m + 1 , y , id << 1 | 1 , ver)) % mod;
  return ret;
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N;
  for(int i = 2; i <= N; ++i){
    int p; cin >> p;
    g[p].push_back(i);
    g[i].push_back(p);
  }
  tot = 1;
  DFS(1 , 1 , 0);
  cin >> Q;
  memset(tree , 0 , sizeof(tree));
  for(int q = 1; q <= Q; ++q){
    int tp; cin >> tp;
    if(tp == 1){
      ll v , x , k; cin >> v >> x >> k;
      ll val = k * level[v] % mod;
      val = (val + x) % mod;
      update(dfn[v] , L[dfn[v]] , 1 , N , 1 , val , 0);
      update(dfn[v] , L[dfn[v]] , 1 , N , 1 , k , 1);
    }
    if(tp == 2){
      int v; cin >> v;
      ll a1 = query(dfn[v] , dfn[v] , 1 , N , 1 , 0);
      ll a2 = query(dfn[v] , dfn[v] , 1 , N , 1 , 1) * level[v] % mod;
      cout << (a1 - a2 + mod) % mod << endl;
    }
  }
}
