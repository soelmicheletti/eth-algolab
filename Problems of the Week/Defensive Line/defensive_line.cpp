#include<iostream>
#include<vector>
#include<tuple>
#include<algorithm>
#include<utility>
#include<limits.h>

using namespace std; 

int algo(vector<vector<int>> &M, const vector<int> &I, int m, int p){
  if(m == 0){int h = I.size(); int k = min(p, h - 1); M[m][k] = 0; return 0;} 
  if(p > I.size() - 1){return INT_MIN;} 
  if(M[m][p] != -1) return M[m][p];
  if(I[p] == -1){
    int S = algo(M, I, m, p + 1); 
    M[m][p] = S; 
    return S; 
  }
  else{
    int first = I[p] - p + 1 + algo(M, I, m - 1, I[p] + 1); 
    int second = algo(M, I, m, p + 1); 
    int S = max(first, second); 
    M[m][p] = S; 
    return max(first, second); 
  }
}

void testcase(){
  int n; cin >> n; 
  int m; cin >> m; 
  int k; cin >> k; 
  
  vector<int> v(n); 
  for(int i = 0; i < n; i++){
    int k; cin >> k; 
    v[i] = k; 
  }
  
  vector<int> I(n, -1); 
  
  int l = 0; int r = 0; 
  int sum = v[0]; 
  while(l < n && r < n){
   // cout << l << " " << r << " " << sum << endl; 
    if(sum < k){
      r++; 
      if(r < n) sum += v[r];
    }
    else if(sum > k){
      sum -= v[l]; 
      l++;
    }
    else if(sum == k){
      I[l] = r;
      if(l == r){ l++; r++; sum = v[l]; } 
      else{sum -= v[l]; l++;}
    }
  }
  
  vector<vector<int>> M(m + 1, vector<int>(n, -1));
  
 
  
  int res = algo(M, I, m, 0);

  for(int i = 0; i <= m; i++){
    for(int j = 0; j < n; j++){
   //   cout << M[i][j] << " ";
    }
    //cout << endl; 
  }
  if(res < 0){
    cout << "fail" << endl; 
  }
  else{
    cout << res << endl; 
  }
}


int main(){
  ios_base::sync_with_stdio(false);
  int t; cin >> t; 
  for(int i = 0; i < t; i++){
    testcase(); 
  }
}
