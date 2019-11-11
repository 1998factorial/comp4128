#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;
//dp[i] = minimal cost to cut the last i trees given that the last ith tree has been cut
//dp[i] = min{dp[j] + a[N - j + 1] * b[N - i + 1]}
//a[N - j + 1] is in decresing order (since we sweep from right ot left) thus , it is gradient
//we are trying to maintain a shape of upper convex hull

struct line{
  ll m , b;
};

double intersect(line x , line y){
  return (double)(y.b - x.b) / (x.m - y.m);
}

const int maxn = 1e5 + 10;
const ll inf = 1e8;
ll a[maxn] , b[maxn];
ll dp[maxn];

vector<line> cht;
int N;

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
  for(int i = 1; i <= N; ++i)cin >> a[i];
  for(int i = 1; i <= N; ++i)cin >> b[i];
  dp[1] = 0;
  line l1;
  l1.m = a[N];
  l1.b = dp[1];
  add(l1);
  for(int i = 2; i <= N; ++i){
    dp[i] = query(b[N - i + 1]);
    line li;
    li.m = a[N - i + 1];
    li.b = dp[i];
    add(li);
  }
  cout << dp[N] << endl;
}
