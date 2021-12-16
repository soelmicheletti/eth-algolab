#include<iostream>
#include<vector>
#include<utility>
#include<algorithm>
#include<limits.h>

using namespace std; 

vector<int> W; 
vector<bool> vis; 
vector<int> LL; 
vector<int> CC; 
vector<int> NN; 

int L(vector<vector<int>> &G, int u);
int C(vector<vector<int>> &G, int u);
int N(vector<vector<int>> &G, int u);

int N(vector<vector<int>> &G, int u){
  if(NN[u] != -1) return NN[u];
  int first = W[u]; 
  for(int i = 0; i < G[u].size(); i++) first += L(G, G[u][i]);
  NN[u] = first; 
  return first; 
}

int C(vector<vector<int>> &G, int u){
 if(CC[u] != -1) return CC[u];
 int first = W[u]; 
  int second = INT_MAX; 
  for(int i = 0; i < G[u].size(); i++){
      first += L(G, G[u][i]);  
  }
  vector<int> loc_n(G[u].size());
  vector<int> loc_c(G[u].size());
  int part = 0; 
  for(int i = 0; i < G[u].size(); i++){
    loc_n[i] = N(G, G[u][i]);
    loc_c[i] = C(G, G[u][i]);
    part += loc_c[i];
  }
  for(int i = 0; i < G[u].size(); i++){
    second = min(second, part - loc_c[i] + loc_n[i]);
  }
  CC[u] = min(first, second); 
  return min(first, second); 
}

int L(vector<vector<int>> &G, int u){
  if(LL[u] != -1) return LL[u];
  int first = W[u]; 
  int second = 0; 
  for(int i = 0; i < G[u].size(); i++){
      first += L(G, G[u][i]);  
      second += C(G, G[u][i]);
  }
  LL[u] = min(first, second);
  return min(first, second); 
}

void testcase(){
  int n; cin >> n; 
  vector<vector<int>> G(n);
  for(int i = 0; i < n - 1; i++){
    int u, v; 
    cin >> u >> v; 
    G[u].push_back(v); 
  }
  
  W.clear(); 
  W.resize(n, 0); 
  vis.clear(); 
  vis.resize(n, false); 
  for(int i = 0; i < n; i++){
    int k; cin >> k; 
    W[i] = k; 
  }
  LL.clear(); LL.resize(n, -1);
  NN.clear(); NN.resize(n, -1);
  CC.clear(); CC.resize(n, -1);
  cout << C(G, 0) << endl; 
}

int main(){
  ios_base::sync_with_stdio(false); 
  int t; cin >> t; 
  for(int i = 0; i < t; i++) testcase(); 
  return 0; 
}
