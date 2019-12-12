#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 3e2 + 10;
const ll inf = 1e18;
int N , M;
ll dp[maxn][maxn];
ll len[maxn][maxn];

int main(){
    cin >> N >> M;
    for(int i = 1; i <= N; ++i){
        for(int j = 1; j <= N; ++j){
            dp[i][j] = -inf;
            len[i][j] = inf;
        }
    }
    for(int i = 1; i <= M; ++i){
        int x , y;
        ll cost , gain;
        cin >> x >> y >> cost >> gain;
        dp[x][y] = gain - cost;
        len[x][y] = 1;

    for(int k = 1; k <= N; ++k){
        for(int i = 1; i <= N; ++i){
            for(int j = 1; j <= N; ++j){
                if(dp[i][j] < dp[i][k] + dp[k][j]){
                    dp[i][j] = dp[i][k] + dp[k][j];
                    len[i][j] = len[i][k] + len[k][j];
                }
                else if(dp[i][j] == dp[i][k] + dp[k][j]){
                    if(len[i][j] > len[i][k] + len[k][j]){
                        len[i][j] = len[i][k] + len[k][j];
                    }
                }
            }
        }
        ll bestlen = inf;
        for(int i = 1; i <= N; ++i){
            if(dp[i][i] > 0){
                if(len[i][i] < bestlen){
                    bestlen = len[i][i];
                }
            }
        }
        if(bestlen < inf){
            ll ret = -inf;
            for(int i = 1; i <= N; ++i){
                if(dp[i][i] > 0 && len[i][i] == bestlen){
                    ret = max(ret , dp[i][i]);
                }
            }
            cout << bestlen << " " << ret << endl;
            return 0;
        }
    }
    return 0;
}
