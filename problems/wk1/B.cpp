#include <iostream>
#include <cstring>
using namespace std;

string s , t;

bool check(){
  int n = s.size() , m = t.size();
  int i = 0 , j = 0;
  for(; j < m; ++j){
    if(t[j] == s[i]){
      ++i;
    }
  }
  return i == n;
}

int main(){
  while(cin >> s >> t){
    if(check())cout << "Yes\n";
    else cout << "No\n";
  }
}
