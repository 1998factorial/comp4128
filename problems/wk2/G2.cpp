#include <iostream>
#include <cstdio>
#include <set>
#include <map>
using namespace std;

typedef long long ll;

const int maxn = 2e5+5;

set<int> S[maxn];

int x[maxn],y[maxn],c[maxn];
int r[maxn], xs[maxn];

int *cmp_c;
bool cmp_id(int i,int j){ return cmp_c[i] < cmp_c[j]; }

int C[maxn];
int ns;

void add(int x)
{
    while(x <= ns){
        C[x]++; x += x&-x;
    }
}

int sum(int x)
{
    int re = 0;
    while(x > 0){
        re += C[x]; x &= x-1;
    }
    return re;
}


void solve()
{
    int n, m, i, j, k;
    scanf("%d%d",&n,&m);
    for(i = 0; i < n; i++) {
        scanf("%d%d%d",x+i,y+i,c+i);
        r[i] = i;
    }

    cmp_c = x;
    sort(r,r+n,cmp_id);
    ns = 1;
    xs[r[0]] = ns;
    for(i = 1; i < n; i++){
        xs[r[i]] = (x[r[i]] == x[r[i-1]]) ? ns:++ns;
    }

    for(i = 1; i <= m; i++){
        S[i].clear();
        S[i].insert(0);
        S[i].insert(ns+1);
    }

    cmp_c = y;
    for(i = 0; i < n; i++) r[i] = i;
    sort(r,r+n,cmp_id);

    memset(C+1,0,sizeof(int)*ns);

    int ans = 0, p, q, cur_y;
    for(i = 0; i < n; i = k){
        cur_y = y[r[i]];
        for(j = i; j < n && y[k = r[j]] == cur_y; j++){
            auto it = S[c[k]].lower_bound(xs[k]);
            p = *it-1;
            q = *--it;
            if(p > q)
                ans = max(ans,sum(p)-sum(q));
        }
        k = j;
        while(--j >= i){
            p = r[j];
            S[c[p]].insert(xs[p]);
            add(xs[p]);
        }
    }
    for(i = 1; i <= m; i++){
        auto it = S[i].begin();
        q = 0;
        for(it++; it != S[i].end(); it++){
            p = *it-1;
            if(p > q) ans = max(ans, sum(p) - sum(q));
            q = *it;
        }
    }
    printf("%d\n", ans);
}

//#define LOCAL
int main()
{
#ifdef LOCAL
    freopen("in.txt","r",stdin);
#endif
    int T; scanf("%d",&T);
    while(T--) solve();
    return 0;
}
