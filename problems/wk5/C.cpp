#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <deque>
using namespace std;
typedef long long ll;

const ll inf = 1ll << 40;
const int maxn = 4e5 + 20;
string s;
int N , K;
ll dp[maxn];

/*
  dp[i] = min(dp[i - 1] + i , dp[j] + (i - K) where i - 2K <= j < i - K)
  we can use a monotonic stack to maintain the good min values
*/

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> K;
  cin >> s;
  dp[0] = 0;
  deque<int> q;
  q.push_back(0);
  for(int i = 1; i <= N + K; ++i){
    dp[i] = dp[i - 1] + i;
    if(i - K - 1 >= 0 && s[i - K - 1] == '1'){
      while(q.size() && q.front() < i - 2 * K - 1)q.pop_front();
      if(q.size())dp[i] = min(dp[i] , dp[q.front()] + i - K);
    }
    while(q.size() && dp[q.back()] > dp[i])q.pop_back();
    q.push_back(i);
  }
  ll ret = inf;
  for(int i = N; i <= N + K; ++i){
    ret = min(ret , dp[i]);
  }
  cout << ret << endl;
  return 0;
}
