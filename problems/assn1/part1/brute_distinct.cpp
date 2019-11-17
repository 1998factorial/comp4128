#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <cstdio>
using namespace std;

const int maxn = 1e5 + 10;
int N , Q;
int a[maxn];

int query(int l , int r){
  unordered_map<int , int> cnt;
  for(int i = l; i <= r; ++i){
    cnt[a[i]]++;
  }
  int ret = 0;
  for(auto& it : cnt){
    if(it.second == 1)++ret;
  }
  return ret;
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> Q;
  for(int i = 1; i <= N; ++i){
    cin >> a[i];
  }
  for(int q = 1; q <= Q; ++q){
    int l , r;
    cin >> l >> r;
    cout << query(l , r) << endl;
  }
}
