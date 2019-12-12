#include <iostream>
#include <vector>
#include <string.h>
using namespace std;

const int maxn = 1e5 + 10;
vector<int> g[maxn];
vector<int> qs[maxn];
int N , M;
int ans[maxn];
int dfn[maxn];
int R[maxn];
int tot;
struct Node{
  int sum , lazy;
} tree[maxn << 2];


void DFS1(int v , int p){
  dfn[v] = tot++;
  for(int u : g[v])
    if(u != p)
      DFS1(u , v);
  R[dfn[v]] = tot - 1;
}

void update(int l , int r , int x , int y , int id , int val){
  if(x > y || l > r || l > y || r < x)return;
  if(l <= x && y <= r){
    tree[id].lazy += val;
    if(tree[id].lazy){
      tree[id].sum = y - x + 1;
    }
    else{
      if(x == y)tree[id].sum = 0;
      else tree[id].sum = tree[id << 1].sum + tree[id << 1 | 1].sum;
    }
  }
  else{
    int m = (x + y) >> 1;
    update(l , r , x , m , id << 1 , val);
    update(l , r , m + 1 , y , id << 1 | 1 , val);
    if(tree[id].lazy){
      tree[id].sum = y - x + 1;
    }
    else{
      if(x == y)tree[id].sum = 0;
      else tree[id].sum = tree[id << 1].sum + tree[id << 1 | 1].sum;
    }
  }
}

void DFS2(int v , int p){
  for(int u : qs[v]){
    update(dfn[u] , R[dfn[u]] , 1 , N , 1 , 1); // cover
  }
  ans[v] = tree[1].sum;
  for(int u : g[v])
    if(u != p)
      DFS2(u , v);
  for(int u : qs[v]){
    update(dfn[u] , R[dfn[u]] , 1 , N , 1 , -1);
  }
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> M;
  for(int i = 1; i <= N - 1; ++i){
    int x , y; cin >> x >> y;
    g[x].push_back(y);
    g[y].push_back(x);
  }
  for(int i = 1; i <= M; ++i){
    int x , y; cin >> x >> y;
    qs[x].push_back(y);
    qs[x].push_back(x);
    qs[y].push_back(x);
    qs[y].push_back(y);
  }
  tot = 1;
  memset(tree , 0 , sizeof(tree));
  DFS1(1 , 1);
  DFS2(1 , 1);
  for(int i = 1; i <= N; ++i){
    if(ans[i])cout << ans[i] - 1 << " ";
    else cout << ans[i] << " ";
  }
  cout << endl;
}
