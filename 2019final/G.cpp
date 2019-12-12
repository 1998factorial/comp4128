#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5 + 10;
ll C;
int N;
ll dp[maxn];
ll P[maxn];
ll S[maxn];

ll cost(int i , int j){
    return (S[i - 1] - S[0]) * (S[j] - S[i - 1]);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N >> C;
    S[0] = 0;
    for(int i = 1; i <= N; ++i){
        cin >> P[i];
        S[i] = S[i - 1] + P[i];
    }
    dp[1] = 0;
    for(int i = 2; i <= N; ++i){
        for(int j = 1; j <= N; ++j){
            dp[i] = max(dp[i] , dp[j - 1] + S[i] * S[j - 1] - S[j - 1] * S[j - 1] - C);
        }
    }
    cout << dp[N] << endl;
}
