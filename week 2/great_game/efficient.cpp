#include<iostream>
#include<vector>
#include<utility>
#include<algorithm>
#include<limits.h>

using namespace std; 


void testcase(){
  int n; cin >> n; 
  int m; cin >> m; 
  vector<vector<int>> trans(n + 1); 
  for(int i = 0; i < n + 1; i++){
    vector<int> k; 
    trans[i] = k; 
  }
  int r; cin >> r; 
  int b; cin >> b; 
  for(int i = 0; i < m; i++){
    int u; cin >> u; 
    int v; cin >> v; 
    trans[u].push_back(v); 
  }
  
  vector<int> min(n + 1); 
  vector<int> max(n + 1); 
  for(int i = 0; i < n + 1; i++){
    min[i] = max[i] = -1; 
  }
  
  min[n] = 0; 
  max[n] = 0;
  
  for(int i = n - 1; i >= 0; i--){
    int t = INT_MAX; 
    for(int j = 0; j < trans[i].size(); j++){
     if(max[trans[i][j]] + 1 < t) t = max[trans[i][j]] + 1;  
    }
    min[i] = t; 
    
    t = INT_MIN; 
    for(int j = 0; j < trans[i].size(); j++){
      if(min[trans[i][j]] + 1 > t) t = min[trans[i][j]] + 1; 
    }
    max[i] = t; 
  }
  
  if(min[r] < min[b]) cout << 0 << endl;
  else if(min[b] < min[r]) cout << 1 << endl; 
  else if(min[r] % 2 == 1) cout << 0 << endl;
  else cout << 1 << endl;
  
}

int main(){
  ios_base::sync_with_stdio(false);
  int t; cin >> t; 
  for(int i = 0; i < t; i++){
    testcase();
  }
  return 0; 
}
