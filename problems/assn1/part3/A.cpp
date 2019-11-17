#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;
typedef pair<int , int> ii;
const int maxn = 2e5 + 10;
int N , M , Q;
/*
  sort queries by time
*/
struct query{
  int time , city , id;
  query(int t_ , int c_ , int id_):time(t_) , city(c_) , id(id_) {}
  bool operator < (const query& other) const {
    return time < other.time;
  }
};

struct edge{
  int a , b , time;
  edge(int a_ , int b_ , int t_) : a(a_) , b(b_) , time(t_) {}
  bool operator < (const edge& other) const {
    return time < other.time;
  }
};

vector<query> qs;
vector<edge> edges;
int a[maxn];
int cs[maxn];
int ans[maxn];

int find(int x){
  return a[x] == x ? x : a[x] = find(a[x]);
}

void add(int x , int y){
  x = find(x);
  y = find(y);
  if(x != y){
    if(cs[x] > cs[y])swap(x , y);
    cs[x] += cs[y];
    a[y] = x;
  }
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> M >> Q;
  qs.clear();
  edges.clear();
  for(int i = 1; i <= N; ++i)a[i] = i , cs[i] = 1;
  for(int i = 1; i <= M; ++i){
    int x , y , z;
    cin >> x >> y >> z;
    edges.emplace_back(x , y , z);
  }
  for(int q = 1; q <= Q; ++q){
    int time , city;
    cin >> city >> time;
    qs.push_back(query(time , city , q));
  }
  sort(qs.begin() , qs.end());
  sort(edges.begin() , edges.end());
  int j = 0;
  for(int i = 0; i < Q; ++i){
    while(j < M && edges[j].time <= qs[i].time){
      add(edges[j].a , edges[j].b);
      ++j;
    }
    ans[qs[i].id] = cs[find(qs[i].city)];
  }
  for(int i = 1; i <= Q; ++i){
    cout << ans[i] << endl;
  }
}
