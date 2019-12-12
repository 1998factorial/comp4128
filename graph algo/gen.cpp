#include <iostream>
#include <time.h>
using namespace std;

int main(){
  int N = 1e5 , M = 2e5;
  srand(time(NULL));
  cout << N << " " << M << endl;
  for(int i = 1; i <= M; ++i){
    cout << rand() % N + 1 << " " << rand() % N + 1 << " " << rand() % 100000 + 1 << endl;
  }
}
