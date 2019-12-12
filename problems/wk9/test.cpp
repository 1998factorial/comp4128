#include <iostream>
#include <time.h>
#include <vector>
using namespace std;

const int mx = 1e6;

bool is(int m){
  bool ret = true;
  for(int i = 2; i * i <= m; ++i)
    if(m % i == 0)ret = false;
  return ret;
}

int main(){
  int T = 10;
  vector<int> p;
  for(int i = 2; i <= 50; ++i)if(is(i))p.push_back(i);
  cout << T << endl;
  srand(time(NULL));
  for(int t = 1; t <= T; ++t){
    int N = rand() % 100;
    int K = rand() % 10 + 1;
    cout << N << " " << K << endl;
    for(int i = K - 1; i >= 0; --i)cout << p[i] << " ";
    cout << endl;
  }
}
