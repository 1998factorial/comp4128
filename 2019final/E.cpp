#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 10;
const int inf = 1e9;
int N , K , Q;
int a[maxn];
bool ban[maxn];
struct node{
    int val , id;
    node(){}
    node(int v , int i) : val(v) , id(i){}
}tree[maxn << 2];
int history[maxn];


node merge(node a , node b){
    node ret;
    if(a.val > b.val){
        ret.val = a.val;
        ret.id = a.id;
    }
    else{
        ret.val = b.val;
        ret.id = b.id;
    }
    return ret;
}

void build(int l , int r , int id){
    if(l > r)return;
    if(l == r){
        tree[id].val = a[l]; tree[id].id = l;
    }
    else{
        int m = (l + r) >> 1;
        build(l , m , id << 1);
        build(m + 1 , r , id << 1 | 1);
        tree[id] = merge(tree[id << 1] , tree[id << 1 | 1]);
    }
}

node query(int l , int r , int x , int y , int id){ //(val , id)
    if(l > r || r < x || l > y)return node(-inf , -1);
    if(l <= x && y <= r){
        return tree[id];
    }
    int m = (x + y) >> 1;
    if(m < l)
        return query(l , r , m + 1 , y , id << 1 | 1);
    if(m >= r)
        return query(l , r , x , m , id << 1);
    return merge(query(l , r , x , m , id << 1) , query(l , r , m + 1 , y , id << 1 | 1));
}

void update(int pos , int l , int r , int id , int ban){
    if(l > r || pos < l || pos > r)return;
    if(pos == l && pos == r){
        if(ban){
            tree[id].val = -inf , tree[id].id = -1;
        }
        else tree[id].val = a[pos] , tree[id].id = pos;
    }
    else{
        int m = (l + r) >> 1;
        update(pos , l , m , id << 1 , ban);
        update(pos , m + 1 , r , id << 1 | 1 , ban);
        tree[id] = merge(tree[id << 1] , tree[id << 1 | 1]);
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N >> K >> Q;
    for(int i = 1; i <= N; ++i)cin >> a[i];
    build(1 , N , 1);
    for(int q = 1; q <= Q; ++q){
        int l , r; cin >> l >> r;
        int lastKban = -1;
        if(q - K - 1 >= 1)lastKban = history[q - K - 1];
        update(lastKban , 1 , N , 1 , 0);
        node ret = query(l , r , 1 , N , 1);
        if(ret.val > 0){
            cout << ret.id << endl;
        }
        else{
            cout << -1 << endl;
        }
        history[q] = ret.id;
        update(ret.id , 1 , N , 1 , 1);
    }
    return 0;
}
