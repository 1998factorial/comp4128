#include <stdio.h>
#include <string.h>
#define inf 1e9
/*
8 by 8 board , given initial and final coordinate of knight,
find number of shortest paths from initial to final.
*/
int xi , yi , xf , yf;
int dist[64][64]; //dist[i][j] = the shortest length from i to j
int g[64][64]; //graph
int dx[8] = {1 , 1 , 2 , 2 , -1 , -1 , -2 , -2}; // possible x-direction
int dy[8] = {2 , -2 , 1 , -1 , 2 , -2 , 1 , -1}; // possible y-direction
int cnt; // answer
int vis[64]; // mark if visited

int neighbour(int x , int y , int a , int b){ // check if (a , b) is reachable from (x , y)
  int ret = 0;
  for(int i = 0; i < 8; ++i){
    if(x + dx[i] == a && y + dy[i] == b){
      ret = 1;
    }
  }
  return ret;
}

void DFS(int v , int len , int end){ // compute answer
  vis[v] = 1;
  if(len == 0){ // base case
    if(v == end){
      cnt++; // good path
    }
  }
  else{
    for(int u = 0; u < 64; ++u){
      if(!vis[u] && neighbour(v / 8 , v % 8 , u / 8 , u % 8)){ // if u is not visited and rechable from v
        DFS(u , len - 1,  end);
      }
    }
  }
  vis[v] = 0;
}

int main(){
  for(int x = 0; x < 8; ++x){
    for(int y = 0; y < 8; ++y){
      for(int i = 0; i < 8; ++i){
        for(int j = 0; j < 8; ++j){
          int from = x * 8 + y;
          int to  = i * 8 + j;
          if(from == to){
            g[from][to] = g[to][from] = dist[to][from] = dist[from][to] = 0;
            continue;
          }
          if(neighbour(x , y , i , j)){
            g[from][to] = g[to][from] = 1;
            dist[from][to] = dist[to][from] = 1;
          }
          else{
            g[from][to] = g[to][from] = 0;
            dist[from][to] = dist[to][from] = inf;
          }
        }
      }
    }
  }
  // floyd algorithm
  for(int k = 0; k < 64; ++k){
    for(int i = 0; i < 64; ++i){
      for(int j = 0; j < 64; ++j){
        if(dist[i][j] > dist[i][k] + dist[k][j]){
          dist[i][j] = dist[i][k] + dist[k][j];
        }
      }
    }
  }
  while(~scanf("%d %d %d %d" , &xi , &yi , &xf , &yf)){
    int start = xi * 8 + yi;
    int end = xf * 8 + yf;
    memset(vis , 0 , sizeof(vis));
    cnt = 0;
    DFS(start , dist[start][end] , end);
    printf("%d\n" , cnt);
  }
  return 0;
}
