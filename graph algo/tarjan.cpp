#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 1005;
int n , m , low[N] , dfn[N] , cnt;
vector<int> g[N];
vector<int> s;
bool ins[N];

void tarjan(int v){ //find strongly connected components in graph
  ++cnt;
  dfn[v] = low[v] = cnt; //increase dfn & low count
  s.push_back(v); //push to stack
  ins[v] = true; //in stack
  for(int i : g[v]){
    if(!dfn[i]){ //have not visited
      tarjan(i);
      low[v] = min(low[v] , low[i]);
    }
    else if(ins[i]){ //inside our stack
      low[v] = min(low[v] , dfn[i]);
    }
  }
  if(dfn[v] == low[v]){ // v is the root for this connected component !
    cout << "component : ";
    while(!s.empty()){ //everything above v in stack belong to the connected component rooted at v
      cout << s.back() << " ";
      int k = s.back();
      s.pop_back();
      ins[k] = false;
      if(k == v)break;
    }
    cout << endl;
  }
}

int main(){
  cin >> n >> m;
  for(int i = 1; i <= n; ++i)g[i].clear();
  s.clear();
  for(int i = 1; i <= m; ++i){
    int x , y;
    cin >> x >> y;
    g[x].push_back(y);
  }
  for(int i = 1; i <= n; ++i){
    dfn[i] = 0;
    low[i] = 1006;
    ins[i] = false;
  }
  cnt = 0;
  for(int i = 1; i <= n; ++i){
    if(!dfn[i]){
      tarjan(i);
    }
  }
}
