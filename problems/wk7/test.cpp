#include <iostream>
#include <algorithm>
#include <time.h>
using namespace std;

int main(){
  srand(time(NULL));
  int N = rand() % 100 + 5;
  cout << N << endl;
  for(int i = 1; i <= N; ++i){
    cout << rand() % 10 + 1 << " " << rand() % 10 + 1 << endl;
  }
}
