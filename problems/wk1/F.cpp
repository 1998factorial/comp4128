#include <iostream>
using namespace std;
typedef long long ll;
int C[1005] , n;
int main(){
  int T;
  cin >> T;
  for(int c = 1; c <= T; ++c){
    cin >> n;
    for(int i = 1; i <= n; ++i)cin >> C[i];
    ll S = C[1];
    int ret = 2;
    for(int i = 2; i < n; ++i){
      if(S + C[i] < C[i + 1]){
        S += C[i];
        ++ret;
      }
    }
    cout << ret << endl;
  }
}
