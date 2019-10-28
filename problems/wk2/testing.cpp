#include <iostream>
#include <cstdio>
#include <time.h>
using namespace std;
int n , k , T;

int main(){
  srand(time(NULL));
  cin >> T;
  cout << T << endl;
  for(int j = 1; j <= T; ++j){
    cin >> n >> k;
    cout << n << " " << k << endl;
    for(int i = 1; i <= n; ++i){
      cout << rand() % 10 << " " << rand() % 10 << " " << (rand() % k) + 1 << endl;
    }
  }
  return 0;
}
