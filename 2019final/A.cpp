#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll mod = 1e9 + 7;
int N;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N;
    ll a = 0 , b = 1;
    ll ret = 1;
    for(int i = 1; i <= N; ++i){
        ll ta = b;
        ll tb = (a + b) % mod;
        ret = (ta + tb) % mod;
        a = ta , b = tb;
    }
    cout << (ret + mod) % mod << endl;
} 
