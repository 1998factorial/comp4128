//#include <bits/stdc++.h>
#include <iostream>
#include <string.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5 + 10;
int N , Q , tot , version;
int a[maxn];
int root[maxn * 80];

struct Node{
  int sum , lazy;
  int lson , rson , pre;
  Node():sum(0) , lazy(0) , lson(-1) , rson(-1) , pre(-1) {}
}tree[maxn * 100];

int copy(int ver){
  int cur = tot;
  ++tot;
  tree[cur] = Node();
  tree[cur].pre = ver;
  tree[cur].sum = tree[ver].sum;
  tree[cur].lazy = tree[ver].lazy;
  return cur;
}

void push_down(int ver , int l , int r){
  int mid = (l + r) >> 1;
  int lc = tree[ver].lson , rc = tree[ver].rson;
  if(lc == -1 || rc == -1){
    int p = tree[ver].pre;
    lc = tree[ver].lson = copy(tree[p].lson); //tree[ver]'s left son links to tree[p]'s left son's copy
    rc = tree[ver].rson = copy(tree[p].rson);
  }
  tree[lc].lazy = tree[ver].lazy;
  tree[rc].lazy = tree[ver].lazy;
  tree[lc].sum = (mid - l + 1) * tree[ver].lazy;
  tree[rc].sum = (r - mid) * tree[ver].lazy;
  tree[ver].lazy = 0;
}

void push_up(int ver){
  tree[ver].sum = tree[tree[ver].lson].sum + tree[tree[ver].rson].sum;
}

int build(int l , int r){
  int cur = tot;
  ++tot;
  tree[cur] = Node();
  tree[cur].sum = a[l];
  if(l == r)return cur;
  int mid = (l + r) >> 1;
  tree[cur].lson = build(l , mid);
  tree[cur].rson = build(mid + 1 , r);
  push_up(cur);
  return cur;
}

int update(int ver , int l , int r , int x , int y , int val){
  int cur = tot;
  ++tot;
  tree[cur] = Node();
  tree[cur].pre = ver;
  if(l <= x && y <= r){
    tree[cur].lazy = val;
    tree[cur].sum = val * (y - x + 1);
  }
  else{
    int mid = (x + y) >> 1;
    if(tree[ver].lazy)
      push_down(ver , x , y);
    if(mid >= l)
      tree[cur].lson = update(tree[ver].lson , l , r , x , mid , val);
    else
      tree[cur].lson = tree[ver].lson;
    if(mid < r)
      tree[cur].rson = update(tree[ver].rson , l , r , mid + 1 , y , val);
    else
      tree[cur].rson = tree[ver].rson;
    push_up(cur);
  }
  return cur;
}

int query(int ver , int l , int r , int x , int y){
  if(l <= x && y <= r){
    return tree[ver].sum;
  }
  int mid = (x + y) >> 1;
  if(tree[ver].lazy)push_down(ver , x , y);
  if(mid >= r)
    return query(tree[ver].lson , l , r , x , mid);
  if(mid < l)
    return query(tree[ver].rson , l , r , mid + 1 , y);
  return query(tree[ver].lson , l , r , x , mid) + query(tree[ver].rson , l , r , mid + 1 , y);
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> Q;
  tot = version = 0;
  root[version] = build(0 , N - 1);
  for(int i = 0; i < N; ++i)a[i] = 0;
  ll last = 0;
  for(int i = 1; i <= Q; ++i){
    char op;
    cin >> op;
    if(op == 'U'){
      int l , r;
      ll x;
      cin >> l >> r >> x;
      l ^= last;
      r ^= last;
      x ^= last;
      //cout << "update : " << l << " " << r - 1 << " by " << x << endl;
      root[version + 1] = update(root[version] , l , r - 1 , 0 , N - 1 , x);
      ++version;
    }
    else{
      int v , l , r;
      cin >> v >> l >> r;
      l ^= last;
      r ^= last;
      v ^= last;
      //cout << "query : " << l << " " << r - 1 << " at version = " << v << endl;
      last = query(root[v] , l , r - 1 , 0 , N - 1);
      cout << last << endl;
    }
  }
}
