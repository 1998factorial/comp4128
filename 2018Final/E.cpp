#include <iostream>
using namespace std;
typedef long long ll;

const int maxn = 2e4 + 10;
const ll inf = 1e18;
ll dp[maxn][3];
ll F[maxn] , D[maxn];
ll X[maxn];
ll SF[maxn] , SXF[maxn];
int N;

ll cal(int j , int i){
  return X[j]*SF[j - 1] + X[j]*F[j] - SF[j]*X[i] + X[i]*SF[i - 1] + X[i]*F[i] + X[N + 1]*(SF[N] - SF[i]) - SXF[N];

}

int main(){
  cin >> N;
  X[1] = 0;
  for(int i = 1; i <= N; ++i){
    cin >> F[i] >> D[i];
    X[i + 1] = X[i] + D[i];
  }
  SF[0] = 0 , SXF[0] = 0;
  for(int i = 1; i <= N; ++i){
    SF[i] = SF[i - 1] + F[i];
    SXF[i] = SXF[i - 1] + F[i] * X[i];
  }
  ll ret = inf;
  for(int i = 1; i <= N; ++i){
    for(int j = 1; j < i; ++j){
      ll val = cal(j , i);
      ret = min(ret , val);
    }
  }
  cout << ret << endl;
}
