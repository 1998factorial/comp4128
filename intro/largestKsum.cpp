#include <iostream>
#include <algorithm>
using namespace std;

//O(n) algo of finding the largest contiguous subseq sum with k elements
const int N = 1e6 + 5;
int s[N];


int main(){
	int n,k;
	cin >> n >> k; //get n and k
	for(int i = 0; i < n; i++)cin >> s[i];

	cout <<'[';
	for(int i = 0; i < n; i++)cout << s[i] << ' ';
	cout <<']'<<endl;
	
	cout <<"k = "<<k<<endl;

	long long val = 0, sum = 0;

	for(int i = 0; i < n; i++){
		if(i >= k)sum -= s[i-k];
		sum += s[i];
		if(i >= k-1)val = max(sum,val);
	}

	cout << "maximal k-sum = "<< val << endl;
	return 0;
}



