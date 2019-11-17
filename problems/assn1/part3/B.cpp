#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;
typedef pair<int , int> ii;

const int maxn = 2e5 + 10;
int Q , N , M;
int parent[maxn] , cs[maxn];
vector<ii> s[maxn];

struct edge{
  int a , b , time;
  edge(int a_ , int b_ , int t_) : a(a_) , b(b_) , time(t_) {}
  bool operator < (const edge& other) const {
    return time < other.time;
  }
};

vector<edge> edges;

int find(int x){
  return parent[x] == x ? x : find(parent[x]);
}

void add(int x , int y , int t){
  x = find(x);
  y = find(y);
  if(x != y){ // change x's parent
    if(cs[x] > cs[y])swap(x , y); // union by size
    cs[y] += cs[x]; // increase the size of connected component rooted at y
    parent[x] = y; // set x's parent to y
    s[x].emplace_back(t , cs[y]);
    s[y].emplace_back(t , cs[y]);
  }
}

int query(int time , int x){
  if(s[x].empty())return 1;
  if(s[x].back().first < time && parent[x] != x) // last time modified x as parent is less than time
    return query(time , parent[x]); // means we need to look for x's parent
  int l = 0 , r = s[x].size() - 1 , ret = -1;
  while(l <= r){
    int mid = (l + r) >> 1;
    if(s[x][mid].first > time){
      r = mid - 1;
    }
    else{
      ret = mid;
      l = mid + 1;
    }
  }
  if(ret == -1)return 1; // the node's parent is not modified when t = time
  return s[x][ret].second;
}

void show(){
  for(int i = 1; i <= N; ++i){
    cout << i << " : ";
    for(ii j : s[i])
      printf("(%d %d) " , j.first , j.second);
    cout << endl;
  }
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> M >> Q;
  edges.clear();
  for(int i = 1; i <= N; ++i)parent[i] = i , cs[i] = 1 , s[i].clear();
  for(int i = 1; i <= M; ++i){
    int a , b , t;
    cin >> a >> b >> t;
    edges.emplace_back(a , b , t);
  }
  sort(edges.begin() , edges.end());
  for(int i = 0; i < M; ++i){
    add(edges[i].a , edges[i].b , edges[i].time);
  }
  for(int i = 1; i <= N; ++i)
    sort(s[i].begin() , s[i].end());
  int last = 0;
  for(int i = 1; i <= Q; ++i){
    int time , city;
    cin >> city >> time;
    time ^= last;
    city ^= last;
    last = query(time , city);
    cout << last << endl;
  }
}
