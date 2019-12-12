#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
/*
快速多项式相乘：
两点确定一条直线，于是n个不同的点确定一个n项式
利用原跟，wn在单位圆上n等分划分圆的性质，结合
二分思想，在nlogn时间内将每一个F(wn ^ k)算出，
这个步骤称为DFT。
然后由于A(x) * B(x) = C(x),可以通过点值相乘
反推系数从而解出C，由神奇矩阵发现元素为之前矩阵的
倒数，用与DFT相似的方法即可算出C，这个过程称为IDFT
*/
const double PI = acos(-1.0);

struct Complex{
  double x , y;

  Complex(){}

  Complex(double x_ , double y_){
    x = x_;
    y = y_;
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

void change(Complex Y[] , int len){
  // i and reverse(i  ,  base 2) swap
  for(int i = 1 , j = len / 2; i < len - 1; ++i){
    if(i < j)swap(Y[i] , Y[j]);
    int k = len / 2;
    while(j >= k){
      j -= k;
      k /= 2;
    }
    if(j < k)j += k;
  }
}

void FFT(Complex Y[] , int len , int DFT){
  change(Y , len);
  for(int h = 2; h <= len; h *= 2){
    Complex wn(cos(2 * PI / h) , sin(DFT * 2 * PI / h));
    for(int j = 0; j < len; j += h){
      Complex w(1 , 0);
      for(int k = j; k < j + h / 2; ++k){
        Complex u = Y[k];
        Complex t = w * Y[k + h / 2];
        Y[k] = u + t;
        Y[k + h / 2] = u - t;
        w = w * wn;
      }
    }
  }
  if(DFT == -1){
    for(int i = 0; i <= len; ++i){
      Y[i].x /= len;
    }
  }
}

const int maxn = 1e5 + 10;
string s1 , s2;
Complex X1[maxn << 2] , X2[maxn << 2];
int sum[maxn];

int main(){
  cin >> s1;
  cin >> s2;
  int len1 = s1.size();
  int len2 = s2.size();
  int len = 1;
  while(len < len1 * 2 || len < len2 * 2)len *= 2;
  for(int i = 0; i < len1; ++i)X1[i] = Complex(s1[len1 - 1 - i] - '0' , 0);
  for(int i = len1; i < len; ++i)X1[i] = Complex(0 , 0);
  for(int i = 0; i < len2; ++i)X2[i] = Complex(s2[len2 - 1 - i] - '0' , 0);
  for(int i = len2; i < len; ++i)X2[i] = Complex(0 , 0);
  FFT(X1 , len , 1);
  FFT(X2 , len , 1);
  for(int i = 0; i < len; ++i)X1[i] = X1[i] * X2[i];
  FFT(X1 , len , -1);
  for(int i = 0; i < len; ++i)sum[i] = (int)(X1[i].x + 0.5); //4舍5入
  for(int i = 0; i < len; ++i){
    sum[i + 1] += sum[i] / 10;
    sum[i] %= 10;
  }
  len = len1 + len2 - 1;
  while (sum[len] == 0 && len > 0) len--;
  for (int i = len; i >= 0; i--) cout << sum[i];
  cout << endl;
}
