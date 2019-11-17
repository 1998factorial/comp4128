#include <iostream>
#include <time.h>
using namespace std;

int main(){
  int N = 1e5;
  int K = 20;
  cout << N << " " << K << endl;
  srand(time(NULL));
  for(int i = 1; i <= N; ++i)
    cout << rand() % (7) + 1 << " ";
  cout << endl;
}
