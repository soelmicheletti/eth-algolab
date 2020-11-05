#include<iostream>
#include<vector>
#include<algorithm>
#include<utility>

using namespace std; 
int n; 

double algo(vector<vector<double>> &M, vector<double> &p, int s, int k){
  if(k > n - s) return 0; 
  if(s == n) return 1; 
  if(k == 0) return 1; 
  if(M[s][k] != -1) return M[s][k];
  double res = p[s] * algo(M, p, s + 1, k - 1) + (1 - p[s]) * algo(M, p, s + 1, k); 
  M[s][k] = res; 
  return res; 
}

void testcase(){
  int k;
  cin >> n >> k; 
  vector<double> p(n); 
  for(int i = 0; i < n; i++){
    double a; cin >> a; 
    p[i] = a; 
  }
  vector<vector<double>> M(n, vector<double>(k + 1, -1));
  double res = algo(M, p, 0, k); 
  cout << res << endl; 
}

int main(){
  ios_base::sync_with_stdio(false); 
  int t; cin >> t; 
  for(int i = 0; i < t; i++) testcase(); 
  return 0; 
}
