#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
using namespace std;
typedef long long ll;
const int maxn = 3e5 + 10;
ll H[maxn];
struct state{
  ll lazy , left , right , cnt;
}tree[maxn << 2];

int N , Q;

void build(int l , int r , int id){
  if(l > r)return;
  if(l == r){
    tree[id].lazy = tree[id].cnt = 0;
    tree[id].left = tree[id].right = H[l];
  }
  else{
    int m = (l + r) >> 1;
    build(l , m , id << 1);
    build(m + 1 , r , id << 1 | 1);
    tree[id].lazy = 0;
    tree[id].cnt = tree[id << 1].cnt + tree[id << 1 | 1].cnt;
    if(tree[id << 1].right < tree[id << 1 | 1].left)++tree[id].cnt;
    tree[id].left = tree[id << 1].left;
    tree[id].right = tree[id << 1 | 1].right;
  }
}

void propogate(int l , int r , int id){
  if(l < r){
    if(tree[id].lazy != 0){
      tree[id << 1].lazy += tree[id].lazy;
      tree[id << 1 | 1].lazy += tree[id].lazy;
      tree[id << 1].left += tree[id].lazy;
      tree[id << 1].right += tree[id].lazy;
      tree[id << 1 | 1].left += tree[id].lazy;
      tree[id << 1 | 1].right += tree[id].lazy;
      tree[id].lazy = 0;
    }
  }
}

void recal(int l , int r , int id){
  if(l < r){
    tree[id].cnt = tree[id << 1].cnt + tree[id << 1 | 1].cnt;
    tree[id].left = tree[id << 1].left;
    tree[id].right = tree[id << 1 | 1].right;
    if(tree[id << 1].right < tree[id << 1 | 1].left){
      ++tree[id].cnt;
    }
  }
}

void update(int l , int r , int x , int y , int val , int id){
  if(l > r || l > y || r < x)return;
  if(l <= x && y <= r){
    tree[id].lazy += val;
    tree[id].left += val;
    tree[id].right += val;
  }
  else{
    int m = (x + y) >> 1;
    propogate(x , y , id);
    update(l , r , x , m , val , id << 1);
    update(l , r , m + 1 , y , val , id << 1 | 1);
    recal(x , y , id);
  }
}

state query(int l , int r , int x , int y , int id){
  if(l <= x && y <= r){
    return tree[id];
  }
  else{
    int m = (x + y) >> 1;
    propogate(x , y , id);
    if(m < l){
      return query(l , r , m + 1 , y , id << 1 | 1);
    }
    if(m >= r){
      return query(l , r , x , m , id << 1);
    }
    state a = query(l , r , x , m , id << 1);
    state b = query(l , r , m + 1 , y , id << 1 | 1);
    recal(x , y , id);
    state ret;
    ret.left = a.left;
    ret.right = b.right;
    ret.cnt = a.cnt + b.cnt;
    if(a.right < b.left)++ret.cnt;
    return ret;
  }
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> Q;
  for(int i = 0; i < N; ++i){
    cin >> H[i];
  }
  build(0 , N - 1 , 1);
  for(int q = 1; q <= Q; ++q){
    string op;
    cin >> op;
    if(op == "U"){
      ll l , r , v;
      cin >> l >> r >> v;
      update(l , r - 1 , 0 , N - 1 , v , 1);
    }
    if(op == "Q"){
      ll l , r;
      cin >> l >> r;
      state ret = query(l , r - 1 , 0 , N - 1 , 1);
      cout << ret.cnt << endl;
    }
  }
  return 0;
}
