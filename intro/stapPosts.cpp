#include <iostream>
#include <algorithm>
#include <utility>
using namespace std;

const int N = 1000000;
pair<int,int> victims[N];

//order posts by their end points, always stab the post that has the smallest end point among 
//unstabbed posts

int main(){
	//scan in (end,start) then sort by end points
	int n;
	cin >> n;
	for(int i = n; i --> 0;)cin >> victims[i].second >> victims[i].first;
	sort(victims,victims+n);
	for(int i = 0; i < n; i++)
		cout << "(" << victims[i].first << " , " << victims[i].second << ")" << endl;
	//(end,start)
	int last = -1000000, val = 0;
	for(int i = 0; i < n; i++){
		//if this post has been stabbed , skip it
		if(last >= victims[i].second)continue;
		//else stab at the end of it
		++val;
		last = victims[i].first;
	}

	cout << "# of nails needed = " << val << endl;
	return 0;
}