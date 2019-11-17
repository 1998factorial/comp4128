#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <cstdio>
using namespace std;

const int maxn = 1e5 + 10;
int a[maxn];
struct Node{
  int sum , lson , rson , pre;
  Node():sum(0) , lson(-1) , rson(-1) , pre(-1){}
}tree[maxn * 80];
int root[maxn << 2];
int N , Q , version , tot;
int pre[maxn];
int froot[maxn];

/*
  sweep from left to right, "add" a[i] each iteration into our persistent segment tree
  -> 1 for i
  -> -1 for pre[i]
  -> 0 for pre[pre[i]]

  at the end , we will have N versions of persistent segment tree
  when query [l , r]
  segtree[version r] query l , r
*/

void push_up(int ver){
  tree[ver].sum = tree[tree[ver].lson].sum + tree[tree[ver].rson].sum;
}

int build(int l , int r){
  int cur = tot;
  ++tot;
  tree[cur] = Node();
  if(l == r)return cur;
  int mid = (l + r) >> 1;
  tree[cur].lson = build(l , mid);
  tree[cur].rson = build(mid + 1 , r);
  push_up(cur);
  return cur;
}

int query(int ver , int l , int r , int x , int y){
  if(l <= x && y <= r){
    return tree[ver].sum;
  }
  int mid = (x + y) >> 1;
  if(mid >= r)
    return query(tree[ver].lson , l , r , x , mid);
  if(mid < l)
    return query(tree[ver].rson , l , r , mid + 1 , y);
  return query(tree[ver].lson , l , r , x , mid) + query(tree[ver].rson , l , r , mid + 1 , y);
}

int update(int ver , int pos , int x , int y , int val){
  int cur = tot;
  ++tot;
  tree[cur] = Node();
  tree[cur].pre = ver;
  if(x == pos && pos == y){
    tree[cur].sum = val;
  }
  else{
    int mid = (x + y) >> 1;
    if(mid >= pos){
      tree[cur].lson = update(tree[ver].lson , pos , x , mid , val);
      tree[cur].rson = tree[ver].rson;
    }
    else{
      tree[cur].rson = update(tree[ver].rson , pos , mid + 1 , y , val);
      tree[cur].lson = tree[ver].lson;
    }
    push_up(cur);
  }
  return cur;
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> Q;
  unordered_map<int , int> mp;
  pre[0] = 0;
  for(int i = 1; i <= N; ++i){
    cin >> a[i];
    pre[i] = mp[a[i]];
    mp[a[i]] = i;
  }
  version = tot = 0;
  root[version] = build(1 , N);
  for(int i = 1; i <= N; ++i){
    root[version + 1] = update(root[version] , i , 1 , N , 1);
    ++version;
    froot[i] = version;
    if(pre[i] == 0)continue;
    root[version + 1] = update(root[version] , pre[i] , 1 , N , -1);
    ++version;
    froot[i] = version;
    if(pre[pre[i]] == 0)continue;
    root[version + 1] = update(root[version] , pre[pre[i]] , 1 , N , 0);
    ++version;
    froot[i] = version;
  }
  int last = 0;
  for(int i = 1; i <= Q; ++i){
    int l , r;
    cin >> l >> r;
    l ^= last , r ^= last;
    if(l > r)swap(l , r);
    last = query(root[froot[r]] , l , r , 1 , N);
    cout << last << endl;
  }
}
