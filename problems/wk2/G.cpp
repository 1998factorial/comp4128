#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <unordered_map>
#include <set>
using namespace std;

const int maxn = 2e5 + 10;
int N , K , T;
int tree[maxn << 2];
set<int> S[maxn];

/*
用线段树维护xl到xr，当前高度进行到y时的所有珠宝数量
将xi离散化，按照y排序，枚举不使用的颜色
*/

void update(int l , int r , int pos , int id){
  if(l > r || pos < l || pos > r)return;
  if(l == r && l == pos){
    ++tree[id];
  }
  else{
    int m = (l + r) >> 1;
    update(l , m , pos , id << 1);
    update(m + 1 , r , pos , id << 1 | 1);
    tree[id] = tree[id << 1] + tree[id << 1 | 1];
  }
}

int query(int l , int r , int x , int y , int id){
  if(l > r || y < l || x > r)return 0;
  if(x >= l && y <= r){
    return tree[id];
  }
  int m = (x + y) >> 1;
  int ret = 0;
  ret += query(l , r , x , m , id << 1);
  ret += query(l , r , m + 1 , y , id << 1 | 1);
  return ret;
}

int main(){
  cin >> T;
  for(int q = 1; q <= T; ++q){
    cin >> N >> K;
    vector<int> X(N);
    vector<vector<int>> points(N , vector<int>(3));
    for(int i = 0; i < N; ++i){
      cin >> points[i][0] >> points[i][1] >> points[i][2];
      X[i] = points[i][0];
    }
    sort(X.begin() , X.end());
    unordered_map<int , int> Xmap;
    int tot = 1;
    Xmap[X[0]] = tot;
    for(int i = 1; i < N; ++i){
      if(X[i] != X[i - 1]){
        ++tot;
        Xmap[X[i]] = tot;
      }
    }
    for(int i = 1; i <= K; ++i){ // ini for each color set
      S[i].clear();
      S[i].insert(0);
      S[i].insert(tot + 1);
    }
    for(int i = 0; i <= (N << 2); ++i){
      tree[i] = 0; //ini tree
    }
    sort(points.begin() , points.end() , [](vector<int> a , vector<int> b){
      if(a[1] == b[1])return a[0] < b[0];
      return a[1] < b[1];
    }); //sort by y then by x
    int ret = 0;
    int i = 0;
    while(i < N){
      int j = i;
      while(j < N && points[j][1] == points[i][1]){ // for all points on the same height level
        int c = points[j][2];
        int y = points[j][1];
        int x = points[j][0];
        auto it = S[c].lower_bound(Xmap[x]); // first not less than x as color c
        int r = *it - 1;
        --it;
        int l = *it + 1;
        int cret = query(l , r , 1 , tot , 1);
        ret = max(ret , cret);
        ++j;
      }
      for(int k = i; k < j; ++k){
        S[points[k][2]].insert(Xmap[points[k][0]]);
        update(1 , tot , Xmap[points[k][0]] , 1);
      }
      i = j;
    }
    for(int i = 1; i <= K; ++i){
      auto pre = S[i].begin();
      auto cur = pre;
      ++cur;
      for(; cur != S[i].end(); ++cur , ++pre){
        int l = *pre + 1;
        int r = *cur - 1;
        int cret = query(l , r , 1 , tot , 1);
        ret = max(ret , cret);
      }
    }
    cout << ret << endl;
  }
  return 0;
}
