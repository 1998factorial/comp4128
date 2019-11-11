#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;
typedef long long ll;

const ll inf = 1e18;
const int maxn = 5e4 + 10;

//O(N * logN)
//dp[i] = minimal cost to select the first i rectangles
//sort by x (x[i] <= x[i + 1]), if y[i] <= y[i + 1] , ith rectangle will never be considered , so its not usefull
//use a stack to force y[i] > y[i + 1] , and the problem is very similar to E this week

struct rec{
  ll x , y;
}R[maxn];

struct line{
  ll m , b;
};

ll dp[maxn];
int N;
vector<line> cht;

double intersect(line x , line y){
  return (double)(y.b - x.b) / (x.m - y.m);
}

void add(line l){
  int n = cht.size();
  while(n >= 2 && intersect(cht[n - 1] , cht[n - 2]) >= intersect(cht[n - 1] , l)){
    cht.pop_back();
    --n;
  }
  cht.push_back(l);
}

ll query(ll x){
  int l = 0 , r = cht.size() - 2;
  int ret = cht.size() - 1;
  while(l <= r){
    int mid = (l + r) >> 1;
    if(intersect(cht[mid] , cht[mid + 1]) >= x)
      ret = mid , r = mid - 1;
    else
      l = mid + 1;
  }
  return cht[ret].m * x + cht[ret].b;
}

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
  dp[1] = R[1].x * R[1].y;
  line l0;
  l0.m = R[1].y;
  l0.b = 0;
  add(l0);
  for(int i = 2; i <= N; ++i){
    dp[i] = R[i].x * R[i].y + dp[i - 1];
    dp[i] = min(dp[i] , query(R[i].x));
    line l1;
    l1.m = R[i].y;
    l1.b = dp[i - 1];
    add(l1);
  }
  cout << dp[N] << endl;
  return 0;
}
