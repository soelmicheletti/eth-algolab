#include<iostream>
#include<vector>
#include<utility>
#include<algorithm>
#include<limits.h>

using namespace std; 

int algo(vector<vector<vector<int>>> &M, const vector<int> &value, int left, int right, int m, int k, int turn){
  if(M[left][right][k] != -1) return M[left][right][k]; 
  int n = value.size(); 
  if(left == right && turn == k) return value[left]; 
  else if(left == right) return 0; 
  if(turn == k){
    int a1 = value[left] + algo(M, value, left + 1, right, m, k, (turn + 1) % m); 
    int a2 = value[right] + algo(M, value, left, right - 1, m, k, (turn + 1) % m);
    int res = max(a1, a2);
    M[left][right][k] = res; 
    return res; 
  }
  else{
    int a1 = algo(M, value, left + 1, right, m, k, (turn + 1) % m); 
    int a2 = algo(M, value, left, right - 1, m, k, (turn + 1) % m); 
    int res = min(a1, a2); 
    M[left][right][k] = res; 
    return res; 
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
  
  vector<vector<vector<int>>> M(n, vector<vector<int>>(n, vector<int>(2, -1)));
  
  int res = algo(M, value, 0, n - 1, m, k, 0);
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
