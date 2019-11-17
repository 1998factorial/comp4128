#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <unordered_map>
#include <string.h>
#include <vector>
using namespace std;

const int maxn = 1e5 + 10;
int N , Q;
int a[maxn];
int sum[maxn << 2];
int pre[maxn];
int ans[maxn];

struct query{
  int l , r , id;
}qs[maxn];

/*
  offline process query [l , r] , return number of elements that appear only once in a[l , r]
*/

void update(int pos , int l , int r , int val , int id){
  if(l > r || pos > r || pos < l)return;
  if(pos == l && l == r){
    sum[id] = val;
  }
  else{
    int m = (l + r) >> 1;
    update(pos , l , m , val , id << 1);
    update(pos , m + 1 , r , val , id << 1 | 1);
    sum[id] = sum[id << 1] + sum[id << 1 | 1];
  }
}

int query(int l , int r , int x , int y , int id){
  if(l <= x && y <= r){
    return sum[id];
  }
  int m = (x + y) >> 1;
  if(m < l)return query(l , r , m + 1 , y , id << 1 | 1);
  if(m >= r)return query(l , r , x , m , id << 1);
  return query(l , r , m + 1 , y , id << 1 | 1) + query(l , r , x , m , id << 1);
}


int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> Q;
  unordered_map<int , int> mp;
  for(int i = 1; i <= N; ++i){
    cin >> a[i];
    pre[i] = mp[a[i]];
    mp[a[i]] = i;
  }
  for(int i = 1; i <= Q; ++i){
    cin >> qs[i].l >> qs[i].r;
    qs[i].id = i;
  }
  sort(qs + 1 , qs + 1 + Q , [](struct query x , struct query y){
    return x.r < y.r;
  });
  memset(sum , 0 , sizeof(sum));
  int j = 1;
  for(int i = 1; i <= Q; ++i){
    while(j <= N && j <= qs[i].r){
      update(j , 1 , N , 1 , 1);
      update(pre[j] , 1 , N , -1 , 1);
      update(pre[pre[j]] , 1 , N , 0 , 1);
      ++j;
    }
    ans[qs[i].id] = query(qs[i].l , qs[i].r , 1 , N , 1);
  }
  for(int i = 1; i <= Q; ++i){
    cout << ans[i] << endl;
  }
}
