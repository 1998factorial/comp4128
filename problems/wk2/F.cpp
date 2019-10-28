#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

const int maxn = 1e5 + 10;
const ll mod = 1e9 + 7;
ll F[maxn];
ll a , b;
ll X[maxn];
ll delta[maxn << 2][2];
int N , Q;

/*
线段树维护区间增量，如何表示数列？
保存前两位即可，状态压缩思想（如何表示数列？）
等比，等差，递推都可以这样表示
若遇到次方，可以用矩阵快速幂
*/

void update(int l , int r , int x , int y , int id){
  if(l > r || y < l || x > r)return; // invaild interval / out of range
  if(x >= l && y <= r){
    if(x < y){ // this interval length is at least 2 so we need to store 2 troynacci number
      delta[id][0] = (delta[id][0] + F[x - l + 1]) % mod;
      delta[id][1] = (delta[id][1] + F[x - l + 2]) % mod;
    }
    else{ // single element interval need only 1
      delta[id][0] = (delta[id][0] + F[x - l + 1]) % mod;
    }
  }
  else{
    int m = (x + y) >> 1;
    update(l , r , x , m , id << 1);
    update(l , r , m + 1 , y , id << 1 | 1);
  }
}

void fix(int l , int r , int id){ // O(nlogn)
  if(l > r)return;
  if(l == r){
    X[l] = (X[l] + delta[id][0]) % mod;
  }
  else{
    if(delta[id][0] || delta[id][1]){
      X[l] = (X[l] + delta[id][0]) % mod;
      X[l + 1] = (X[l + 1] + delta[id][1]) % mod;
      ll cur = ((delta[id][0] * a) % mod + (delta[id][1] * b) % mod) % mod;
      ll pre = delta[id][1];
      for(int i = l + 2; i <= r; ++i){
        X[i] = (X[i] + cur) % mod;
        ll tmp = cur;
        cur = ((cur * b) % mod + (pre * a) % mod) % mod;
        pre = tmp;
      }
    }
    int m = (l + r) >> 1;
    fix(l , m , id << 1);
    fix(m + 1 , r , id << 1 | 1);
  }
}

int main(){
  cin >> N >> Q;
  cin >> F[1] >> F[2];
  cin >> a >> b;
  for(int i = 1; i <= N; ++i){
    cin >> X[i];
  }
  for(int i = 3; i <= N; ++i){ // precompute all F[1 .. N] in O(n)
    F[i] = ((F[i - 2] * a) % mod + (b * F[i - 1]) % mod) % mod;
  }
  for(int i = 0; i <= (N << 2); ++i){ // O(n)
    delta[i][0] = delta[i][1] = 0; // ini
  }
  for(int i = 1; i <= Q; ++i){ // O(qlogn)
    int l , r;
    cin >> l >> r;
    update(l , r , 1 , N , 1);
  }
  fix(1 , N , 1); //O(nlogn)
  for(int i = 1; i <= N; ++i){ // O(n)
    cout << (X[i] + mod) % mod << " ";
  }
  cout << endl;
  return 0;
}
