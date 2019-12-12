#include <iostream>
#include <vector>
using namespace std;

//int N = 10000; //number of vertices in graph

vector<int> edges[10000]; //each vertex has a list of connected vertices
bool seen[10000];

void add(int u, int v){
	edges[u].push_back(v);
	edges[v].push_back(u);
}

int min(int i, int j){
	return (i > j) ? j : i;//<==> if(i > j)return j;else return
}

void dfs(int u){
	if(seen[u])return;
	cout << u << endl;
	seen[u] = true;
	for(int v: edges[u])dfs(v);
}

int main(){
	add(0,1);
	add(0,2);
	add(100,0);
	add(100,1);
	add(100,2);
	//for(int v: edges[0])cout << v << endl;
	//for(int v: edges[100])cout << v << endl;
	dfs(0);
	return 0;
}