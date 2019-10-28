#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdio>
using namespace std;
typedef long long ll;

/*
  只能交换相邻元素，问最少能多少步将数组排成升序
  = 逆序对个数
  用分治思想计数
*/

const int maxn = 5e5 + 10;
int n;
ll cnt;

void merge(vector<int>& a , int l0 , int r0 , int l1 , int r1){
  int i = l0 , j = l1;
  vector<int> t;
  while(i <= r0 && j <= r1){
    if(a[i] > a[j]){
      cnt += (ll)r0 - i + 1;
      t.push_back(a[j]);
      ++j;
    }
    else{
      t.push_back(a[i]);
      ++i;
    }
  }
  for(; i <= r0; ++i)t.push_back(a[i]);
  for(; j <= r1; ++j)t.push_back(a[j]);
  for(i = l0; i <= r1; ++i)a[i] = t[i - l0];
}

void mergesort(vector<int>& a , int l , int r){
  if(l >= r)return;
  int m = (l + r) >> 1;
  mergesort(a , l , m);
  mergesort(a , m + 1 , r);
  merge(a , l , m , m + 1 , r);
}

int main(){
  while(cin >> n && n){
    vector<int> a(n);
    for(int i = 0; i < n; ++i){
      cin >> a[i];
    }
    cnt = 0ll;
    mergesort(a , 0 , n - 1);
    cout << cnt << endl;
  }
}
