#include<iostream>
#include<vector>
#include<tuple>
#include<algorithm>
#include<limits.h>

using namespace std; 
int x; 

long algo(vector<vector<long>> &M, vector<vector<tuple<int, long>>> &A, vector<bool> &restart, int s, int k){
  if(k == 0) return 0; 
  if(M[s][k] != -1){return M[s][k];}
  if(restart[s]){long nuovo = algo(M, A, restart, 0, k); M[s][k] = nuovo; return nuovo;}
  else{
    long best = 0;
    for(int i = 0; i < A[s].size(); i++){
        best = max(best, algo(M, A, restart, get<0>(A[s][i]), k - 1) + get<1>(A[s][i]));
    }
    M[s][k] = best;
    return best; 
  }
}

void testcase(){
  int n, m;
  long x, k; 
  cin >> n >> m >> x >> k; 
  vector<vector<tuple<int,long>>> A(n); 
  vector<bool> restart(n, true);  
  vector<vector<long>> M(n, vector<long>(k + 1, -1));
  for(int i = 0; i < m; i++){
    int u, v;
    long p;
    cin >> u >> v >> p; 
    A[u].push_back(make_tuple(v, p));
    restart[u] = false;
  }
  
  int c = 1;
  while(c <= k && algo(M, A, restart, 0, c) < x){
    c++;
  }
  
  if(c <= k) cout << c << endl; 
  else cout << "Impossible" << endl;
}

int main(){
  ios_base::sync_with_stdio(false); 
  int t; cin >> t; 
  for(int i = 0; i < t; i++){
    testcase(); 
  }
  return 0; 
}
