#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 5e5 + 10;
ll cnt[maxn];
bool vis[maxn];
int B , F;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> B >> F;
    ll up = 0;
    for(int i = 1; i <= B; ++i){
        ll c , s; cin >> c >> s;
        cnt[s] += c;
        up = max(up , s);
    }
    ll ret = 0;
    vector<int> fs;
    for(int i = 1; i <= F; ++i){
        int j; cin >> j;
        fs.push_back(j);
    }
    sort(fs.begin() , fs.end());
    for(int i = 0; i < F; ++i){
        int f = fs[i];
        if(vis[f])continue;
        for(int j = f; j <= up; j += f){
            ret += cnt[j]; cnt[j] = 0; vis[j] = 1;
        }
    }
    cout << ret << endl;
}
