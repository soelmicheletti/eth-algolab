#include<iostream>
#include<vector>
#include<algorithm>
#include<limits.h>

using namespace std; 

void testcase(){
  int n, D; 
  cin >> n >> D; 
  vector<int> pos(n + 1); 
  vector<int> e(n + 1); 
  for(int i = 1; i <= n; i++){
    int k; cin >> k; 
    pos[i] = k; 
  }
  for(int i = 1; i <= n; i++){
    int k; cin >> k; 
    e[i] = k; 
  }
  e[0] = 0; 
  pos[0] = INT_MIN;
  vector<int> res(n + 1, 0); 
  res[0] = 0;
  res[1] = e[0]; 
  int p = 0; 
  
  for(int i = 1; i <= n; i++){
   // cout << i << " " << p << endl; 
    while(pos[p + 1] + D <= pos[i]) p++; 
    res[i] = max(res[i - 1], res[p] + e[i]);
  }
  
  cout << res[n] << endl; 
}

int main(){
  ios_base::sync_with_stdio(false);
  int t; cin >> t; 
  for(int i = 0; i < t; i++) testcase(); 
}
