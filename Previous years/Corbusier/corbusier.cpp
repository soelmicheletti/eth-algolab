#include<iostream>
#include<vector>
#include<algorithm>
#include<utility>
#include<limits.h>

using namespace std; 

int n; 
int l; 
int k; 
vector<int> D; 
vector<vector<int>> M; 

bool algo(int l, int k, int p){
  if(p == n) return false; 
  if(M[l][p] != -1) return M[l][p];
  if(D[p] % k == l) return true; 
  bool first = algo(l, k, p + 1); 
  bool second = false; 
  if(l >= D[p]) second = algo((l - D[p]) % k, k, p + 1); 
  else second = algo(k - (D[p] - l) % k, k, p + 1);
  M[l][p] = first || second; 
  return first || second; 
}

void testcase(){
  cin >> n >> l >> k; 
  D.clear(); D.resize(n, 0);  
  M.clear(); M.resize(k + 1, vector<int>(n + 1, -1)); 
  for(int i = 0; i < n; i++) cin >> D[i]; 
  if(algo(l, k, 0)) cout << "yes" << endl; 
  else cout << "no" << endl; 
}

int main(){
  ios_base::sync_with_stdio(false); 
  int t; cin >> t; 
  for(int i = 0; i < t; i++) testcase(); 
  return 0;
}
