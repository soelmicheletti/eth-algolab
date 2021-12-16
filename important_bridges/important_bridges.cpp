#include<iostream>
#include<vector>
#include<tuple>
#include<algorithm>
#include<stack>

using namespace std; 
int num; 
int bridge; 
vector<tuple<int, int>> bridges; 

int DFSVisit(const vector<vector<int>> &G, vector<int> & dfs, vector<int> &low, vector<bool> &vis, int v, int cmp) {
    num++; 
    dfs[v] = num;   
    low[v] = dfs[v]; 
    vis[v] = true; 
    for(int i = 0; i < G[v].size(); i++) {
      if(G[v][i] == cmp){}
      else if(vis[G[v][i]]){
        low[v] = min(low[v], dfs[G[v][i]]);
      }
      else{
        int val = DFSVisit(G, dfs, low, vis, G[v][i], v); 
        low[v] = min(low[v], val); 
        if(low[G[v][i]] > dfs[v]){
          bridge++; 
          if(v <= G[v][i]) bridges.push_back(make_tuple(v, G[v][i]));
          else bridges.push_back(make_tuple(G[v][i], v)); 
        }
      }
    }
 //   cout << "v = " << v << " dfs[v] = " << dfs[v] << " low[v] = " << low[v] << endl; 
    return low[v]; 
}

void testcase(){
  int n, m; 
  cin >> n >> m; 
  vector<vector<int>> G(n);
  for(int i = 0; i < n; i++){vector<int> k; G[i] = k;}
  for(int i = 0; i < m; i++){
    int u, v; 
    cin >> u >> v; 
    G[u].push_back(v); 
    G[v].push_back(u); 
  }
  
  vector<int> dfs(n, 0); 
  vector<int> low(n, 0);
  vector<bool> vis(n, false); 
  num = 0; 
  bridge = 0; 
  bridges.clear(); 
  for(int i = 0; i < n; i++){
    if(dfs[i] == 0){
        DFSVisit(G, dfs, low, vis, i, i); 
    }    
  }
  sort(bridges.begin(), bridges.end()); 
  
  cout << bridge <<"\n";
  for(int i = 0; i < bridges.size(); i++){
    cout << get<0>(bridges[i]) << " " << get<1>(bridges[i]) << endl; 
  }
}

int main(){
  ios_base::sync_with_stdio(false);
  int t; cin >> t; 
  while(t--)testcase();
  return 0; 
}
