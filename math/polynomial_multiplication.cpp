#include <cmath>
#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;

const int maxn = 5e5 + 10;
int N , M , len;
int A[maxn] , B[maxn];
int C[maxn];

const double PI = acos(-1.0);
struct Complex {
  double x, y;
  Complex(double _x = 0.0, double _y = 0.0) {
    x = _x;
    y = _y;
  }
  Complex operator-(const Complex &b) const {
    return Complex(x - b.x, y - b.y);
  }
  Complex operator+(const Complex &b) const {
    return Complex(x + b.x, y + b.y);
  }
  Complex operator*(const Complex &b) const {
    return Complex(x * b.x - y * b.y, x * b.y + y * b.x);
  }
};

Complex X1[maxn] , X2[maxn];

void change(Complex Y[] , int len){
  for(int i = 1; i < len - 1; ++i){
    int j = 0 , up = log2(len - 1);
    for(int x = 0; x <= up; ++x){
      if(i & (1 << x))j |= (1 << (up - x));
    }
    if(i < j){
      swap(Y[i] , Y[j]);
    }
  }
}

void FFT(Complex Y[] , int len , int DFT){
  change(Y , len);
  for(int h = 2; h <= len; h *= 2){
    Complex wn = Complex(cos(2 * PI / h) , sin(2 * PI * DFT / h));
    for(int j = 0; j < len; j += h){
      Complex w = Complex(1 , 0);
      for(int k = j; k < j + h / 2; ++k){
        Complex u = Y[k];
        Complex t = Y[k + h / 2] * w;
        Y[k] = u + t;
        Y[k + h / 2] = u - t;
        w = w * wn;
      }
    }
  }
  if(DFT == -1){
    for(int i = 0; i < len; ++i){
      Y[i].x /= len;
    }
  }
}

int main(){
  cin >> N >> M;
  for(int i = 0; i < N; ++i)cin >> A[i];
  for(int i = 0; i < M; ++i)cin >> B[i];
  len = 1;
  while(len < N * 2 || len < M * 2)len *= 2;
  for(int i = 0; i < N; ++i)X1[i] = Complex(A[i] , 0);
  for(int i = N; i < len; ++i)X1[i] = Complex(0 , 0);
  for(int i = 0; i < M; ++i)X2[i] = Complex(B[i] , 0);
  for(int i = M; i < len; ++i)X2[i] = Complex(0 , 0);
  FFT(X1 , len , 1);
  FFT(X2 , len , 1);
  for(int i = 0; i < len; ++i)X1[i] = X1[i] * X2[i];
  FFT(X1 , len , -1);
  for(int i = 0; i < len; ++i)C[i] = (int)(X1[i].x + 0.5);
  for(int i = 0; i < len; ++i){
    printf("C[%d] = %d\n" , i , C[i]);
  }
}
