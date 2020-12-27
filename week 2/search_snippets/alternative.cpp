#include<iostream>
#include<vector>
#include<algorithm>
#include<utility>
#include<limits.h>

using namespace std; 

void testcase(){
  int n; cin >> n; 
  vector<int> nums(n, 0); 
  for(int i = 0; i < n; i++) cin >> nums[i]; 
  vector<pair<int, int>> A; 
  
  for(int i = 0; i < n; i++){
    for(int j = 0; j < nums[i]; j++){
      int p; cin >> p; 
      A.push_back({p, i}); 
    }
  }
  
  sort(A.begin(), A.end()); 
  int q = 0;
  vector<int> C(n, 0); 
  
  int l = 0; 
  int r = 0; 
  int best = INT_MAX; 
  bool flag = true; 
  while(r < A.size()){
    if(flag && C[A[r].second] == 0) q++; 
    if(flag) C[A[r].second]++; 
    if(r != l && A[r].second == A[l].second){
      C[A[r].second]--; 
      l++; 
      if(l > r) r = l; 
      flag = false; 
    }
    if(q == n){
      if(A[r].first - A[l].first + 1 < best){
        best = A[r].first - A[l].first + 1;
       // cout << "l = " << A[l].second << " " << A[l].first << endl; 
      //  cout << "r = " << A[r].second << " " << A[r].first << endl;
      //  cout << best << endl; 
      }  
      C[A[l].second]--; 
      if(C[A[l].second] == 0) q--; 
      l++; 
      if(l > r) r = l; 
      flag = false; 
    }
    else{flag = true; r++;}
  }
  
  cout << best << endl; 
}

int main(){
  ios_base::sync_with_stdio(false); 
  int t; cin >> t; 
  for(int i = 0; i < t; i++) testcase(); 
  return 0; 
}
