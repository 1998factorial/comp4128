#include <bits/stdc++.h>
using namespace std;

const int maxn = 5e4 + 10;
const int inf = 1e9;
int N , W , K;
int a[maxn];
int sum[maxn];
int dp[maxn][3]; //K is at most 3

int cost(int i , int j){
    return sum[j] - sum[i];
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N >> W >> K;
    sum[0] = 0;
    for(int i = 1; i <= N; ++i)
        cin >> a[i] , sum[i] = sum[i - 1] + a[i];
    int ret = 0;
    for(int i = W; i <= N; ++i){
        dp[i][1] = cost(i - W , i);
        ret = max(ret , dp[i][1]);
    }
    for(int j = 2; j <= K; ++j){
        int mx = 0;
        for(int i = 1; i <= (j - 1) * W; ++i){
            mx = max(mx , dp[i][j - 1]);
        }
        for(int i = j * W; i <= N; ++i){
            dp[i][j] = max(dp[i][j] , mx + cost(i - W , i));
            ret = max(ret , dp[i][j]);
            mx = max(mx , dp[i - W + 1][j - 1]);
        }
    }
    cout << ret << endl;
}
