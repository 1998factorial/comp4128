#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

const int inf = 1 << 27;
const int maxn = 1e6 + 10;
int N , K;
int a[maxn]; //sequence
int dp[maxn]; //dp[i] = the length of greedy sequence starting with a[i]
vector<int> g[maxn]; //tree
bool vis[maxn];
int dfn[maxn]; //DFS order
int subtree[maxn]; //[dfn[v] , subtree[dfn[v]]] is the range of subtree rooted at v
int tot;
int MAX[maxn << 2];
int lazy[maxn << 2];

/*
  notice that a number can have at most one sucessor so this is a tree structure
  the answer is just the maximal height of the tree in the forest
  then , we draw the whole forest but with all nodes are set to 0
  add the last K elements into the tree , we keep a range tree that stores the maximal of [l , r]
  where l and r are some dfs order bound
  we then sweep from right to left , set the node in tree to -inf with respect to the removing node ,
  subtract its range by 1 , add the new node val into our tree. note that the val we are adding in is
  dp[i] , the length of the greedy sequence starting at a[i]
  overrall complexity O(NlogN)
*/


void show_tree(){
  for(int i = 1; i <= N; ++i){
    cout << i << " : ";
    for(int j : g[i])cout << j << " ";
    cout << endl;
  }
}

void DFS(int v , int p , int dep){
  dp[v] = dep + 1;
  vis[v] = true;
  for(int u : g[v]){
    if(u == p)continue;
    DFS(u , v , dp[v]);
  }
}

void DFS2(int v , int p){
  dfn[v] = tot;
  ++tot;
  for(int u : g[v]){
    if(u == p)continue;
    DFS2(u , v);
  }
  subtree[dfn[v]] = tot - 1;
}

void build(int l , int r , int id){
  if(l > r)return;
  if(l == r){
    MAX[id] = 0;
    lazy[id] = 0;
    return;
  }
  MAX[id] = 0;
  lazy[id] = 0;
  int m = (l + r) >> 1;
  build(l , m , id << 1);
  build(m + 1 , r , id << 1 | 1);
}

void propogate(int l , int r , int id){
  if(l < r){
    // change tag of my child first
    // then change their MAXs , notice that their MAXs are also shifted by lazy[id]
    // lastly , reset my lazy
    lazy[id << 1] += lazy[id];
    lazy[id << 1 | 1] += lazy[id];
    MAX[id << 1] += lazy[id];
    MAX[id << 1 | 1] += lazy[id];
    lazy[id] = 0;
  }
}

void recal(int l , int r , int id){
  if(l < r){
    // range merge up
    MAX[id] = max(MAX[id << 1] , MAX[id << 1 | 1]) + lazy[id];
  }
}

void point(int pos , int l , int r , int val , int id){
  if(pos == l && pos == r){
    MAX[id] = val + lazy[id]; // need to account lazy as well
  }
  else{
    int m = (l + r) >> 1;
    propogate(l , r , id);
    if(pos > m){
      point(pos , m + 1 , r , val , id << 1 | 1);
    }
    else{
      point(pos , l , m , val , id << 1);
    }
    recal(l , r , id);
  }
}

void range(int l , int r , int x , int y , int id){
  if(l > r || y < l || x > r)return;
  if(l <= x && y <= r){
    --lazy[id]; //making sure the range MAX and lazy under my control is correct
    --MAX[id];
  }
  else{
    int m = (x + y) >> 1;
    propogate(x , y , id); //propogate down to my child
    range(l , r , x , m , id << 1);
    range(l , r , m + 1 , y , id << 1 | 1);
    recal(x , y , id);
  }
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> K;
  for(int i = 1; i <= N; ++i)cin >> a[i];
  for(int i = 1; i <= N; ++i)dp[i] = 0 , g[i].clear() , vis[i] = false , dfn[i] = 0;
  vector<int> stack;
  for(int i = 1; i <= N; ++i){ //build tree
    while(stack.size() && a[i] > a[stack.back()]){
      g[i].push_back(stack.back());
      g[stack.back()].push_back(i);
      stack.pop_back();
    }
    stack.push_back(i);
  }
  //show_tree();
  for(int i = N; i >= 1; --i){ //depth
    if(!vis[i]){
      DFS(i , -1 , 0);
    }
  }
  //dfs order
  tot = 1;
  for(int i = N; i >= 1; --i){
    if(dfn[i] == 0){
      DFS2(i , -1);
    }
  }
  build(1 , N , 1);
  for(int i = 0; i < K; ++i){
    int pos = dfn[N - i];
    int val = dp[N - i];
    point(pos , 1 , N , val , 1);
  }
  vector<int> ans;
  ans.push_back(MAX[1]);
  for(int i = N - K; i >= 1; --i){
    int l = dfn[i + K];
    int r = subtree[l];
    int pos = dfn[i];
    int val = dp[i];
    // lazy[l , r] -= 1
    range(l , r , 1 , N , 1);
    // MAX[l , l] = -inf
    point(l , 1 , N , -inf , 1);
    // MAX[pos , pos] = val - x
    point(pos , 1 , N , val , 1);
    // ans[-1] = MAX[1 , N]
    ans.push_back(MAX[1] + lazy[1]);
  }
  reverse(ans.begin() , ans.end());
  for(int i : ans){
    cout << i << " ";
  }
  cout << endl;
  return 0;
}
