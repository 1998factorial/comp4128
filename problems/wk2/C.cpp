#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <cstdio>
using namespace std;
typedef pair<int , int> ii;
typedef long long ll;
const int inf = 50000000;
const int maxn = 1e5 + 10;
ll H[maxn] , Hs[maxn] , Hss[maxn];
unordered_map<ll , int> mp; //离散化
int dp[maxn << 2][2]; //[l .. r] max length , index
int dp2[maxn]; //dp2[i] = maximal length ending at i
int pre[maxn]; //i's previous
int N , D;
/*
用线段树维护区间内的dp最值从而达到logn时间复杂度的搜素
这题用到了数据离散化 + 各种mapping + back track + dp 思想 + 线段树思想
*/
void update(int l , int r , int pos , int val , int index , int id){
  if(l > r || pos < l || pos > r)return;
  if(l == r && l == pos){
    dp[id][0] = val;
    dp[id][1] = index;
  }
  else{
    int m = (l + r) >> 1;
    update(l , m , pos , val , index , id << 1);
    update(m + 1 , r , pos , val , index , id << 1 | 1);
    dp[id][0] = (dp[id << 1][0] > dp[id << 1 | 1][0]) ? dp[id << 1][0] : dp[id << 1 | 1][0];
    dp[id][1] = (dp[id << 1][0] > dp[id << 1 | 1][0]) ? dp[id << 1][1] : dp[id << 1 | 1][1];
  }
}

int query(int l , int r , int x , int y , int id){
  if(y < l || x > r){ // out of range
    return -1;
  }
  else if (x >= l && y <= r){ // in the range
    return dp[id][1];
  }
  int m = (x + y) >> 1;
  int left = query(l , r , x , m , id << 1);
  int right = query(l , r , m + 1 , y , id << 1 | 1);
  int ret = (dp2[left] > dp2[right]) ? left : right;
  return ret;
}

int main(){
  cin >> N >> D;
  for(int i = 0; i < N; ++i){
    cin >> H[i];
    Hss[i] = H[i]; // Hs will be sorted version of Hs
    pre[i] = -1; // ini pre
    dp2[i] = 0;
  }
  sort(Hss , Hss + N);
  int tot = 0; // total number of distinct number in H
  mp[Hss[0]] = tot;
  Hs[0] = Hss[0];
  for(int i = 1; i < N; ++i){
    if(Hss[i] != Hss[i - 1]){
      ++tot;
      mp[Hss[i]] = tot;
      Hs[tot] = Hss[i];
    }
  }
  for(int i = 0; i <= (N << 2); ++i){
    dp[i][0] = 0;
    dp[i][1] = -1;
  }
  for(int i = 0; i < N; ++i){
    auto j = lower_bound(Hs , Hs + tot , H[i] + D);
    auto k = lower_bound(Hs , Hs + tot , H[i] - D);
    if(*k > H[i] - D){
      if(k == Hs)k = nullptr;//left bound element is larger than target -> no such element in array
      else --k;
    }
    if(*j < H[i] + D)j = nullptr; //right bound element is smaller than target -> no such bound in array
    int left = -1 , right = -1;
    if(j != nullptr) right = query(mp[*j] , tot , 0 , tot , 1);
    if(k != nullptr) left = query(0 , mp[*k] , 0 , tot , 1);
    int best = -1;
    if(right == -1)best = left;
    if(left == -1)best = right;
    if(left > -1 && right > -1)best = (dp2[left] > dp2[right]) ? left : right;
    if(best >= 0){
      pre[i] = best;
      dp2[i] = 1 + dp2[best];
    }
    else dp2[i] = 1;
    update(0 , tot , mp[H[i]] , dp2[best] + 1 , i , 1);
  }
  cout << dp[1][0] << endl;
  int start = dp[1][1];
  vector<int> path;
  while(start != -1){
    path.push_back(start);
    start = pre[start];
  }
  reverse(path.begin() , path.end());
  for(int i = 0; i < path.size(); ++i){
    cout << path[i] + 1 << " ";
  }
  cout << endl;
  return 0;
}
