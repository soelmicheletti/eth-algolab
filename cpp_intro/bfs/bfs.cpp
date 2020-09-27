#include<iostream>
#include<vector>
#include<queue>

using namespace std; 

void testcase(){
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

    int d[n]; 
    for(int i = 0; i < n; i++){
        d[i] = -1; 
    }
    d[v] = 0;     
    queue<int> Q; 
    Q.push(v); 
    while(!Q.empty()){
        int u = Q.front(); 
        Q.pop(); 
        for(int i = 0; i < G.at(u).size(); i++){
            int e = G.at(u).at(i); 
            if(d[e] == -1){
                d[e] = d[u] + 1; 
                Q.push(e); 
            }
        }
    }

    for(int i = 0; i < n; i++){
        cout << d[i] << " "; 
    }
    cout << endl; 
}

int main(){
    ios_base::sync_with_stdio(false);
    int t; cin >> t; 
    for(int i = 0; i < t; i++){
        testcase(); 
    }
    return 0; 
}
