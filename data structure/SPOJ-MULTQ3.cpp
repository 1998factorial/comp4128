#include <iostream>
#include <string.h>
using namespace std;

const int maxn = 1e5 + 10;
struct Node{
  int cnt[3];
  int lazy;
} tree[maxn << 2];
int N , Q;

void build(int l , int r , int id){
  if(l > r)return;
  if(l == r){
    tree[id].cnt[0] = 1;
  }
  else{
    int m = (l + r) >> 1;
    build(l , m , id << 1);
    build(m + 1 , r , id << 1 | 1);
    for(int i = 0; i < 3; ++i){
      tree[id].cnt[i] = tree[id << 1].cnt[i] + tree[id << 1 | 1].cnt[i];
    }
  }
}

Node merge(const Node& a , const Node& b){
  Node ret;
  ret.lazy = 0;
  for(int i = 0; i < 3; ++i)
    ret.cnt[i] = a.cnt[i] + b.cnt[i];
  return ret;
}

void push_down(int l , int r , int id){
  if(l < r && tree[id].lazy){
    Node ret; // fix left child
    for(int i = 0; i < 3; ++i){
      ret.cnt[i] = tree[id << 1].cnt[(i + tree[id].lazy) % 3];
    }
    ret.lazy = tree[id << 1].lazy + tree[id].lazy;
    tree[id << 1] = ret;
    //fix right child
    for(int i = 0; i < 3; ++i){
      ret.cnt[i] = tree[id << 1 | 1].cnt[(i + tree[id].lazy) % 3];
    }
    ret.lazy = tree[id << 1 | 1].lazy + tree[id].lazy;
    tree[id << 1 | 1] = ret;
    tree[id].lazy = 0;
  }
}

void update(int l , int r , int x , int y , int id){
  if(l > r || l > y || r < x)return;
  if(l <= x && y <= r){
    Node ret;
    for(int i = 0; i < 3; ++i){
      ret.cnt[i] = tree[id].cnt[(i + 1) % 3];
    }
    ret.lazy = tree[id].lazy + 1;
    tree[id] = ret;
  }
  else{
    int m = (x + y) >> 1;
    push_down(x , y , id);
    update(l , r , x , m , id << 1);
    update(l , r , m + 1 , y , id << 1 | 1);
    tree[id] = merge(tree[id << 1] , tree[id << 1 | 1]);
  }
}

Node query(int l , int r , int x , int y , int id){
  if(l <= x && y <= r){
    return tree[id];
  }
  int m = (x + y) >> 1;
  push_down(x , y , id);
  if(m < l)
    return query(l , r , m + 1 , y , id << 1 | 1);
  if(m >= r)
    return query(l , r , x , m , id << 1);
  return merge(query(l , r , x , m , id << 1) , query(l , r , m + 1 , y , id << 1 | 1));
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> Q;
  memset(tree , 0 , sizeof(tree));
  build(0 , N - 1 , 1);
  for(int q = 1; q <= Q; ++q){
    int op; cin >> op;
    if(op == 0){
      int l , r; cin >> l >> r;
      update(l , r , 0 , N - 1 , 1);
    }
    if(op == 1){
      int l , r; cin >> l >> r;
      Node ret = query(l , r , 0 , N - 1 , 1);
      cout << ret.cnt[0] << endl;
    }
  }
}
