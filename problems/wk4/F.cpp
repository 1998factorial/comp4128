#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long ll;

const int maxn = 1e5 + 10;
ll P[maxn];
ll sum[maxn << 2];
ll MAX[maxn << 2];
bool I[maxn << 2];
bool D[maxn << 2];
ll end_point[maxn << 2][2];
int N , M;
ll inf = 1ll << 40;

void build(int l , int r , int id){
  if(l > r)return;
  if(l == r){
    sum[id] = P[l];
    MAX[id] = P[l];
    I[id] = true;
    D[id] = true;
    end_point[id][0] = end_point[id][1] = P[l];
  }
  else{
    int m = (l + r) >> 1;
    build(l , m , id << 1);
    build(m + 1 , r , id << 1 | 1);
    sum[id] = sum[id << 1] + sum[id << 1 | 1];
    MAX[id] = max(MAX[id << 1] , MAX[id << 1 | 1]);
    end_point[id][0] = end_point[id << 1][0];
    end_point[id][1] = end_point[id << 1 | 1][1];
    I[id] = I[id << 1] && I[id << 1 | 1] && (end_point[id << 1][1] <= end_point[id << 1 | 1][0]);
    D[id] = D[id << 1] && D[id << 1 | 1] && (end_point[id << 1][1] >= end_point[id << 1 | 1][0]);
  }
}

ll query_sum(int l , int r , int x , int y , int id){
  if(l > r || x > r || y < l)return 0;
  if(l <= x && y <= r){
    return sum[id];
  }
  ll ret = 0;
  int m = (x + y) >> 1;
  if(l <= m)ret += query_sum(l , r , x , m , id << 1);
  if(r >= m)ret += query_sum(l , r , m + 1 , y , id << 1 | 1);
  return ret;
}

ll query_max(int l , int r , int x , int y , int id){
  if(l > r || x > r || y < l)return -(1ll << 40);
  if(l <= x && y <= r){
    return MAX[id];
  }
  ll ret = -(1ll << 40);
  int m = (x + y) >> 1;
  if(l <= m)ret = max(ret , query_max(l , r , x , m , id << 1));
  if(r >= m)ret = max(ret , query_max(l , r , m + 1 , y , id << 1 | 1));
  return ret;
}

bool query_inc(int l , int r , int x , int y , int id){
  if(l > r || x > r || y < l)return true;
  if(l <= x && y <= r){
    return I[id];
  }
  int m = (x + y) >> 1;
  bool ret = true;
  if(l <= m)ret &= query_inc(l , r , x , m , id << 1);
  if(r >= m)ret &= query_inc(l , r , m + 1 , y , id << 1 | 1);
  //check if both left and right are included
  if(l <= m && m <= r && l <= m + 1 && m + 1 <= r)
    ret &= end_point[id << 1][1] <= end_point[id << 1 | 1][0];
  return ret;
}

bool query_dec(int l , int r , int x , int y , int id){
  if(l > r || x > r || y < l){
    return true;
  }
  if(l <= x && y <= r){
    return D[id];
  }
  int m = (x + y) >> 1;
  bool ret = true;
  if(l <= m)ret &= query_dec(l , r , x , m , id << 1);
  if(r >= m)ret &= query_dec(l , r , m + 1 , y , id << 1 | 1);
  //check if both left and right are included
  if(l <= m && m <= r && l <= m + 1 && m + 1 <= r)
    ret &= end_point[id << 1][1] >= end_point[id << 1 | 1][0];
  return ret;
}

void update(int pos , ll val , int l , int r , int id){
  if(l > r || pos < l || pos > r)return;
  if(l == r){
    sum[id] = val;
    MAX[id] = val;
    end_point[id][0] = end_point[id][1] = val;
  }
  else{
    int m = (l + r) >> 1;
    if(pos >= l)update(pos , val , l , m , id << 1);
    if(pos <= r)update(pos , val , m + 1 , r , id << 1 | 1);
    sum[id] = sum[id << 1] + sum[id << 1 | 1];
    MAX[id] = max(MAX[id << 1] , MAX[id << 1 | 1]);
    end_point[id][0] = end_point[id << 1][0];
    end_point[id][1] = end_point[id << 1 | 1][1];
    I[id] = I[id << 1] && I[id << 1 | 1] && (end_point[id << 1][1] <= end_point[id << 1 | 1][0]);
    D[id] = D[id << 1] && D[id << 1 | 1] && (end_point[id << 1][1] >= end_point[id << 1 | 1][0]);
  }
}

int main(){
  scanf("%d %d" , &N , &M);
  for(int i = 1; i <= N; ++i){
    scanf("%lld" , &P[i]);
  }

  build(1 , N , 1);
  for(int q = 1; q <= M; ++q){
    string t;
    cin >> t;
    int x , y;
    scanf("%d %d" , &x , &y);
    if(t == "U"){
      update(x , y , 1 , N , 1);
    }
    if(t == "M"){
      printf("%lld\n" , query_max(x , y , 1 , N , 1));
    }
    if(t == "S"){
      printf("%lld\n" , query_sum(x , y , 1 , N , 1));
    }
    if(t == "I"){
      if(query_inc(x , y , 1 , N , 1))printf("1\n");
      else printf("0\n");
    }
    if(t == "D"){
      if(query_dec(x , y , 1 , N , 1))printf("1\n");
      else printf("0\n");
    }
  }
  return 0;
}
