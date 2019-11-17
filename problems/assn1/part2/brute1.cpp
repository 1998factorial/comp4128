#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int maxn = 1e5 + 10;
int a[maxn];
vector<pair<int , int>> qs;
int N , Q;

int find(int x){
  return a[x] == x ? x : a[x] = find(a[x]);
}

void add(int x , int y){
  x = find(x);
  y = find(y);
  if(x != y){
    if(x > y)swap(x , y);
    a[x] = y;
  }
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> Q;
  qs.clear();
  for(int i = 1; i <= N; ++i)a[i] = i;
  for(int q = 1; q <= Q; ++q){
    char op;
    cin >> op;
    if(op == 'U'){ //add connection
      int x , y;
      cin >> x >> y;
      add(x , y);
      qs.push_back(make_pair(x , y));
    }
    else if(op == 'D'){ //delete most recent connection
      qs.pop_back();
      for(int i = 1; i <= N; ++i)a[i] = i;
      for(auto& it : qs){
        add(it.first , it.second);
      }
    }
    else if(op == 'Q'){ //query
      int x , y;
      cin >> x >> y;
      if(find(x) == find(y))cout << "YES\n";
      else cout << "NO\n";
    }
  }

}
