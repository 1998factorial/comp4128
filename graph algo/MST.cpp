#include <vector>
#include <algorithm>
#include <iostream>
#include <string.h>
using namespace std;
const int maxn = 1e5 + 10;

struct edge{
  int from , to , w;
  edge(){}
  edge(int f_ , int t_ , int w_): from(f_) , to(t_) , w(w_) {}
  bool operator < (const edge& other) const {
    return w < other.w;
  }
};

int id[maxn];
vector<edge> edges;
vector<edge> tree;
int N , M;

int find(int x){
  return id[x] == x ? x : id[x] = find(id[x]);
}

void add(int x , int y){
  x = find(x);
  y = find(y);
  if(x != y){
    id[x] = y;
  }
}

void MST(){
  for(auto& e : edges){
    int x = find(e.from) , y = find(e.to);
    if(x != y){
      tree.push_back(e);
      add(x , y);
    }
  }
}

int main(){
  cin >> N >> M;
  for(int i = 1; i <= M; ++i){
    int x , y , w; cin >> x >> y >> w;
    edges.emplace_back(x , y , w);
  }
  sort(edges.begin() , edges.end());
  for(int i = 1; i <= N; ++i)id[i] = i;
  MST();
  int ret = 0;
  for(auto& e : tree){
    ret += e.w;
    cout << e.from << " " << e.to << endl;
  }
  cout << ret << endl;
}
