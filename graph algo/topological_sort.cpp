//i->j <==> j comes after i
//if a directed graph has a cycle then the graph can not be topologically sorted

vector<bool> seen; //all false at the begining

void dfs(int i, vector<vector<int>>& G, vector<int>& order){
	if(seen[i])return;
	seen[i] = true;
	for(int j = 0; j < G[i].size(); j++)dfs(j,G,order);
	order.push_back(i); //add source last
}

vector<int> top_sort(){
	vector<int> ans;
	for(int i = 0; i < G.size(); i++)
		dfs(i,G,ans);
	reverse(ans.begin(),ans.end()); //reverse
	return ans;
}