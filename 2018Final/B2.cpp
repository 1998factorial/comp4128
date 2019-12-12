#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <set>
using namespace std;
typedef pair<int , int> ii;
/*
  x = h , y = w
  smimilar to codeforces - Point 
*/
const int maxn = 2e5 + 10;
const int inf = 2e9 + 10;
int Q , N;
ii rec[maxn];
int qs[maxn][2];
int maxtree[maxn << 2];
set<int> atX[maxn];

void build(int l , int r , int id){
  if(l > r)return;
  if(l == r){
    if(atX[l].size())maxtree[id] = *atX[l].rbegin();
    else maxtree[id] = -1;
  }
  else{
    int m = (l + r) >> 1;
    build(l , m , id << 1);
    build(m + 1 , r , id << 1 | 1);
    maxtree[id] = max(maxtree[id << 1] , maxtree[id << 1 | 1]);
  }
}

void update(int pos , int l , int r , int val , int id , int add){
  if(l > r || pos < l || pos > r)return;
  if(pos == l && pos == r){
    if(add){
      atX[pos].insert(val);
    }
    else{
      atX[pos].erase(val);
    }
    if(atX[pos].size()) maxtree[id] = *atX[pos].rbegin();
    else maxtree[id] = -1;
  }
  else{
    int m = (l + r) >> 1;
    update(pos , l , m , val , id << 1 , add);
    update(pos , m + 1 , r , val , id << 1 | 1 , add);
    maxtree[id] = max(maxtree[id << 1] , maxtree[id << 1 | 1]);
  }
}

int query(int l , int r , int x , int y , int val , int id){ // return the smallest x such that maxtree[x] is at least val
  if(l > r || x > r || y < l || maxtree[id] < val)return inf;
  if(l <= x && y <= r){
    if(x == y)return x;
    else {
      int mid = (x + y) >> 1;
      if(maxtree[id << 1] >= val)return query(l , r , x , mid , val , id << 1); // my left child is at least val
      return query(l , r , mid + 1 , y , val , id << 1 | 1); // check my right
    }
  }
  int mid = (x + y) >> 1;
  if(mid < l)
    return query(l , r , mid + 1 , y , val , id << 1 | 1);
  if(mid >= r)
    return query(l , r , x , mid , val , id << 1);
  return min(query(l , r , x , mid , val , id << 1) , query(l , r , mid + 1 , y , val , id << 1 | 1));
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> Q;
  int tot = 0;
  vector<int> xs;
  unordered_map<int , int> mp , imp; // discrete
  unordered_map<int , unordered_map<int , int>> mapping; // (x , y) -> id
  for(int q = 1; q <= Q; ++q){
    char op; cin >> op;
    if(op == 'D'){
      ++tot;
      cin >> rec[tot].second >> rec[tot].first;
      mapping[rec[tot].first][rec[tot].second] = tot;
      qs[q][0] = 1;
      qs[q][1] = tot;
      xs.push_back(rec[tot].first);
    }
    else if(op == 'P'){
      qs[q][0] = 2;
      cin >> qs[q][1];
    }
  }
  sort(xs.begin() , xs.end());
  N = 1;
  mp[xs[0]] = N; imp[N] = xs[0];
  for(int i = 1; i < xs.size(); ++i){
    if(xs[i] != xs[i - 1])
      ++N , mp[xs[i]] = N , imp[N] = xs[i];
  }
  build(1 , N , 1);
  for(int q = 1; q <= Q; ++q){
    if(qs[q][0] == 1){ // add
      int id = qs[q][1];
      int pos = mp[rec[id].first];
      int val = rec[id].second;
      update(pos , 1 , N , val , 1 , 1);
    }
    else if(qs[q][0] == 2){ // find
      int id = qs[q][1];
      int pos = mp[rec[id].first]; // height after discrete
      int val = rec[id].second; // width
      update(pos , 1 , N , val , 1 , 0);
      int ret = query(pos , N , 1 , N , val , 1);
      if(ret >= inf)cout << "RIP\n";
      else{
        int x = imp[ret];
        int y = *atX[ret].lower_bound(val); // must be at least width
        cout << mapping[x][y] << endl;
      }
      update(pos , 1 , N , val , 1 , 1);
    }
  }
}
