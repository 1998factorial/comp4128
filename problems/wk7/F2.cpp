#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;
typedef long long ll;

const ll inf = 1e18;
const int maxn = 5e4 + 10;

//O(N * N)

struct rec{
  ll x , y;
}R[maxn];

ll dp[maxn];
int N;

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N;
  for(int i = 1; i <= N; ++i)cin >> R[i].x >> R[i].y;
  sort(R + 1 , R + N + 1 , [](rec a , rec b){
    return a.x < b.x;
  });
  // forcing x[i] <= x[i + 1] and y[i] > y[i + 1]
  vector<rec> gr;
  for(int i = 1; i <= N; ++i){
    while(gr.size() && gr.back().y <= R[i].y)gr.pop_back();
    gr.push_back(R[i]);
  }
  N = gr.size();
  for(int i = 0; i < gr.size(); ++i){
    R[i + 1] = gr[i];
  }
  dp[0] = 0;
  for(int i = 1; i <= N; ++i){
    dp[i] = inf;
    for(int j = 0; j < i; ++j){
      dp[i] = min(dp[i] , dp[j] + R[i].x * R[j + 1].y);
    }
  }
  cout << dp[N] << endl;
  return 0;
}
