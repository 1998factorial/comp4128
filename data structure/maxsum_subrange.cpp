#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;
/*
Problem Statement:
  Given an array of integers A[N],
  initially all 0, support M operations of the forms:
  Update U i v. Set A[i] = v.
  Query Q i j. Consider the sum of every (contiguous)
  subarray of A[i..j). What’s the maximum of these? Treat
  the empty subarray as having sum 0.
Input Format: First line, 2 integers, N, M. The following
M lines each describe an operation.

5 7
U 0 -2
U 2 -2
U 1 3
Q 0 1
Q 0 100
U 3 3
Q 0 4

0
3
4
foreach node,  it stores ,
the maximal sum starting from its left ,
maximal sum ending at its right ,
its wholes sum ,
and its optimal sum
*/
const int maxn = 1e5 + 10;
int N , Q;
int a[maxn];
struct state{
  ll L , R , sum , best;
} tree[maxn << 2];

state merge(const state& left , const state& right){
  // merge [l , m] and [m + 1 , r] into [l , r]
  state ret;
  ret.sum = left.sum + right.sum;
  ret.L = max(left.L , left.sum + right.L);
  ret.R = max(right.R , left.R + right.sum);
  ret.best = max(max(left.best , right.sum) , left.R + right.L);
  return ret;
}

void update(int pos , int l , int r , int id , ll val){
  if(pos < l || pos > r)return;
  if(pos == l && pos == r){
    tree[id].sum = val;
    tree[id].L = tree[id].R = tree[id].best = max(0ll , val);
  }
  else{
    int m = (l + r) >> 1;
    if(pos <= m)
      update(pos , l , m , id << 1 , val);
    else
      update(pos , m + 1 , r , id << 1 | 1 , val);
    tree[id] = merge(tree[id << 1] , tree[id << 1 | 1]);
  }
}

state query(int l , int r , int x , int y , int id){
  if(l <= x && y <= r){
    return tree[id];
  }
  int m = (x + y) >> 1;
  if(m >= r)
    return query(l , r , x , m , id << 1);
  if(m < l)
    return query(l , r , m + 1 , y , id << 1 | 1);
  state ret = merge(query(l , r , x , m , id << 1) , query(l , r , m + 1 , y , id << 1 | 1));
  return ret;
}

void print(int l , int r , int id){
  if(l > r)return;
  printf("(%d %d) -> %lld , %lld , %lld , %lld\n" , l , r , tree[id].L , tree[id].R , tree[id].sum , tree[id].best);
  if(l == r)return;
  int m = (l + r) >> 1;
  print(l , m , id << 1);
  print(m + 1 , r , id << 1 | 1);
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> Q;
  memset(tree , 0 , sizeof(tree));
  for(int q = 1; q <= Q; ++q){
    char op; cin >> op;
    if(op == 'U'){
      int pos , val;
      cin >> pos >> val;
      update(pos , 0 , N - 1 , 1 , val);
    }
    if(op == 'Q'){
      int l , r;
      cin >> l >> r;
      state ret = query(max(l , 0) , min(r - 1 , N - 1) , 0 , N - 1 , 1);
      cout << ret.best << endl;
    }
  }
}
