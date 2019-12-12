#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>
using namespace std;
typedef long long ll;
/*
fenwick tree used for single point update for sums
*/
const int maxn = 2e5 + 10;
int p[maxn];
ll sum[maxn << 2];
ll ans[maxn];
int pos[maxn];
bool vis[maxn];
int N , Q;
struct query{
  int l , r , id;
  query(){}
  query(int l_ , int r_ , int id_):l(l_) , r(r_) , id(id_){}
}qs[maxn];
vector<int> g[maxn];

void preprocess(){
  for(int i = 1; i <= N; ++i){
    for(int j = i; j <= N; j += i){
      g[i].push_back(j);
    }
  }
}

void update(int x){
  while(x <= N){
    sum[x] += 1;
    x += (x & (-x));
  }
}

ll ask(int x){
  ll ret = 0;
  while(x){
    ret += sum[x];
    x -= (x & (-x));
  }
  return ret;
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> Q;
  for(int i = 1; i <= N; ++i)cin >> p[i] , pos[p[i]] = i;
  for(int i = 0; i < Q; ++i){
    cin >> qs[i].l >> qs[i].r;
    qs[i].id = i;
  }
  sort(qs , qs + Q , [&](query& a , query& b){
    return a.r < b.r;
  });
  memset(vis , false , sizeof(vis));
  preprocess();
  memset(sum , 0 , sizeof(sum));
  int i = 1;
  for(int q = 0; q < Q; ++q){
    while(i <= N && i <= qs[q].r){
      vis[p[i]] = true;
      for(int j : g[p[i]]){
        if(vis[j])update(pos[j]);
      }
      ++i;
    }
    ans[qs[q].id] = ask(qs[q].r) - ask(qs[q].l - 1);
  }
  sort(qs , qs + Q , [&](query& a,  query& b){
    return a.l > b.l;
  });
  i = N;
  memset(vis , false , sizeof(vis));
  memset(sum , 0 , sizeof(sum));
  for(int q = 0; q < Q; ++q){
    while(i > 0 && i >= qs[q].l){
      vis[p[i]] = true;
      for(int j : g[p[i]]){
        if(vis[j])update(pos[j]);
      }
      --i;
    }
    ans[qs[q].id] += ask(qs[q].r) - ask(qs[q].l - 1);
    ans[qs[q].id] -= (qs[q].r - qs[q].l + 1);
  }
  for(int j = 0; j < Q; ++j){
    cout << ans[j] << endl;
  }
}
