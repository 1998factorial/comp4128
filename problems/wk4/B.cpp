#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds ;
using namespace std ;
typedef tree <int , null_type , less <int >, rb_tree_tag ,
tree_order_statistics_node_update> ordered_set ;

const int maxn = 2e5 + 10;
int N , Q;
ordered_set s[maxn << 2]; //ordered statistic tree used as segment tree on tree
int dfn[maxn]; //dfs ordering
int R[maxn]; //the interval
int a[maxn]; //old value on each node
int mp[maxn]; //inverse of dfn for each v
bool vis[maxn];
vector<int> g[maxn];
int cnt;

void DFS(int v){
    vis[v] = true;
    dfn[v] = cnt;
    mp[cnt] = v;
    ++cnt;
    for(int i : g[v]){
        if(!vis[i])
            DFS(i);
    }
    R[dfn[v]] = cnt - 1;
}


void build(int l , int r , int id){
    if(l > r)return;
    if(l == r){
        s[id].insert(a[mp[l]]);
    }
    else{
        int m = (l + r) >> 1;
        build(l , m , id << 1);
        build(m + 1 , r , id << 1 | 1);
        for(int i : s[id << 1]){
            s[id].insert(i);
        }
        for(int i : s[id << 1 | 1]){
            s[id].insert(i);
        }
    }
}

void update(int l , int r , int x , int y , int val , int id){
    if(l > r || y < l || x > r)return;
    if(l <= x && y <= r){
        s[id].insert(val);
    }
    else{
        int m = (x + y) >> 1;
        update(l , r , x , m , val , id << 1);
        update(l , r , m + 1 , y , val , id << 1 | 1);
        s[id].insert(val);
    }
}

int query(int l , int r , int x , int y , int val , int id){
    if(l > r || y < l || x > r)return 0;
    if(l <= x && y <= r){
        return s[id].order_of_key(val);
    }
    else{
        int m = (x + y) >> 1;
        int ret = 0;
        ret += query(l , r , x , m , val , id << 1);
        ret += query(l , r , m + 1 , y , val , id << 1 | 1);
        return ret;
    }
}

int main(){
    scanf("%d %d", &N , &Q);
    for(int i = 0; i < N; ++i){
        scanf("%d", &a[i]);
        g[i].clear();
        vis[i] = false;
    }
    for(int i = 0; i < N - 1; ++i){
        int x , y;
        scanf("%d %d", &x , &y);
        g[x].push_back(y);
        g[y].push_back(x);
    }
    cnt = 0;
    DFS(0);
    build(0 , N - 1 , 1);
    for(int q = 1; q <= Q; ++q){
        int v , val;
        scanf("%d %d" , &v , &val);
        printf("%d\n" , query(dfn[v] , R[dfn[v]] , 0 , N - 1 , val , 1));
        update(dfn[v] , dfn[v] , 0 , N - 1 , val , 1);
    }
    return 0;
}
