#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;
int n , xc , yc;
double r;

double dis(double x1 , double y1 , double x2 , double y2){
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

int main(){
    while(cin >> n >> xc >> yc >> r){
        vector<int> ret;
        for(int i = 0; i <= n; ++i){
            for(int j = 0; j <= n; ++j){
              if(i - 1 < 0 || j - 1 < 0)continue;
              vector<double> d(4);
              d[0] = dis(xc , yc , i , j);
              d[1] = dis(xc , yc , i , j - 1);
              d[2] = dis(xc , yc , i - 1 , j);
              d[3] = dis(xc , yc , i - 1 , j - 1);
              //check if cut
              int cnt1 = 0 , cnt2 = 0;
              for(int k = 0; k < 4; ++k){
                if(d[k] < r){
                  ++cnt1;
                }
                if(d[k] > r){
                  ++cnt2;
                }
              }
              if(cnt1 > 0 && cnt2 > 0){
                ret.push_back((j - 1) * n + i);
              }
            }
        }
        sort(ret.begin() , ret.end());
        for(int i : ret)cout << i << " ";
        if(ret.size() == 0)cout << -1;
        cout << endl;
    }
}
