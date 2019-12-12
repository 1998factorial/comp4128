#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <algorithm>
using namespace std;
typedef pair<int , int> ii;
const int maxn = 2e5 + 10;
const int inf = 2e9 + 10;
set<int> X[maxn];
int tree[maxn << 2];
int E;
int qs[maxn][2]; // y , x
int N;

struct point{
  int x , y , id;
  point(){}
  point(int x_ , int y_ , int id_) : x(x_) , y(y_) , id(id_) {}
}ps[maxn];

void build(int l , int r , int id){
  if(l > r)return;
  if(l == r){
    if(X[l].size() == 0)tree[id] = -1;
    else tree[id] = *X[l].rbegin();
  }
  else{
    int m = (l + r) >> 1;
    build(l , m , id << 1);
    build(m + 1 , r , id << 1 | 1);
    tree[id] = max(tree[id << 1] , tree[id << 1 | 1]);
  }
}

void add(int pos , int l , int r , int val , int id){
  if(l > r || pos < l || pos > r)return;
  if(l == pos && pos == r){
    tree[id] = max(val , tree[id]);
  }
  else{
    int m = (l + r) >> 1;
    if(pos <= m) add(pos , l , m , val , id << 1);
    else add(pos , m + 1 , r , val , id << 1 | 1);
    tree[id] = max(tree[id << 1] , tree[id << 1 | 1]);
  }
}

int query(int l , int r , int x , int y , int val , int id){
  if(l > r || x > r || y < l)return inf;
  if(tree[id] < val)return inf;
  if(l <= x && y <= r){
    if(x == y)return x;
    else{
      int m = (x + y) >> 1;
      if(tree[id << 1] >= val)return query(l , r , x , m , val , id << 1);
      return query(l , r , m + 1 , y , val , id << 1 | 1);
    }
  }
  int m = (x + y) >> 1;
  if(m >= r)
    return query(l , r , x , m , val , id << 1);
  if(m < l)
    return query(l , r , m + 1 , y , val , id << 1 | 1);
  int id1 = query(l , r , x , m , val , id << 1);
  int id2 = query(l , r , m + 1 , y , val , id << 1 | 1);
  return min(id1 , id2);
}

void del(int pos , int x , int y , int id){
  if(x > y)return;
  if(pos == x && pos == y){
    if(X[x].size() > 0)tree[id] = *X[x].rbegin();
    else tree[id] = -1;
  }
  else{
    int m = (x + y) >> 1;
    if(pos <= m) del(pos , x , m , id << 1);
    else del(pos , m + 1 , y , id << 1 | 1);
    tree[id] = max(tree[id << 1] , tree[id << 1 | 1]);
  }
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> E;
  unordered_map<int , int> mp , imp;
  unordered_map<int , unordered_map<int , int>> pmp;
  vector<int> xs;
  int cnt = 0;
  for(int i = 1; i <= E; ++i){
    char op; cin >> op;
    if(op == 'D'){
      ++cnt;
      cin >> ps[cnt].y >> ps[cnt].x;
      xs.push_back(ps[cnt].x);
      pmp[ps[cnt].x][ps[cnt].y] = cnt;
      ps[cnt].id = cnt;
      qs[i][1] = 1;
      qs[i][0] = cnt;
    }
    else if(op == 'P'){
      qs[i][1] = 2;
      cin >> qs[i][0];
    }
  }
  sort(xs.begin() , xs.end());
  N = 1;
  mp[xs[0]] = N;
  imp[N] = xs[0];
  for(int i = 1; i < xs.size(); ++i){
    if(xs[i] != xs[i - 1])
      ++N , mp[xs[i]] = N , imp[N] = xs[i];
  }
  build(1 , N , 1);
  cnt = 0;
  for(int i = 1; i <= E; ++i){
    if(qs[i][1] == 1){
      // add
      ++cnt;
      X[ps[cnt].x].insert(ps[cnt].y);
      add(mp[ps[cnt].x] , 1 , N , ps[cnt].y , 1);
    }
    else if(qs[i][1] == 2){
      // find
      int id = qs[i][0];
      X[mp[ps[id].x]].erase(ps[id].y);
      del(mp[ps[id].x , 1 , N , 1);
      int ret = query(mp[ps[id].x] , N , 1 , N , ps[id].y , 1);
      if(ret >= inf)cout << "RIP\n";
      else{
        int yy = *X[ret].lower_bound(ps[id].y);
        int xx = imp[ret];
        cout << pmp[xx][yy] << endl;
      }
      X[mp[ps[id].x]].insert(ps[id].y);
      add(mp[ps[id].x] , 1 , N , ps[id].y , 1);
    }
  }
}
