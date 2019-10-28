#include <iostream>
#include <cmath>
using namespace std;
/*
(2 * a[1] + k) * (k + 1) = 2n
*/
int n;
int main(){
  cin >> n;
  int ret = 0;
  for(int k = 0; k <= sqrt(2*(double)n) - 1; ++k){
    if((2 * n) % (k + 1) == 0 && ( (2 * n) / (k + 1) - k ) % 2 == 0)++ret; //, cout << k << endl;
  }
  cout << ret << endl;
}
