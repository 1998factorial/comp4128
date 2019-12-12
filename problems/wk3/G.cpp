#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <unordered_map>
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;
int N;
const int inf = 1 << 20;
double a[404] , b[405] , h[405];
unordered_map<double , int> mp;

// R 有单调性 -> binary search answer

struct edge{
  int from , to;
  int w;
  edge(){}
  edge(int x , int y , int z) : from(x) , to(y) , w(z){}
};

vector<edge> edges;
int dis[1500];
int cnt;

void relax(){
  for(int i = 0; i < edges.size(); ++i){
    int u = edges[i].from;
    int v = edges[i].to;
    int c = edges[i].w;
    if(dis[v] > dis[u] + c){
      dis[v] = dis[u] + c;
    }
  }
}

bool check(){
  for(int i = 1; i <= cnt; ++i){
    dis[i] = inf;
  }
  dis[0] = 0;
  for(int i = 1; i <= cnt; ++i){
    relax ();
  }
  for(int i = 0; i < edges.size(); ++i){
    int u = edges[i].from;
    int v = edges[i].to;
    int c = edges[i].w;
    if(dis[v] > dis[u] + c){
      return false;
    }
  }
  return true;
}

void init(int k){
  //discrete
  vector<double> p;
  for(int i = 1; i <= N; ++i){
    p.push_back(a[i]);
    p.push_back(b[i]);
    p.push_back((a[i] + b[i]) / 2.0); //mid point of interval
  }
  edges.clear();
  sort(p.begin() , p.end());
  cnt = 1;
  mp.clear();
  mp[p[0]] = cnt;
  for(int i = 1; i < p.size(); ++i){
    if(p[i] != p[i - 1]){
      ++cnt;
      mp[p[i]] = cnt;
    }
  }
  for(int i = 1; i <= N; ++i){ // build graph
    int l = mp[a[i]];
    int r = mp[b[i]];
    edges.push_back(edge(r , l - 1 , k));
    edges.push_back(edge(l - 1 , r , -1));
  }
  for(int i = 1; i <= cnt; ++i){
    edges.push_back(edge(i - 1 , i , 0));
  }
}

int main(){
  cin >> N;
  for(int i = 1; i <= N; ++i){
    cin >> a[i] >> b[i] >> h[i];
    a[i] += 0.1;
    b[i] -= 0.1;
  }
  int l = 0 , r = N;
  while(l < r){ // binary search answer
    int mid = (l + r) >> 1;
    init(mid);
    if(check()){
      r = mid;
    }
    else{
      l = mid + 1;
    }
  }
  cout << l << endl;
  return 0;
}
