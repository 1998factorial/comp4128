#include <iostream>
#include <cstring>
#include <cstdio>
#include <unordered_map>
using namespace std;
typedef long long ll;

const int maxn = 5e6;
string a;
const ll limit = 1e18;
unordered_map<char , int> mp;

/*
有#就有base
否则若开头为0 则为八进制
0x 或者0X的是16base
什么都没有就是10base
*/

int checkhash(int n){
    for(int i = 0; i < n; ++i)
        if(a[i] == '#')return i;
    return n;
}

int main(){
    int tot = 0;
    for(char i = '0'; i <= '9'; ++i)mp[i] = tot , ++tot;
    for(char i = 'a'; i <= 'z'; ++i)mp[i] = tot , ++tot;
    for(char i = 'A'; i <= 'Z'; ++i)mp[i] = tot , ++tot;
    mp['@'] = tot , ++tot;
    mp['_'] = tot , ++tot;
    cin >> a;
    int n = a.size();
    int h = checkhash(n);
    if(h < n){ // base not decided yet
        ll base;
        for(int i = 0; i < h; ++i)base = base * 10 + a[i] - '0';
            //base found
        ll ret = 0;
        for(int i = h + 1; i < n; ++i){
          ll cur = mp[a[i]];
          if(cur > base){
            cout << "ERROR\n";
            return 0;
          }
          if(ret > (limit - ret) / base ){
            cout << "ERROR\n";
            return 0;
          }
          ret = ret * base + cur;
        }
        cout << ret << endl;
    }
    else{
      if(a[0] == '0'){
        ll base;
        if(a[1] == 'x' || a[1] == 'X')base = 16;
        else base = 8;
        ll ret = 0;
        int e = (base == 8) ? 1 : 2;
        for(int i = e; i < n; ++i){
          ll cur = mp[a[i]];
          if(cur > base){
            cout << "ERROR\n";
            return 0;
          }
          ret = ret * base + cur;
          if(ret > (limit - ret) / base ){
            cout << "ERROR\n";
            return 0;
          }
        }
        cout << ret << endl;
      }
      else{
        if(a.size() > 18)cout << "ERROR\n";
        else cout << a << endl;
      }
    }
    return 0;
}
