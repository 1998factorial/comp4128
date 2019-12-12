#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll mod = 1e9 + 7;
int N , M;
const int maxn = 1e5 + 10;
int K;

struct edge{
    int x , y , w;
    edge(){}
    edge(int x_ , int y_ , int w_) : x(x_) , y(y_) , w(w_){}
    bool operator < (const edge& other) const {
        return w < other.w;
    }
};
vector<edge> edges;

int a[maxn];

int find(int x){
    return (a[x] == x) ? x : a[x] = find(a[x]);
}

void add(int x , int y){
    x = find(x);
    y = find(y);
    if(x != y)a[x] = y;
}

int MST(){
    sort(edges.begin() , edges.end());
    for(int i = 1; i <= N; ++i)a[i] = i;
    int ret = 0;
    for(edge& e : edges){
        int x = e.x , y = e.y , c = e.w;
        if(find(x) != find(y)){
            add(x , y);
            ret += c;
        }
    }
    return ret;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N >> M >> K;
    for(int i = 1; i <= M; ++i){
        int x , y , z; cin >> x >> y >> z;
        edges.emplace_back(x , y , z);
    }
    int ret = MST();
    cout << ret << endl;
} 
