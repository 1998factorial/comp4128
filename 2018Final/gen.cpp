#include <iostream>
#include <time.h>
#include <vector>
using namespace std;

int main(){
  srand(time(NULL));
  int N = 10;
  cout << N << endl;
  int cnt = 0;
  vector<pair<int , int>> vec;
  for(int i = 1; i <= N; ++i){
    for(int j = i + 1; j <= N; ++j){
      if(rand() % 2 == 0)continue;
      ++cnt;
      vec.emplace_back(i , j);
    }
  }
  cout << cnt << endl;
  for(auto it : vec)cout << it.first << " " << it.second << endl;
}
