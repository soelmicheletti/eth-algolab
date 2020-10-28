#include<iostream>
#include<vector>
#include<algorithm>

using namespace std; 
int num; 

int DFS(vector<vector<int>> &G, vector<bool> &art, vector<int> &low, vector<int> &dfs, vector<vector<int>> &T, int v){
  num++; 
  dfs[v] = num; 
  low[v] = num; 
  art[v] = false; 
  for(int i = 0; i < G[v].size(); i++){
    int w = G[v][i]; 
    if(dfs[w] == -1){
      T[v][w] = 1; 
      int val = DFS(G, art, low, dfs, T, w);
      if(val >= dfs[v]) art[v] = true;
      low[v] = min(low[v], val);
    }
    else if(dfs[w] != -1 && T[v][w] == -1){
      low[v] = min(low[v], dfs[w]);
    }
  }
  return low[v];
}

void testcase(){
  int n, m; 
  cin >> n >> m; 
  vector<vector<int>> G(n); 
  for(int i = 0; i < m; i++){
    int u, v; 
    cin >> u >> v; 
    G[u].push_back(v); 
    G[v].push_back(u);
  }
  vector<bool> art(n, false);
  vector<int> low(n, -1); 
  vector<int> dfs(n, -1);
  vector<vector<int>> T(n, vector<int>(n, -1));
  num = 0;
  
  for(int i = 0; i < n; i++){
    if(dfs[i] == -1){
      DFS(G, art, low, dfs, T, i);
      int cnt = 0; 
      for(int j = 0; j < T[i].size(); j++){
        if(T[i][j] != -1) cnt++;  
      }
      if(cnt >= 2) art[i] = true;
      else art[i] = false; 
    }  
  }
  
  
  bool flag = false;
  for(int i = 0; i < n; i++){
    if(art[i]){flag = true; cout << i << " ";}
  }
  if(flag){
  cout << endl; 
  }
  else cout << -1 << endl; 
}

int main(){
  ios_base::sync_with_stdio(false);
  int t; cin >> t; 
  for(int i = 0; i < t; i++) testcase(); 
  return 0; 
}
