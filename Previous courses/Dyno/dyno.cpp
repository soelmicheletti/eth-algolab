#include<iostream>
#include<vector>
#include<limits.h>

using namespace std; 



int algo(vector<int> &M, int L, int D, int C, vector<bool> &cacti, int p){
  if(p >= L) return L; 
  if(M[p] != -1) return M[p];
  int first = p; 
  int second = p; 
  if(p + 1 < L && !cacti[p + 1]){
    first = algo(M, L, D, C, cacti, p + 1);
  }
  if(p + D < L && !cacti[p + D]){
    second = algo(M, L, D, C, cacti, p + D);
  }
  M[p] = max(first, second); 
  return max(first, second); 
}

void testcase(){
  int L, D, C; 
  cin >> L >> D >> C; 
  vector<bool> cacti(L, false); 
  for(int i = 0; i < C; i++){
    int k; cin >> k; 
    cacti[k] = true; 
  }
  vector<int> M(L, -1); 
  int res = algo(M, L, D, C, cacti, 0); 
  cout << res << endl; 
}

int main(){
  ios_base::sync_with_stdio(false);
  int t; cin >> t; 
  for(int i = 0; i < t; i++) testcase(); 
  return 0; 
}
