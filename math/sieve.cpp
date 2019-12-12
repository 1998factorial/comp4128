#include <iostream>
#include <vector>
using namespace std;

const int N = 1e6;
bool vis[N];
vector<int> primes;

int main(){
  for(int i = 2; i < N; ++i){
    if(!vis[i]){
      primes.push_back(i);
      for(int j = i; j < N; j += i){
        vis[j] = true;
      }
    }
  }
  for(int i : primes)cout << i << " ";
  cout << endl;
}
