#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <string.h>
#include <cstdio>
using namespace std;
/*
  add edge
  delete most recent added edge
  query
  aim : O(QlogN)

  use stack to maintain each node's parent
  can not use path compression , as it will make us to lose track of previous parent
  how to speed up?
  try not to make the size of connected component too large by keeping a size array

  这个版本是错的，拿数组记录size乱搞，结果导致size错了，使得union的结构不平衡，导致TLE

*/
const int maxn = 1e5 + 10;
int N , Q;
vector<int> a[maxn];
vector<pair<int , int>> qs;
int csize[maxn];

void show(){
  for(int i = 1; i <= N; ++i){
    cout << i << " : ";
    for(int j : a[i])cout << j << " ";
    cout << endl;
  }
  for(int i = 1; i <= N; ++i){
    printf("size[%d] = %d ," , i , csize[i]);
  }
  cout << endl;
}

int find(int x){
  return a[x].back() == x ? x : find(a[x].back());
}

void add(int x , int y){
  x = find(x);
  y = find(y);
  if(x != y){ // different ancestor
    if(csize[x] > csize[y])swap(x , y); //link the smaller one to larger one
    a[x].push_back(y);
    csize[y] += csize[x];
  }
  qs.emplace_back(x , y);
}

int main(){
  //ios::sync_with_stdio(false);
  //cin.tie(nullptr);
  //cin >> N >> Q;
  scanf("%d %d" , &N , &Q);
  qs.clear();
  for(int i = 1; i <= N; ++i)a[i].clear();
  for(int i = 1; i <= N; ++i)a[i].push_back(i) , csize[i] = 1;
  for(int q = 1; q <= Q; ++q){
    char op;
    cin >> op;
    if(op == 'A'){ //add connection
      int x , y;
      scanf("%d %d" , &x , &y);
      //cin >> x >> y;
      add(x , y);
    }
    else if(op == 'D'){ //delete most recent connection
      if(qs.empty())continue;
      int x = qs.back().first;
      int y = qs.back().second;
      qs.pop_back();
      if(a[x].empty())continue;
      if(x != y){
        a[x].pop_back();
        csize[x] -= csize[y];
      }
    }
    else if(op == 'Q'){ //query
      int x , y;
      cin >> x >> y;
      if(find(x) == find(y))printf("1\n");//cout << "1\n";
      else printf("0\n");//cout << "0\n";
    }
  }
}
