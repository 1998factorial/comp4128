#include <iostream>
using namespace std;

int n, a[12];
int num = 0;

void go(int i){ //i is the row number
	if(i == n){ //i == n, we have obtained our solution, thus print it out
		for(int k = 0; k < n; k++)
			cout << a[k]+1 << " ";
		cout << '\n';
		num++;
		return;
	}
	
	for(int j = 0; j < n; j++){
	//need to check if position (i,j) is vaild
		bool vaild = true;
		for(int k = 0; k < i; k++){ //we have placed i-1 queens
			if(a[k] == j || i - k == j - a[k] || i - k == a[k] - j)vaild = false;//check col and diagonals
		}
		if(vaild){//(i,j) is vaild
			a[i] = j;
			go(i+1);
		}
	}
}

int main(){
	cin >> n;
	go(0);
	cout << "number of arrangements = " << num << endl;
	return 0;
}

