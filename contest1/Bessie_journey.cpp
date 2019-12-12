#include <iostream>
#include <string.h>
using namespace std;
typedef long long ll;

const int maxn = 3e5 + 10;
struct state{
  ll s , e , cnt , lazy;
  state(){}
  state(ll s_ , ll e_ , ll c_ , ll l_) : s(s_) , e(e_) , cnt(c_) , lazy(l_) {}
}tree[maxn << 2];
int N , Q;
ll H[maxn];

state merge(state a , state b){
  state ret;
  ret.cnt = a.cnt + b.cnt + (a.e < b.s);
  ret.s = a.s;
  ret.e = b.e;
  ret.lazy = 0;
  return ret;
}

void push_down(int l , int r , int id){
  if(l < r && tree[id].lazy){
    tree[id << 1].s += tree[id].lazy;
    tree[id << 1].e += tree[id].lazy;
    tree[id << 1].lazy += tree[id].lazy;
    tree[id << 1 | 1].s += tree[id].lazy;
    tree[id << 1 | 1].e += tree[id].lazy;
    tree[id << 1 | 1].lazy += tree[id].lazy;
    tree[id].lazy = 0;
  }
}

void build(int l , int r , int id){
  if(l > r)return;
  if(l == r){
    tree[id].cnt = 0 , tree[id].s = tree[id].e = H[l] , tree[id].lazy = 0;
  }
  else{
    int m = (l + r) >> 1;
    build(l , m , id << 1);
    build(m + 1 , r , id << 1 | 1);
    tree[id] = merge(tree[id << 1] , tree[id << 1 | 1]);
  }
}

void update(int l , int r , int x , int y , int id , ll val){
  if(l > r || l > y || r < x)return;
  if(l <= x && y <= r){
    tree[id].lazy += val;
    tree[id].s += val;
    tree[id].e += val;
  }
  else{
    int m = (x + y) >> 1;
    push_down(x , y , id);
    update(l , r , x , m , id << 1 , val);
    update(l , r , m + 1 , y , id << 1 | 1 , val);
    tree[id] = merge(tree[id << 1] , tree[id << 1 | 1]);
  }
}

state query(int l , int r , int x , int y , int id){
  if(l <= x && y <= r)
    return tree[id];
  int m = (x + y) >> 1;
  push_down(x , y , id);
  if(m < l)
    return query(l , r , m + 1 , y , id << 1 | 1);
  if(m >= r)
    return query(l , r , x , m , id << 1);
  return merge(query(l , r , x , m , id << 1) , query(l , r , m + 1 , y , id << 1 | 1));
}

void show(int l , int r , int id){
  if(l > r)return;
  printf("tree[%d %d] -> (%lld , %lld , %lld , %lld)\n" , l , r , tree[id].s , tree[id].e , tree[id].cnt , tree[id].lazy);
  if(l == r)return;
  int m = (l + r) >> 1;
  show(l , m , id << 1);
  show(m + 1 , r , id << 1 | 1);
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
    char op; cin >> op;
    if(op == 'U'){
      ll l , r , v; cin >> l >> r >> v;
      update(l , r - 1 , 0 , N - 1 , 1 , v);
    }
    else if(op == 'Q'){
      int l , r; cin >> l >> r;
      state ret = query(l , r - 1 , 0 , N - 1 , 1);
      cout << ret.cnt << endl;
    }
  }
}
