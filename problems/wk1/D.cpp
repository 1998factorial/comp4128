#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

int pos[8];
int a[8];
int ret;
void solve(int col){
  if(col >= 8){
    int sum = 0;
    for(int i = 0; i < 8; ++i){
      sum += (pos[i] != a[i]);
    }
    ret = min(ret , sum);
  }
  else{
    for(int row = 0; row < 8; ++row){
      bool check = true;
      for(int i = 0; i < col && check; ++i){
        if(a[i] == row || abs(a[i] - row) == abs(i - col)){
          check = false;
        }
      }
      if(check){
        a[col] = row;
        solve(col + 1);
      }
    }
  }
}

int main(){
  int c = 1;
  while(cin >> pos[0] >> pos[1] >> pos[2] >> pos[3] >> pos[4] >> pos[5] >> pos[6] >> pos[7]){
    ret = 100;
    for(int i = 0; i < 8; ++i)--pos[i];
    solve(0);
    cout << "Case " << c << ": " << ret << endl;
    ++c;
  }
}
