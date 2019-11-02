#include <iostream>
#include <time.h>
#include <set>
#include <vector>
using namespace std;

int main(){
  srand(time(NULL));
  int N = 10 , M = 1000;
  vector<pair<int , int>> v;
  int cnt = 0;
  for(int i = 1; i <= N; ++i){
    for(int j = i + 1; j <= N; ++j){
      if(rand() % 4 == 0 && M){
        v.push_back(make_pair(i , j));
        --M;
        ++cnt;
      }
    }
  }
  cout << N << " " << cnt << endl;
  for(auto& it : v){
    cout << it.first << " " << it.second << endl;
  }

}
