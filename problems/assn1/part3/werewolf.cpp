#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
typedef pair<int , int> ii;

const int maxn = 2e5 + 10;
vector<int> g[maxn];
vector<int> hightree[maxn]; // v greater than all child
vector<int> lowtree[maxn]; // v less than all child
int N , M , Q;
int ans[maxn];
int tree[maxn << 2];

struct unionset{
  int parent[maxn];
  void init(){
    for(int i = 1; i <= N; ++i)parent[i] = i;
  }

  int find(int x){
    return parent[x] == x ? x : parent[x] = find(parent[x]);
  }
}highH , lowH;

struct sTree{
  vector<int> t[maxn];
  int dfn[maxn];
  int tot;
  int right[maxn];
  int idfn[maxn];
  int up[maxn][20];
  int L;

  int jump(int start , int val , int high){
    int ret = start;
    if(high){
      for(int i = L; i >= 0; --i){
        if(up[ret][i] <= val)
          ret = up[ret][i];
      }
    }
    else{
      for(int i = L; i >= 0; --i){
        if(up[ret][i] >= val)
          ret = up[ret][i];
      }
    }
    return ret;
  }

  void DFS2(int v , int p){
    up[v][0] = p;
    for(int i = 1; i <= L; ++i)
      up[v][i] = up[up[v][i - 1]][i - 1];
    for(int u : t[v]){
      if(u != p)
        DFS2(u , v);
    }
  }

  void DFS(int v){ //DFS for dfs order , to turn tree into interval
    dfn[v] = ++tot;
    idfn[dfn[v]] = v;
    for(int u : t[v]){
      if(dfn[u] == -1){
        DFS(u);
      }
    }
    right[dfn[v]] = tot;
  }

  void process(int high){
    for(int i = 1; i <= N; ++i)dfn[i] = -1 , right[i] = -1 , idfn[i] = -1;
    tot = 0;
    // turn tree into interval by dfs order
    if(high)DFS(N);
    else DFS(1);
    L = ceil(log2(N));
    for(int i = 1; i <= N; ++i)
      for(int j = 0; j <= L; ++j)
        up[i][j] = 0;
    // calculate up[i][j]
    if(high)DFS2(N , N);
    else DFS2(1 , 1);
  }

  void init(){
    for(int i = 1; i <= N; ++i)t[i].clear();
  }

  void add(int x , int y){
    t[x].push_back(y);
  }

  void show(){
    for(int i = 1; i <= N; ++i){
      cout << i << " : ";
      for(int j : t[i]){
        cout << j << " ";
      }
      cout << endl;
    }
  }

}highT , lowT;

struct Query{
  int xl , xr , yl , yr , id;
  Query(){}
  Query(int a_ , int b_ , int c_ , int d_ , int e_): xl(a_) , xr(b_) , yl(c_) , yr(d_) , id(e_) {}
  bool operator < (const Query& other) const {
    return xr < other.xr;
  }
};

void build(int l , int r , int id){
  if(l > r)return;
  if(l == r){
    tree[id] = 0;
  }
  else{
    int m = (l + r) >> 1;
    build(l , m , id << 1);
    build(m + 1 , r , id << 1 | 1);
    tree[id] = max(tree[id << 1] , tree[id << 1 | 1]);
  }
}

void update(int pos , int x , int y , int val , int id){
  if(pos < x || pos > y)return;
  if(x == pos && y == pos){
    tree[id] = max(tree[id] , val);
  }
  else{
    int m = (x + y) >> 1;
    update(pos , x , m , val , id << 1);
    update(pos , m + 1 , y , val , id << 1 | 1);
    tree[id] = max(tree[id << 1] , tree[id << 1 | 1]);
  }
}

int query(int l , int r , int x , int y , int id){
  if(l <= x && y <= r){
    return tree[id];
  }
  int m = (x + y) >> 1;
  if(m < l)
    return query(l , r , m + 1 , y , id << 1 | 1);
  if(m >= r)
    return query(l , r , x , m , id << 1);
  return max(query(l , r , x , m , id << 1) , query(l , r , m + 1 , y , id << 1 | 1));
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> M >> Q;
  for(int i = 1; i <= N; ++i)g[i].clear() , hightree[i].clear() , lowtree[i].clear();
  for(int i = 1; i <= M; ++i){
    int x , y;
    cin >> x >> y;
    ++x , ++y;
    g[x].push_back(y);
    g[y].push_back(x);
  }
  highH.init() , lowH.init();
  highT.init() , lowT.init();
  // build heap structure , where v is greater than all its child
  for(int i = 1; i <= N; ++i){ //for each connected component , parent is the maximal
    for(int j : g[i]){
      if(i > j){
        int y = highH.find(j); // y is maximal node in j's component
        if(i != y)highH.parent[y] = i , highT.add(i , y);
      }
    }
  }
  // build heap structure , where v is smaller than all its child
  for(int i = N; i >= 1; --i){ // for each connected component , parent is the minimal
    for(int j : g[i]){
      if(i < j){
        int y = lowH.find(j); // y is minimal node in j's component
        if(i != y)lowH.parent[y] = i , lowT.add(i , y);
      }
    }
  }
  highT.process(1);
  lowT.process(0);
  vector<ii> pos;
  for(int i = 1; i <= N; ++i){
    pos.emplace_back(highT.dfn[i] , lowT.dfn[i]); // (x , y)
  }
  vector<Query> qs;
  for(int i = 1; i <= Q; ++i){
    // for each S E L R , we can use binary flip to get subtree in logn
    // then the problem is turned into , given 2 permutations of 1 ... N
    // for [l1 , r1] , [l2 , r2] , if they have common element ?
    int S , E , L , R;
    cin >> S >> E >> L >> R;
    ++S , ++E , ++L , ++R;
    int v = highT.jump(E , R , 1); // jump from E , towards R
    int u = lowT.jump(S , L , 0); // jump from S , towards L
    int L1 = highT.dfn[v] , R1 = highT.right[highT.dfn[v]] , L2 = lowT.dfn[u] , R2 = lowT.right[lowT.dfn[u]];
    qs.emplace_back(L1 , R1 , L2 , R2 , i);
    //(xl , xr , yl , yr)
  }
  sort(pos.begin() , pos.end());
  sort(qs.begin() , qs.end());
  build(1 , N , 1);
  int j = 0;
  for(int i = 0; i < Q; ++i){
    while(j < N && pos[j].first <= qs[i].xr){
      update(pos[j].second , 1 , N , pos[j].first , 1);
      ++j;
    }
    int ret = query(qs[i].yl , qs[i].yr , 1 , N , 1);
    ans[qs[i].id] = ret >= qs[i].xl;
  }
  for(int i = 1; i <= Q; ++i){
    cout << ans[i] << endl;
  }
}
