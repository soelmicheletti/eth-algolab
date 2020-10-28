#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>

using namespace std; 

void testcase(){
  int n, m, r; 
  cin >> n >> m >> r; 
  vector<vector<int>> G(n);
  for(int i = 0; i < m; i++){
    int u, v; 
    cin >> u >> v; 
    G[u].push_back(v);
    G[v].push_back(u);
  }
  vector<bool> blue(n, false);
  vector<bool> red(n, false);
  queue<int> Q; 
  Q.push(0);
  blue[0] = true; 
  bool res = true;
  while(!Q.empty()){
    int u = Q.front();
    Q.pop();
    for(int i = 0; i < G[u].size(); i++){
      int v = G[u][i];
      if(blue[u]){
        if(blue[v]) res = false;
        else if(!red[v]){red[v] = true; Q.push(v);}
      }
      else if(red[u]){
        if(red[v]) res = false;
        else if(!blue[v]){blue[v] = true; Q.push(v);}
      }
    }
  }
  
  if(!res){
    cout << "no" << endl;
  }
  else{
    if(red[r]){
      for(int i = 0; i < n; i++){
        if(red[i]) cout << i << " ";
      }
    }
    else if(blue[r]){
      for(int i = 0; i < n; i++){
        if(blue[i]) cout << i << " ";
      }
    }
    cout << endl;
  }
}

int main(){
  ios_base::sync_with_stdio(false);
  int t; cin >> t; 
  for(int i = 0; i < t; i++) testcase();
  return 0; 
}
