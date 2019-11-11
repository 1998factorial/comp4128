#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
using namespace std;
typedef long long ll;

/*
  sort x into increasing order , since no 2 rectangles are nested ,
  we know that when sweeping from left to right , y must be decresing
  hence , let dp[i] = maximal cost of choosing rectangles up to ith.
  dp[i] = max{dp[j] - x[j] * y[i]} - a[i] + x[i] * y[i]
  gradient be x[j] , and we query at -y[i]
  gradient increasing , and we are maintaining a shape of lower convex hull
*/

const int maxn = 1e6 + 10;
int N;
struct rec{
  ll x , y , a;
}R[maxn];

struct line{
  ll m , b;
};

double intersect(line x , line y){
  return (double)(y.b - x.b) / (x.m - y.m);
}

vector<line> cht;
ll dp[maxn];

void add(line l){
  int n = cht.size();
  while(n >= 2 && intersect(cht[n - 1] , cht[n - 2]) >= intersect(cht[n - 1] , l)){
    cht.pop_back();
    --n;
  }
  cht.push_back(l);
}

ll query(int x){
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
  for(int i = 1; i <= N; ++i)cin >> R[i].x >> R[i].y >> R[i].a;
  sort(R + 1 , R + 1 + N , [](rec p , rec q){
    return p.x < q.x;
  });
  R[0].x = R[0].y = R[0].a = 0;
  dp[0] = 0;
  line l0;
  l0.m = 0;
  l0.b = 0;
  add(l0);
  ll ret = 0;
  for(int i = 1; i <= N; ++i){
    dp[i] = query(-R[i].y);
    dp[i] -= R[i].a;
    dp[i] += R[i].x * R[i].y;
    ret = max(ret , dp[i]);
    line li;
    li.m = R[i].x;
    li.b = dp[i];
    add(li);
  }
  cout << ret << endl;
}
