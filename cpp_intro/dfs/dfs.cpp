#include<iostream>
#include<stack>
#include<vector>
#include <bits/stdc++.h> 

using namespace std; 

void testcase(){
    
    // READ INPUT IN GRAPH G
    
    int n; cin >> n; 
    int m; cin >> m; 
    int v; cin >> v; 

    vector<vector<int>> G; 
    for(int i = 0; i < n; i++){
        vector<int> tmp; 
        G.push_back(tmp);
    }
    
    for(int i = 0; i < m; i++){
        int a; cin >> a; 
        int b; cin >> b; 
        G.at(a).push_back(b); 
        G.at(b).push_back(a);
    }
    
    for(int i = 0; i < n; i++){
      sort(G.at(i).begin(), G.at(i).end());
    }
    
    // SOLVES THE PROBLEM

    int in[n]; 
    int out[n]; 
    for(int i = 0; i < n; i++){
        in[i] = -1; 
        out[i] = -1; 
    }
    stack<int> S; 
    S.push(v); 
    int t = 0; 
    while(!S.empty()){
      int w = S.top();
      if(in[w] == -1){
        in[w] = t;
        t++;
        for(int i = G.at(w).size() - 1; i >= 0; i--){
          int x = G.at(w).at(i);
          if(in[x] == -1){
            S.push(x);
          }
        }
      } else{
        S.pop();
        if(out[w] == -1){
            out[w] = t;
            t++;
        }
      }
    }

    for(int i = 0; i < n; i++){
        cout << in[i] << " "; 
    }
    cout << endl; 

    for(int i = 0; i < n; i++){
        cout << out[i] << " "; 
    }
    cout << endl;

/*    for(int i = 0; i < n; i++){
        cout << "Nodo " << i << endl; 
        for(int j = 0; j < G.at(i).size(); j++){
            cout << G.at(i).at(j) << " " ; 
        }
        cout << endl; 
    }
*/
}

int main(){
    int t; cin >> t; 
    for(int i = 0; i < t; i++){
        testcase();
    }
}
