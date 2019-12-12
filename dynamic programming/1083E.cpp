#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

const int maxn = 1e6 + 10;
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

struct rec{
  ll x , y , a;
} R[maxn];

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N;
  for(int i = 1; i <= N; ++i)
    cin >> R[i].x >> R[i].y >> R[i].a;
  sort(R + 1 , R + 1 + N , [&](rec& a , rec& b){
    return a.x < b.x;
  });
  line l0; l0.m = l0.b = 0; add(l0);
  ll ret = 0;
  for(int i = 1; i <= N; ++i){
    dp[i] = query(-R[i].y) - R[i].a + (ll)R[i].x * R[i].y;
    ret = max(ret , dp[i]);
    line l;
    l.m = R[i].x;
    l.b = dp[i];
    add(l);
  }
  cout << ret << endl;
}
