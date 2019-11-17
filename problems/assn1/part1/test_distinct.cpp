#include <iostream>
#include <time.h>
#include <algorithm>
using namespace std;

int main(){
  srand(time(NULL));
  int N = rand() % 10 + 5;
  int Q = rand() % 10 + 2;
  cout << N << " " << Q << endl;
  for(int i = 1; i <= N; ++i){
    cout << rand() % 10 << " ";
  }
  cout << endl;
  for(int i = 1; i <= Q; ++i){
    int l = rand() % N + 1;
    int r = rand() % N + 1;
    if(l > r)swap(l , r);
    cout << l << " " << r << endl;
  }
}
