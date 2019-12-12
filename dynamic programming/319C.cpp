#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

const ll inf = 1e18;
const int maxn = 1e5 + 10;
int a[maxn] , b[maxn];
int N;
ll dp[maxn];

struct line{
  ll m , b;
  line(){}
  line(ll m_ , ll b_) : m(m_) , b(b_) {}
};

double intersect(line a , line b){
  return (double)(b.b - a.b) / (a.m - b.m);
}
vector<line> cht;

void add(line l){
  int n = cht.size();
  while(n > 1 && intersect(cht[n - 1] , cht[n - 2]) >= intersect(cht[n - 1] , l)){
    cht.pop_back();
    n = cht.size();
  }
  cht.push_back(l);
}

ll query(ll x){
  int l = 0 , r = cht.size() - 2 , best = cht.size() - 1;
  //find largest best such that x <= intersect(cht[best] , cht[best + 1])
  while(l <= r){
    int mid = (l + r) >> 1;
    if(x <= intersect(cht[mid] , cht[mid + 1])){
      best = mid;
      r = mid - 1;
    }
    else{
      l = mid + 1;
    }
  }
  return cht[best].m * x + cht[best].b;
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N;
  for(int i = 1; i <= N; ++i)cin >> a[i];
  for(int i = 1; i <= N; ++i)cin >> b[i];
  dp[1] = 0;
  line l0;
  l0.m = a[N];
  l0.b = 0;
  add(l0);
  for(int i = 2; i <= N; ++i){
    dp[i] = query((ll)b[N - i + 1]);
    line l;
    l.m = (ll)a[N - i + 1];
    l.b = dp[i];
    add(l);
  }
  cout << dp[N] << endl;
}
