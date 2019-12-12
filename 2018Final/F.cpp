#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std;
const int maxn = 1e3 + 10;
const int inf = 1e9;
int g[maxn][maxn];
int N , M;
bool ok[maxn][maxn][2];

int sub(int x){
  return (x + N - 2) % N + 1;
}

int add(int x){
  return x % N + 1;
}

void solve(int i , int j , int k){
  int pos = (k == 0) ? i : j;
  cout << pos << endl;
  if(i == j)return;
  if(k == 0){
    //at i
    int x = add(i);
    if(x < j){
      if(ok[x][j][0])solve(x , j , 0);
      else if(ok[x][j][1])solve(x , j , 1);
    }
    else{
      if(ok[x][j][1])solve(x , j , 1);
      else if(ok[x][j][0])solve(x , j , 0);
    }
  }
  else{
    //at j
    int x = sub(j);
    if(i < x){
      if(ok[i][x][0])solve(i , x , 0);
      else if(ok[i][x][1])solve(i , x , 1);
    }
    else{
      if(ok[i][x][1])solve(i , x , 1);
      else if(ok[i][x][0])solve(i , x , 0);
    }
  }
}

int main(){
  cin >> N >> M;
  for(int i = 1; i <= N; ++i)
    for(int j = 1; j <= N; ++j)
      g[i][j] = 0;
  for(int i = 1; i <= M; ++i){
    int x , y; cin >> x >> y;
    g[x][y] = g[y][x] = 1;
  }
  memset(ok , false , sizeof(ok));
  for(int i = 1; i <= N; ++i)
    for(int j = 0; j < 2; ++j)
      ok[i][i][j] = 1;
  for(int len = 2; len <= N; ++len){
    for(int i = 1; i <= N; ++i){
      int j = (i + len - 2) % N + 1;
      int i1 = add(i);
      int j1 = sub(j);
      ok[i][j][0] |= ok[i1][j][0] && g[i][i1];
      ok[i][j][0] |= ok[i1][j][1] && g[i][j];
      ok[i][j][1] |= ok[i][j1][0] && g[j][i];
      ok[i][j][1] |= ok[i][j1][1] && g[j][j1];
      //if(ok[i][j][0]) cout << "ending at " << i << " for " << i << " " << j << " ok \n";
      //if(ok[i][j][1]) cout << "ending at " << j << " for " << i << " " << j << " ok \n";
    }
  }
  int start = inf , l = -1 , r = -1 , p = -1;
  for(int i = 1; i <= N; ++i){
    for(int k = 0; k < 2; ++k){
      int j = sub(i);
      if(ok[i][j][k]){
        if(k){
          if(start > j){
            start = j , l = i , r = j , p = k;
          }
        }
        else{
          if(start > i){
            start = i , l = i , r = j , p = k;
          }
        }
      }
    }
  }
  if(start >= inf)cout << -1 << endl;
  else{
    //cout << l << " " << r << " " << p << endl;
    solve(l , r , p);
  }
}
