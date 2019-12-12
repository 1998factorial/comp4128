#include <vector>
#include <algorithm>
#include <iostream>
#include <string.h>
using namespace std;
const int maxn = 1e5 + 10;
vector<int> g[maxn];
int N , M;
bool vis[maxn] , active[maxn];

bool cycle(int v){
	if(vis[v])return false;
	vis[v] = active[v] = true;
	for(int u : g[v]){
		if(active[u] || cycle(u))
			return true;
	}
	active[v] = false;
	return false;
}

int main(){
  cin >> N >> M;
  for(int i = 1; i <= M; ++i){
    int x , y; cin >> x >> y;
    g[x].push_back(y);
  }
	bool ret = false;
	for(int i = 1; i <= N; ++i)
		ret |= cycle(i);
  if(ret)cout << "YES\n";
	else cout << "NO\n";
}
