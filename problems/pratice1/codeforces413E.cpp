#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

const int maxn = 2e5 + 10;
int N , Q;
string maze[2];
int dp[maxn << 2][2][2];
int inf = 1 << 28;

struct state{
  int dis[2][2];
  state(int x1 , int x2 , int x3 , int x4){
    dis[0][0] = x1;
    dis[0][1] = x2;
    dis[1][0] = x3;
    dis[1][1] = x4;
  }
};

void build(int l , int r , int id){
  if(l > r)return;
  if(l == r){
    for(int i = 0; i < 2; ++i){
      for(int j = 0; j < 2; ++j){
        if(maze[j][l] == 'X' || maze[i][l] == 'X')dp[id][i][j] = inf;
        else dp[id][i][j] = (i == j) ? 0 : 1;
      }
    }
  }
  else{
    int m = (l + r) >> 1;
    build(l , m , id << 1);
    build(m + 1 , r , id << 1 | 1);
    for(int i = 0; i < 2; ++i){
      for(int j = 0; j < 2; ++j){
        dp[id][i][j] = inf;
        for(int x = 0; x < 2; ++x){
          for(int y = 0; y < 2; ++y){
            if(maze[x][m] == 'X')continue;
            if(maze[y][m + 1] == 'X')continue;
            if(x == y){
              dp[id][i][j] = min(dp[id][i][j] , dp[id << 1][i][x] + dp[id << 1 | 1][y][j] + 1);
            }
            else{
              if(maze[1 - x][m] == 'X' && maze[1 - y][m + 1] == 'X')continue;
              dp[id][i][j] = min(dp[id][i][j] , dp[id << 1][i][x] + dp[id << 1 | 1][y][j] + 2);
            }
          }
        }
      }
    }
  }
}

state query(int l , int r , int x , int y , int id){
  if(l > r || x > r || y < l){
    return state(inf , inf , inf , inf);
  }
  if(l <= x && y <= r){
    return state(dp[id][0][0] , dp[id][0][1] , dp[id][1][0] , dp[id][1][1]);
  }
  int m = (x + y) >> 1;
  if(m >= r){
    return query(l , r , x , m , id << 1);
  }
  if(m < l){
    return query(l , r , m + 1 , y , id << 1 | 1);
  }
  state ret = state(inf , inf , inf , inf);
  state lr = query(l , r , x , m , id << 1);
  state rr = query(l , r , m + 1 , y , id << 1 | 1);
  for(int i = 0; i < 2; ++i){
    for(int j = 0; j < 2; ++j){
      for(int x = 0; x < 2; ++x){
        for(int y = 0; y < 2; ++y){
          if(x == y){
            ret.dis[i][j] = min(ret.dis[i][j] , lr.dis[i][x] + rr.dis[y][j] + 1);
          }
          else{
            if(maze[1 - x][m] == 'X' && maze[1 - y][m + 1] == 'X')continue;
            ret.dis[i][j] = min(ret.dis[i][j] , lr.dis[i][x] + rr.dis[y][j] + 2);
          }
        }
      }
    }
  }
  return ret;
}

int main(){
  scanf("%d %d", &N , &Q);
  cin >> maze[0];
  cin >> maze[1];
  build(0 , N - 1 , 1);
  for(int q = 1; q <= Q; ++q){
    int u , v;
    scanf("%d %d" , &u , &v);
    int fx , fy , tx , ty;
    fx = (u - 1) % N + 1;
    fy = (u > N) ? 2 : 1;
    tx = (v - 1) % N + 1;
    ty = (v > N) ? 2 : 1;
    if(fx > tx){
      swap(fx , tx);
      swap(fy , ty);
    }
    //printf("find (%d %d) to (%d %d)\n" , fx - 1, fy -1 , tx -1, ty-1);
    state ans = query(fx - 1 , tx - 1 , 0 , N - 1 , 1);
    if(ans.dis[fy - 1][ty - 1] >= inf)printf("-1\n");
    else printf("%d\n" , ans.dis[fy - 1][ty - 1]);
  }
  return 0;
}
