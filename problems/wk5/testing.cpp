#include <iostream>
#include <time.h>
#include <algorithm>
#include <cstdio>
using namespace std;

int main(){
  srand(time(NULL));
  int N = 10;
  int K = 4;
  cout << N << " " << K << endl;
  for(int i = 1; i <= N; ++i){
    cout << rand() % 100 + 1 << " ";
  }
  cout << endl;
  return 0;
}
