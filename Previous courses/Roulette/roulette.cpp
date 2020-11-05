#include<iostream>
#include<vector>
#include<limits.h>
#include<utility>
#include<algorithm>

using namespace std; 

int initial_k;

double algo(vector<vector<double>> &M, int m, int k, double p){
  if(m == 0 && k == 0) return 0;
  if(m == 1 && k > 1) return 0;
  if(m == 1 && k == 1) return p; 
  if(k <= 0) return 1; 
  if(m == 0) return 0; 
  if(M[m][k] != -1) return M[m][k];
  double res = p * algo(M, m - 1, k - 1, p) + (1 - p) * algo(M, m - 1, initial_k, p); 
  M[m][k] = res; 
  return res; 
}

void testcase(){
  int n, m, k; 
  cin >> n >> m >> k; 
  initial_k = k;
  double count = 0; 
  for(int i = 0; i < n; i++){
    int k; cin >> k; 
    if(k == 0) count++; 
  }
  
  double p = count / n; 
  vector<vector<double>> M(m + 1, vector<double>(k + 1, - 1));
  
  double res = algo(M, m, k, p); 
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
