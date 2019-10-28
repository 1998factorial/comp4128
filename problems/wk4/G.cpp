#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <set>
#include <algorithm>
#include <unordered_map>
using namespace std;

const int maxn = 2e5 + 10;
const int inf = 1 << 28;
int Q[maxn][3];
int N;
int cnt;
int tree[maxn << 2];
unordered_map<int , int> mp, imp;
set<int> Y[maxn];

/*
  segment tree maintains the maximal y for a range
  Y[x] has all the ys on this x
*/

void build(int l , int r , int id){
  if(l > r)return ;
  if(l == r){
    if(Y[l].size() == 0)tree[id] = -1;
    else tree[id] = *Y[l].rbegin();
  }
  else{
    int m = (l + r) >> 1;
    build(l , m , id << 1);
    build(m + 1 , r , id << 1 | 1);
    tree[id] = max(tree[id << 1] , tree[id << 1 | 1]);
  }
}

void add(int pos , int val , int l , int r , int id){
  if(l > r)return;
  if(pos == l && l == r){
    tree[id] = max(tree[id] , val);
  }
  else{
    int m = (l + r) >> 1;
    if(pos <= m)add(pos , val , l , m , id << 1);
    else add(pos , val , m + 1 , r , id << 1 | 1);
    tree[id] = max(tree[id << 1] , tree[id << 1 | 1]);
  }
}

int query(int l , int r , int x , int y , int val , int id){
  if(l > r || x > r || y < l)return inf;
  if(tree[id] <= val)return inf;
  if(l <= x && y <= r){
    if(x == y)return x;
    else{
      int m = (x + y) >> 1;
      if(tree[id << 1] > val)return query(l , r , x , m , val , id << 1);
      return query(l , r , m + 1 , y , val , id << 1 | 1);
    }
  }
  else{
    int m = (x + y) >> 1;
    return min(query(l , r , x , m , val , id << 1) , query(l , r , m + 1 , y , val , id << 1 | 1));
  }
}

void fix(int pos , int x , int y , int id){
  if(x > y)return;
  if(pos == x && x == y){
    if(Y[x].size() > 0)tree[id] = *(Y[x].rbegin());
    else tree[id] = -1;
  }
  else{
    int m = (x + y) >> 1;
    if(pos <= m)fix(pos , x , m , id << 1);
    else fix(pos , m + 1 , y , id << 1 | 1);
    tree[id] = max(tree[id << 1] , tree[id << 1 | 1]);
  }
}

int main(){
  scanf("%d", &N);
  vector<int> X;
  for(int i = 1; i <= N; ++i){
    string t;
    cin >> t;
    scanf("%d %d" , &Q[i][0] , &Q[i][1]);
    X.push_back(Q[i][0]);
    if(t == "add"){
      Q[i][2] = 1;
    }
    if(t == "find"){
      Q[i][2] = 2;
    }
    if(t == "remove"){
      Q[i][2] = 3;
    }
  }
  sort(X.begin() , X.end());
  cnt = 1;
  mp[X[0]] = cnt;
  imp[cnt] = X[0];
  for(int i = 1; i < X.size(); ++i){
    if(X[i] != X[i - 1]){
      ++cnt;
      mp[X[i]] = cnt;
      imp[cnt] = X[i];
    }
  }
  build(1 , cnt , 1);
  for(int i = 1; i <= N; ++i){
    int x = mp[Q[i][0]] , y = Q[i][1];
    if(Q[i][2] == 1){ // add
      Y[x].insert(y);
      add(x , y , 1 , cnt , 1);
    }
    if(Q[i][2] == 2){ // find
      int ret = query(x + 1 , cnt , 1 , cnt , y , 1);
      if(ret != inf){
        if(Y[ret].upper_bound(y) != Y[ret].end())
          printf("%d %d\n" , imp[ret] , *Y[ret].upper_bound(y));
        else
          cout << -1 << endl;
      }
      else cout << -1 << endl;
    }
    if(Q[i][2] == 3) { // erase
      Y[x].erase(y);
      fix(x , 1 , cnt , 1);
    }
  }
  return 0;
}
