#include<iostream>
#include<vector>
#include<algorithm>
#include<stack>

using namespace std; 

int algo(vector<vector<int>> &G, int u, vector<int> M){
  if(M[u] != -1) return M[u]; 
  if(G[u].empty()){M[u] = 0; return 0; }
  bool flag = false; 
  for(int i = 0; i < G[u].size(); i++){
    if(algo(G, G[u][i], M) == 0){
      flag = true; 
    }
  }
  if(flag){
    M[u] = 1; return 1; 
  }
  else{
    M[u] = 0; return 0; 
  }
}

void testcase(){
  int n; cin >> n; 
  vector<vector<int>> G(n);
  for(int i = 0; i < n; i++){
    int d; cin >> d; 
    for(int j = 0; j < d; j++){
      int u; cin >> u; 
      G[i].push_back(u); 
    }
  }
  
  vector<int> M(n, -1); 
  int res = algo(G, 0, M); 
  if(res == 1) cout << "A" << endl; 
  else cout << "B" << endl; 
  
}

int main(){
  ios_base::sync_with_stdio(false); 
  int t; cin >> t; 
  for(int i = 0; i < t; i++) testcase(); 
  return 0; 
}
