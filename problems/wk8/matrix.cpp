#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long ll;

struct Matrix{
  static const int maxn = 105;
  ll A[maxn][maxn];
  int n;

  Matrix(int n_): n(n_) {
    for(int i = 0; i < n; ++i)
      for(int j = 0; j < n; ++j)
        A[i][j] = 0;
  }

  Matrix operator * (const Matrix& o) const {
    Matrix ret(n);
    for(int i = 0; i < n; ++i)
      for(int j = 0; j < n; ++j)
        for(int k = 0; k < n; ++k)
          ret.A[i][j] += A[i][k] * o.A[k][j];
    return ret;
  }

  static Matrix identity(int n){
    Matrix ret(n);
    for(int i = 0; i < n; ++i)
      ret.A[i][i] = 1;
    return ret;
  }

  Matrix operator ^ (long long k) const {
    Matrix ret = identity(n);
    Matrix a = *this;
    while(k){
      if(k & 1)ret = ret * a;
      a = a * a;
      k /= 2;
    }
    return ret;
  }

};

int N;

int main(){
  cin >> N;
  Matrix a(N);
  for(int i = 0; i < N; ++i)
    for(int j = 0; j < N; ++j)
      cin >> a.A[i][j];
  Matrix b = a ^ 20;
  for(int i = 0; i < N; ++i){
    for(int j = 0; j < N; ++j){
      cout << b.A[i][j] << " ";
    }
    cout << endl;
  }
}
