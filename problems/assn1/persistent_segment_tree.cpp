#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <string.h>
using namespace std;
typedef long long ll;

const int maxn = 5e5 + 10;
int a[maxn];
int N , Q , tot , version;
int root[maxn]; // root[i] = version i's root

struct Node{
  int sum , lson , rson , lazy , pre;
  Node():sum(0) , lson(-1) , rson(-1) , lazy(0) , pre(-1){}
}tree[maxn << 5];

int copy(int ver){ //create a copy of tree[ver] and it's pre point to ver
  int cur = tot;
  ++tot;
  tree[cur] = Node();
  tree[cur].pre = ver;
  tree[cur].sum = tree[ver].sum;
  tree[cur].lazy = tree[ver].lazy;
  return cur;
}

void push_up(int ver){
  tree[ver].sum = tree[tree[ver].lson].sum + tree[tree[ver].rson].sum;
}

void push_down(int ver , int l , int r){
  int mid = (l + r) >> 1;
  if(tree[ver].lson == -1 || tree[ver].rson == -1){
    int p = tree[ver].pre;
    tree[ver].lson = copy(tree[p].lson);
    tree[ver].rson = copy(tree[p].rson);
  }
  tree[tree[ver].lson].lazy += tree[ver].lazy;
  tree[tree[ver].rson].lazy += tree[ver].lazy;
  tree[tree[ver].lson].sum += (mid - l + 1) * tree[ver].lazy;
  tree[tree[ver].rson].sum += (r - mid) * tree[ver].lazy;
  tree[ver].lazy = 0;
}

int build(int l , int r){
  int cur = tot;
  ++tot;
  tree[cur] = Node();
  tree[cur].sum = a[l];
  if(l == r)return cur;
  int m = (l + r) >> 1;
  tree[cur].lson = build(l , m);
  tree[cur].rson = build(m + 1 , r);
  push_up(cur);
  return cur;
}

int update(int ver , int l , int r , int x , int y , int val){
  int cur = tot;
  ++tot;
  tree[cur] = Node();
  tree[cur].pre = ver;
  if(l <= x && y <= r){
    tree[cur].lazy = tree[ver].lazy + val;
    tree[cur].sum = tree[ver].sum + val * (y - x + 1);
  }
  else{
    int mid = (x + y) >> 1;
    if(tree[ver].lazy)push_down(ver , x , y);
    if(l <= mid) // need to update my left child
      tree[cur].lson = update(tree[ver].lson , l , r , x , mid , val);
    else // no need to update my left child
      tree[cur].lson = tree[ver].lson;
    if(r > mid) // need to update my right child
      tree[cur].rson = update(tree[ver].rson , l , r , mid + 1 , y , val);
    else // no need to care about my right child
      tree[cur].rson = tree[ver].rson;
    push_up(cur); // update value of my current node
  }
  return cur; // return the id of my node
}

int query(int ver , int l , int r , int x , int y){
  if(l <= x && y <= r){
    return tree[ver].sum;
  }
  int mid = (x + y) >> 1;
  if(tree[ver].lazy)push_down(ver , x , y);
  if(l > mid)
    return query(tree[ver].rson , l , r , mid + 1 , y);
  if(r <= mid)
    return query(tree[ver].lson , l , r , x , mid);
  return query(tree[ver].lson , l , r , x , mid) + query(tree[ver].rson , l , r , mid + 1 , r);
}

int main(){
  cin >> N >> Q;
  memset(a , 0 , sizeof(a));
  version = tot = 0;
  root[version] = build(1 , N);
  for(int i = 1; i <= Q; ++i){
    char op;
    cin >> op;
    if(op == 'U'){
      int l , r , x;
      cin >> l >> r >> x;
      root[version + 1] = update(root[version] , l , r , 1 , N , x);
      ++version;
    }
    else{
      int l , r , v;
      cin >> v >> l >> r;
      if(v == 0)cout << 0 << endl;
      else{
        cout << query(root[v] , l , r , 1 , N) << endl;
      }
    }
  }
}
