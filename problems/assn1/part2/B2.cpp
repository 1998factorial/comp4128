#include <iostream>
#include <vector>
using namespace std;
typedef pair<int , int> ii;

const int maxn = 1e5 + 10;
int N , Q;
struct query{
  int c; //0->add , 1->query
  int a , b; //node a and b
  int start , end; //only for add
  query(){}
  query(int c_ , int a_ , int b_ , int s_ , int e_) : c(c_) , a(a_) , b(b_) , start(s_) , end(e_) {}
}qs[maxn];
vector<ii> tree[maxn << 2];
// for each segment tree node , store the edges that are legal for this range
int ans[maxn];
// store answer for each query
vector<int> a[maxn];
vector<int> csize[maxn];
vector<ii> q;

//from part 2 a

int find(int x){
  return a[x].back() == x ? x : find(a[x].back());
}

void undo(){
  int x = q.back().first;
  int y = q.back().second;
  q.pop_back();
  a[x].pop_back();
  a[y].pop_back();
  csize[x].pop_back();
  csize[y].pop_back();
}

void add(int x , int y){
  x = find(x);
  y = find(y);
  if(x != y){ // different ancestor
    if(csize[x].back() > csize[y].back())swap(x , y); //link the smaller one to larger one
    a[x].push_back(y);
    a[y].push_back(y);
    int sx = csize[x].back() , sy = csize[y].back();
    csize[x].push_back(sx + sy);
    csize[y].push_back(sx + sy);
  }
  else {
    a[x].push_back(x);
    a[y].push_back(y);
    csize[x].push_back(csize[x].back());
    csize[y].push_back(csize[y].back());
  }
  q.emplace_back(x , y);
}

void DFS(int id , int l , int r){
  if(l > r)return;
  int cnt = 0;
  for(auto& it : tree[id]){
    add(it.first , it.second);
    ++cnt;
  }
  if(l == r){
    if(qs[l].c)
      ans[l] = find(qs[l].a) == find(qs[l].b);
  }
  else{
    int mid = (l + r) >> 1;
    DFS(id << 1 , l , mid);
    DFS(id << 1 | 1 , mid + 1 , r);
  }
  while(cnt){
    undo();
    --cnt;
  }
}

void update(int l , int r , int x , int y , int a , int b , int id){
  if(l > r || x > y || l > y || r < x)return;
  if(l <= x && y <= r){
    tree[id].emplace_back(a , b);
  }
  else{
    int mid = (x + y) >> 1;
    update(l , r , x , mid , a , b , id << 1);
    update(l , r , mid + 1 , y , a , b , id << 1 | 1);
  }
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> Q;
  for(int i = 1; i <= Q; ++i){
    char op;
    cin >> op;
    if(op == 'A'){
      int x , y;
      cin >> x >> y;
      qs[i] = query(0 , x , y , i , Q);
    }
    else if(op == 'D'){
      int x;
      cin >> x;
      qs[x].end = i;
    }
    else{
      int x , y;
      cin >> x >> y;
      qs[i] = query(1 , x , y , 0 , 0);
    }
    ans[i] = -1;
  }
  for(int i = 1; i <= Q * 2; ++i)tree[i].clear();
  for(int i = 1; i <= N; ++i){
    a[i].clear();
    a[i].push_back(i);
    csize[i].clear();
    csize[i].push_back(1);
  }
  for(int i = 1; i <= Q; ++i){
    if(qs[i].c == 0){
      //add into segment tree node
      update(qs[i].start , qs[i].end , 1 , Q , qs[i].a , qs[i].b , 1);
    }
  }
  q.clear();
  DFS(1 , 1 , Q);
  for(int i = 1; i <= Q; ++i){
    if(ans[i] != -1)
      cout << ans[i] << endl;
  }
}
