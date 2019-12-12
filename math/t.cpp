#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;

int a[100];
int N;

void print(int s){
  for(int i = log2(a[N - 1]); i >= 0; --i){
    if(s & (1 << i))cout << 1;
    else cout << 0;
  }
  cout << " ";
}

void change(int len){
  int up = log2(N - 1);
  for(int i = 1; i < len - 1; ++i){
    int j = 0;
    for(int x = 0; x <= up; ++x){
      if(i & (1 << x))j |= (1 << (up - x));
    }
    if(i < j){
      print(i) , print(j);
      cout << endl;
      swap(a[i] , a[j]);
    }
  }
}

int main(){
  N = 16;
  for(int i = 0; i < N; ++i)a[i] = i;
  change(N);
  for(int i = 0; i < N; ++i)cout << a[i] << " ";
  cout << endl;
}
