#include <iostream>
#include <algorithm>
#include <time.h>
using namespace std;

int main(){
  srand(time(NULL));
  int N = rand() % 10 + 2;
  int Q = rand() % 10 + 2;
  cout << N << " " << Q << endl;
  int tot = 0;
  for(int i = 1; i <= Q; ++i){
    if(rand() % 2 == 0){
      int l = rand() % N + 1;
      int r = rand() % N + 1;
      int val = rand() % 10;
      if(l > r)swap(l , r);
      cout << "U" << " " << l << " " << r << " " << val << endl;
      ++tot;
    }
    else{
      int l = rand() % N + 1;
      int r = rand() % N + 1;
      if(l > r)swap(l , r);
      int ver = rand() % tot;
      cout << "Q" << " " << ver << " " << l << " " << r << endl; 
    }
  }
}
