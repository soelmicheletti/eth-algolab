#include<iostream>
#include<vector>

using namespace std; 

int main(){
  ios_base::sync_with_stdio(false); 
  int n; 
  cin >> n; 
  vector<vector<int>> M(n, vector<int>(n, -1)); 
  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      int k; cin >> k; 
      M[i][j] = k; 
    }
  }
  vector<vector<int>> P(n + 1, vector<int>(n + 1, 0));
  for(int i = 1; i <= n; i++){
    P[1][i] = P[1][i - 1] + M[0][i - 1];
    P[i][1] = P[i - 1][1] + M[i - 1][0];
  }
  for(int i = 2; i <= n; i++){
    for(int j = 2; j <= n; j++){
      P[i][j] = P[i - 1][j] + P[i][j - 1] - P[i - 1][j - 1] + M[i - 1][j - 1];
    }
  }
  
  int t; cin >> t;
  for(int i = 0; i < t; i++){
    int a, b, c, d; 
    cin >> a >> b >> c >> d; 
    int res = (P[b][d] - P[a - 1][d] - P[b][c - 1] + P[a - 1][c - 1]);
    cout << res << endl; 
  }
}
