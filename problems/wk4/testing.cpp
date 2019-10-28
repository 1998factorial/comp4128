#include <iostream>
#include <algorithm>
#include <cstdio>
#include <time.h>
using namespace std;

int main(){
  srand(time(NULL));
  int n = rand() % 10;
  cout << n << endl;
  for(int i = 1; i <= n; ++i){
    int x = rand() % 100 , r = rand() % 100;
    cout << x << " " << r << endl;
  }
}
