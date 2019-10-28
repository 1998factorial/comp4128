#include <iostream>
#include <cstdio>
#include <map>
using namespace std;
typedef long long ll;

const int maxn = 2e5 + 10;
const ll mod = 1e9 + 7;
int N;
ll A[maxn];
ll B[maxn];
ll ret;

int main(){
  int T;
  scanf("%d" , &T);
  for(int t = 1; t <= T; ++t){
    scanf("%d" , &N);
    for(int i = 0; i < N; ++i){
      scanf("%lld" , &A[i]);
    }
    for(int i = 0; i < N; ++i){
      scanf("%lld" , &B[i]);
    }
    ret = 0;
    map<int , int> mp[10];
    for(int i = 1; i < (1 << N); ++i){
      ll a = 0 , b = 0;
      for(int j = 0; j < N; ++j){
        if(i & (1 << j)){
          a = max(a , A[j]);
          b = max(b , B[j]);
        }
      }
      mp[a][b]++;
      ret = (ret + (a * b) % mod) % mod;
    }
    printf("%lld\n" , ret);
  }
  return 0;
}
