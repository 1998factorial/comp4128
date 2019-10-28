#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

int N , n , C[21];
int tot , best;

void DFS(int pos , int sum , int state){
  if(sum > N){
    return; //pruning
  }
  if(pos >= n){
    if(sum > tot){
      tot = sum;
      best = state;
    }
    return;
  }
  DFS(pos + 1 , sum + C[pos] , state | (1 << pos));
  DFS(pos + 1 , sum , state);
}

int main(){
  while(cin >> N){
    cin >> n;
    for(int i = 0; i < n; ++i){
      cin >> C[i];
    }
    tot = best = 0;
    DFS(0 , 0 , 0);
    for(int i = 0; i < n; ++i){
      if(best & (1 << i))cout << C[i] << " ";
    }
    cout << "sum:" << tot << endl;
  }
}
