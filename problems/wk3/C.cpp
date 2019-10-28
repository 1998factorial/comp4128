#include <iostream>
#include <cstdio>
#include <set>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

int S , N;
double X[505] , Y[505];
int id[505];

struct edge{
  int i , j;
  double w;
  edge(int ii , int jj , double ww){
    i = ii;
    j = jj;
    w = ww;
  }
  bool operator<(const edge& o) const {
    return w < o.w;
  }
};

double dis(int i , int j){
  return sqrt((X[i] - X[j]) * (X[i] - X[j]) + (Y[i] - Y[j]) * (Y[i] - Y[j]));
}

int find(int i){
  return (id[i] == i) ? i : id[i] = find(id[i]);
}

void add(int i , int j){
  i = find(i);
  j = find(j);
  if(i != j){
    id[i] = j;
  }
}

int main(){
  int T;
  cin >> T;
  for(int t = 1; t <= T; ++t){
    cin >> S >> N;
    for(int i = 1; i <= N; ++i){
      cin >> X[i] >> Y[i];
      id[i] = i;
    }
    vector<edge> edges;
    for(int k = 1; k <= N; ++k){
      for(int j = k + 1; j <= N; ++j){
        edges.push_back(edge(k , j , dis(k , j)));
      }
    }
    sort(edges.begin() , edges.end());
    vector<edge> tree;
    for(int k = 0; k < edges.size(); ++k){
      int x = edges[k].i;
      int y = edges[k].j;
      if(find(x) != find(y)){
        add(x , y);
        tree.push_back(edges[k]);
      }
    }
    sort(tree.begin() , tree.end());
    int k = tree.size() - 1;
    for(; k >= 0 && S > 1; --k , --S);
    if(k >= 0){
      printf("%.2f\n" , tree[k].w);
    }
  }
  return 0;
}
