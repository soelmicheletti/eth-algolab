#include<iostream>
#include<vector>
#include<utility>
#include<algorithm>
#include<limits.h>

using namespace std; 

int algo(vector<vector<int>> &M, const vector<int> &value, int left, int right, int m, int k){
  if(M[left][right] != -1) return M[left][right]; 
  int n = value.size(); 
  if((n - 1 - right + left) % m == k ){
    if(left == right) return value[left]; 
    int a1 = value[left] + algo(M, value, left + 1, right, m, k); 
    int a2 = value[right] + algo(M, value, left, right - 1, m, k); 
    M[left][right] = max(a1, a2); 
    return M[left][right]; 
  }
  else{
    if(left - right == 0) return 0; 
    int a1 = algo(M, value, left + 1, right, m, k);
    int a2 = algo(M, value, left, right - 1, m, k); 
    M[left][right] = min(a1, a2); 
    return min(a1, a2); 
  }
}

void testcase(){
  int n; cin >> n; 
  int m; cin >> m; 
  int k; cin >> k; 
  
  vector<int> value(n); 
  for(int i = 0; i < n; i++){
    int k; cin >> k; 
    value[i] = k; 
  }
  
  vector<vector<int>> M(n); 
  for(int i = 0; i < n; i++){
    vector<int> k(n); 
    M[i] = k; 
  }
  
  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      M[i][j] = -1; 
    }
  }

  int res = algo(M, value, 0, n - 1, m, k);
  
  cout << res << endl; 
  
}

int main(){
  ios_base::sync_with_stdio(false); 
  int t; cin >> t; 
  for(int i = 0; i < t; i++){
    testcase(); 
  }
  return 0; 
}
