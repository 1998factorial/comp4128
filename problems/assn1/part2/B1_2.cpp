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

  这个版本是对的

*/
const int maxn = 1e5 + 10;
int N , Q;
vector<int> a[maxn];
vector<pair<int , int>> qs;
vector<int> csize[maxn];

int find(int x){
  return a[x].back() == x ? x : find(a[x].back());
}

void add(int x , int y){
  x = find(x);
  y = find(y);
  if(x != y){ // different ancestor
    if(csize[x].back() > csize[y].back())swap(x , y); //link the smaller one to larger one
    a[x].push_back(y);
    a[y].push_back(y);
    int sx = csize[x].back() , sy = csize[y].back();
    csize[x].push_back(sx + sy);
    csize[y].push_back(sx + sy);
  }
  else {
    a[x].push_back(x);
    a[y].push_back(y);
    csize[x].push_back(csize[x].back());
    csize[y].push_back(csize[y].back());
  }
  qs.emplace_back(x , y);
}

int main(){
  scanf("%d %d" , &N , &Q);
  qs.clear();
  for(int i = 1; i <= N; ++i)a[i].clear() , csize[i].clear();
  for(int i = 1; i <= N; ++i)a[i].push_back(i) , csize[i].push_back(1);
  for(int q = 1; q <= Q; ++q){
    char op;
    cin >> op;
    if(op == 'A'){ //add connection
      int x , y;
      scanf("%d %d" , &x , &y);
      add(x , y);
    }
    else if(op == 'D'){ //delete most recent connection
      if(qs.empty())continue;
      int x = qs.back().first;
      int y = qs.back().second;
      qs.pop_back();
      a[x].pop_back();
      a[y].pop_back();
      csize[x].pop_back();
      csize[y].pop_back();
    }
    else if(op == 'Q'){ //query
      int x , y;
      cin >> x >> y;
      if(find(x) == find(y))printf("1\n");
      else printf("0\n");
    }
  }
}
