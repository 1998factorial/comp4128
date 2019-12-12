#include <iostream>
using namespace std;
typedef long long ll;

const ll mod = 1e9 + 7;
ll N , M;

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
        for(int k = 0; k < n; ++k){
          ll c = A[i][k] * o.A[k][j] % mod;
          ret.A[i][j] = (ret.A[i][j] + c) % mod;
        }
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

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> M;
  if(N < M){
    cout << 1 << endl;
    return 0;
  }
  Matrix a(M);
  a.A[0][0] = a.A[0][M - 1] = 1;
  for(int i = 1; i < M; ++i){
    a.A[i][i - 1] = 1;
  }
  a = a ^ (N - M + 1);
  ll ret = 0;
  for(int i = 0; i < M; ++i){
    ret = (ret + a.A[0][i]) % mod;
  }
  cout << (ret + mod) % mod << endl;
}
