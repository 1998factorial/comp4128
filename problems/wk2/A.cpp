#include <iostream>
#include <cstdio>
using namespace std;
const int maxn = (1 << 17) + 10;
int n , m;
int a[maxn] , tree[maxn << 2];

//线段树板子题

void build(int l , int r , int id , int level){
  if(l > r)return;
  if(l == r)tree[id] = a[l];
  else{
    int m = (l + r) >> 1;
    build(l , m , id << 1 , level - 1);
    build(m + 1 , r , id << 1 | 1 , level - 1);
    if(level & 1){
      tree[id] = tree[id << 1] | tree[id << 1 | 1];
    }
    else{
      tree[id] = tree[id << 1] ^ tree[id << 1 | 1];
    }
  }
}

void update(int l , int r , int pos , int val , int id , int level){
  if(pos < l || pos > r)return;
  if(l == r && l == pos){
    tree[id] = val;
  }
  else{
    int m = (l + r) >> 1;
    update(l , m , pos , val , id << 1 , level - 1);
    update(m + 1 , r , pos , val , id << 1 | 1 , level - 1);
    if(level & 1){
      tree[id] = tree[id << 1] | tree[id << 1 | 1];
    }
    else{
      tree[id] = tree[id << 1] ^ tree[id << 1 | 1];
    }
  }
}

int main(){
  cin >> n >> m;
  for(int i = 1; i <= (1 << n); ++i){
    cin >> a[i];
  }
  build(1 , (1 << n) , 1 , n);
  for(int q = 1; q <= m; ++q){
    int p , b;
    cin >> p >> b;
    update(1 , (1 << n) , p , b , 1 , n);
    cout << tree[1] << endl;
  }
  return 0;
}
