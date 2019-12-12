#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

const int maxn = 2e4 + 10;
const ll inf = 1e18;
ll dp[maxn][3];
ll F[maxn] , D[maxn];
ll X[maxn];
ll SF[maxn] , SXF[maxn];
int N;
struct line{
  ll m , b;
};

double intersect(line x , line y){
  return (double)(y.b - x.b) / (x.m - y.m);
}

vector<line> cht;

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
    if(intersect(cht[mid] , cht[mid + 1]) >= x)ret = mid , r = mid - 1;
    else l = mid + 1;
  }
  return cht[ret].m * x + cht[ret].b;
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
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
  line l0;
  l0.m = -SF[1];
  l0.b = X[1] * SF[0] + X[1] * F[1];
  add(l0);
  for(int i = 2; i <= N; ++i){
    ll val = query(X[i]) + X[i] * SF[i - 1] + X[i] * F[i] + X[N + 1] * (SF[N] - SF[i]) - SXF[N];
    ret = min(ret , val);
    line li;
    li.m = -SF[i];
    li.b = X[i] * SF[i - 1] + X[i] * F[i];
    add(li);
  }
  cout << ret << endl;
}
