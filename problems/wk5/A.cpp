#include <iostream>
#include <cstdio>
using namespace std;
typedef long long ll;

ll dp[35][2];
int N;

void init(){
  dp[0][0] = 1;
  dp[0][1] = 0;
  dp[1][0] = 0;
  dp[1][1] = 2;
  for(int i = 2; i <= 30; ++i){
    dp[i][0] = dp[i - 1][1] + dp[i - 2][0];
    dp[i][1] = 2ll * dp[i - 1][0] + dp[i - 2][1];
  }
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  init();
  while(cin >> N && N != -1){
    cout << dp[N][0] << endl;
  }
  return 0;
}
