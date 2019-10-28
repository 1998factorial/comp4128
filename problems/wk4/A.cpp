#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

const int maxn = 1e5 + 10;
int N , Q;
int cnt[maxn << 2][3]; // [l ..r][0] -> # of numbers mod 3 == 0
int delta[maxn << 2]; // [l .. r] -> incremental amount mod 3

/*
lazy propogation:
the node we are standing at now combine with the lazy tag must be a good interval for
current node only.
the nodes that are higher then me , i don't care about their tags
so when we query/update downwards , we need to propogate down
*/

void recount(int id , int l , int r){
  if(l < r){
    for(int i = 0; i < 3; ++i)
      cnt[id][(i + delta[id]) % 3] = cnt[id << 1][i] + cnt[id << 1 | 1][i];
  }
  else if(l == r){
    for(int i = 0; i < 3; ++i)cnt[id][i] = 0;
    cnt[id][delta[id] % 3] = 1;
  }
}

void update(int l , int r , int x , int y , int id){
  if(l > r || l > y || r < x)return; // out of bound
  if(x >= l && y <= r){ // inclusive interval
    ++delta[id]; // make sure this node corresbonds to good subtree
    recount(id , x , y);
  }
  else{
    int m = (x + y) >> 1;
    //need to propogate down
    delta[id << 1] += delta[id];
    delta[id << 1 | 1] += delta[id];
    recount(id << 1 , x , m);
    recount(id << 1 | 1 , m + 1 , y);
    delta[id] = 0;
    update(l , r , x , m , id << 1);
    update(l , r , m + 1 , y , id << 1 | 1);
    // when come back from children , we make sure that their subtree is good subtree
    recount(id , x , y);
  }
}

int query(int l , int r , int x , int y , int id){
  if(l > r || l > y || r < x)return 0; // out of bound
  if(x >= l && y <= r){ // inclusive interval
    return cnt[id][0];
  }
    int m = (x + y) >> 1;
    delta[id << 1] += delta[id];
    delta[id << 1 | 1] += delta[id];
    recount(id << 1 , x , m);
    recount(id << 1 | 1 , m + 1 , y);
    delta[id] = 0;
    int ret = 0;
    ret += query(l , r , x , m , id << 1);
    ret += query(l , r , m + 1 , y , id << 1 | 1);
    //recount(id , x , y);
    return ret;
}

void print(int l , int r , int id){
  if(l > r)return;
  printf("[%d , %d] -> %d , %d , %d\n" , l , r , cnt[id][0] , cnt[id][1] , cnt[id][2]);
  printf("delta[%d , %d] = %d\n" ,l , r , delta[id]);
  if(l == r)return;
  int m = (l + r) >> 1;
  print(l , m , id << 1);
  print(m + 1 , r , id << 1 | 1);
}

void build(int l , int r , int id){
  if(l > r)return;
  if(l == r)cnt[id][0] = 1 , cnt[id][1] = cnt[id][2] = 0;
  else{
    int m = (l + r) >> 1;
    build(l , m , id << 1);
    build(m + 1 , r , id << 1 | 1);
    for(int i = 0; i < 3; ++i){
      cnt[id][i] = cnt[id << 1][i] + cnt[id << 1 | 1][i];
    }
  }
}

int main(){
  scanf("%d %d" , &N , &Q);
  for(int i = 0; i <= (N << 2); ++i){
    for(int j = 0; j < 3; ++j){
      cnt[i][j] = 0;
    }
    delta[i] = 0;
  }
  build(0 , N - 1 , 1);
  for(int q = 1; q <= Q; ++q){
    int x , l , r;
    scanf("%d %d %d" , &x , &l , &r);
    if(x == 0){
      update(l , r , 0 , N - 1 , 1);
    }
    else{
      printf("%d\n" , query(l , r , 0 , N - 1 , 1));
    }
  }
  return 0;
}
