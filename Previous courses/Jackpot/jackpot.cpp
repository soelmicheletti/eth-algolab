#include<iostream>
#include<vector>
#include<limits.h>
#include<tuple>
#include<algorithm>
#include<utility>

using namespace std; 

int n; 
int k; 

double algo(vector<vector<double>> &M, vector<vector<int>> &A, int l, int pref){
  if(l == n) return 1; 
  double res = 0; 
  for(int i = 0; i < k; i++){
    if(A[l][i] >= pref){
      if(M[l][i] != -1) res += M[l][i];
      else{
        double tmp = (1.0 / k) * algo(M, A, l + 1, A[l][i]);
        M[l][i] = tmp;
        res += tmp;
      }
    }
  }
  return res; 
}

void testcase(){
  cin >> n >> k; 
  vector<vector<int>> A(n, vector<int>(k, -1)); 
  for(int i = 0; i < n; i++){
    for(int j = 0; j < k; j++){
      int a; cin >> a; 
      A[i][j] = a; 
    }
  }
  vector<vector<double>> M(n, vector<double>(k, -1));
  double res = algo(M, A, 0, INT_MIN);
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
