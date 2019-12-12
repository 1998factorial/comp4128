#include <iostream>
#include <vector>
using namespace std;

vector<int> g[205];
int N;
int a[205][205];
vector<int> conner;

bool check1(){
  int cnt = 0;
  for(int i = 1; i <= N; ++i)
    if(g[i].size() == 4)
      ++cnt , conner.push_back(i);
  return cnt == 4
}

void solve(){
  a[1][1] = conner[0];
  
}

int main(){
  cin >> N;
  for(int i = 1; i <= N; ++i){
    int t; cin >> t;
    for(int j = 1; j <= t; ++j){
      int p; cin >> p
      g[i].push_back(p);
    }
  }
  if(!check1())cout << -1 << endl;
  else{
    solve();
  }
  return 0;
}
