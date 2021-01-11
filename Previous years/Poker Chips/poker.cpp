#include<iostream>
#include<vector>
#include<limits.h>
#include<utility>
#include<algorithm>

using namespace std; 

int n; 
vector<int> size; 
vector<vector<int>> A; 
vector<vector<int>> M; 
vector<vector<vector<vector<vector<int>>>>> N; 

int algo2(int f, int s){
 // cout << f << " " << s << endl; 
  if(f < 0 || s < 0) return 0; 
  if(M[f][s] != -1) return M[f][s]; 
  if(A[0][f] == A[1][s]){
    int first = algo2(f - 1, s); 
    int second = algo2(f, s - 1); 
    int third = 1 + algo2(f - 1, s - 1);
    M[f][s] = max(max(first, second), third);
    return max(max(first, second), third); 
  }
  else{
    int first = algo2(f - 1, s); 
    int second = algo2(f, s - 1); 
    M[f][s] = max(first, second); 
    return max(first, second); 
  }
}

int algo(int a, int b, int c, int d, int e){
  int res = 0; 
  int i1 = (a == -1) ? size[0] : a; 
  int i2 = (b == -1) ? size[1] : b; 
  int i3 = (c == -1) ? size[2] : c; 
  int i4 = (d == -1) ? size[3] : d; 
  int i5 = (e == -1) ? size[4] : e; 
  if(N[i1][i2][i3][i4][i5] != -1) return N[i1][i2][i3][i4][i5]; 
 // cout << a << " " << b << " " << c << " " << d << " " << e << endl; 
  if(a != -1) res = max(res, algo(a - 1, b, c, d, e)); 
  if(b != -1) res = max(res, algo(a, b - 1, c, d, e)); 
  if(c != -1) res = max(res, algo(a, b, c - 1, d, e)); 
  if(d != -1) res = max(res, algo(a, b, c, d - 1, e)); 
  if(e != -1) res = max(res, algo(a, b, c, d, e - 1)); 
  
  if(a != -1 && b != -1 && A[0][a] == A[1][b]) res = max(res, 1 + algo(a - 1, b - 1, c, d, e)); 
  if(a != -1 && c != -1 && A[0][a] == A[2][c]) res = max(res, 1 + algo(a - 1, b, c - 1, d, e));
  if(a != -1 && d != -1 && A[0][a] == A[3][d]) res = max(res, 1 + algo(a - 1, b, c, d - 1, e));
  if(a != -1 && e != -1 && A[0][a] == A[4][e]) res = max(res, 1 + algo(a - 1, b, c, d, e - 1));
  if(b != -1 && c != -1 && A[1][b] == A[2][c]) res = max(res, 1 + algo(a, b  - 1, c - 1, d, e));
  if(b != -1 && d != -1 && A[1][b] == A[3][d]) res = max(res, 1 + algo(a, b - 1, c, d - 1, e));
  if(b != -1 && e != -1 && A[1][b] == A[4][e]) res = max(res, 1 + algo(a, b - 1, c, d, e - 1));
  if(c != -1 && d != -1 && A[2][c] == A[3][d]) res = max(res, 1 + algo(a, b, c - 1, d - 1, e));
  if(c != -1 && e != -1 && A[2][c] == A[4][e]) res = max(res, 1 + algo(a, b, c - 1, d, e - 1));
  if(d != -1 && e != -1 && A[3][d] == A[4][e]) res = max(res, 1 + algo(a, b, c, d - 1, e - 1));
  
  if(a != -1 && b != -1 && c != -1 && A[0][a] == A[1][b] && A[0][a] == A[2][c]) res = max(res, 2 + algo(a - 1, b - 1, c - 1, d, e)); 
  if(a != -1 && b != -1 && d != -1 && A[0][a] == A[1][b] && A[0][a] == A[3][d]) res = max(res, 2 + algo(a - 1, b - 1, c, d - 1, e)); 
  if(a != -1 && b != -1 && e != -1 && A[0][a] == A[1][b] && A[0][a] == A[4][e]) res = max(res, 2 + algo(a - 1, b - 1, c, d, e - 1)); 
  if(a != -1 && c != -1 && d != -1 && A[0][a] == A[2][c] && A[0][a] == A[3][d]) res = max(res, 2 + algo(a - 1, b, c - 1, d - 1, e)); 
  if(a != -1 && c != -1 && e != -1 && A[0][a] == A[2][c] && A[0][a] == A[4][e]) res = max(res, 2 + algo(a - 1, b, c - 1, d, e - 1)); 
  if(a != -1 && d != -1 && e != -1 && A[0][a] == A[3][d] && A[0][a] == A[4][e]) res = max(res, 2 + algo(a - 1, b, c, d - 1, e -1)); 
  if(b != -1 && c != -1 && d != -1 && A[1][b] == A[2][c] && A[1][b] == A[3][d]) res = max(res, 2 + algo(a, b - 1, c - 1, d - 1, e)); 
  if(b != -1 && c != -1 && e != -1 && A[1][b] == A[2][c] && A[1][b] == A[4][e]) res = max(res, 2 + algo(a, b - 1, c - 1, d, e - 1)); 
  if(b != -1 && d != -1 && e != -1 && A[1][b] == A[3][d] && A[1][b] == A[4][e]) res = max(res, 2 + algo(a, b - 1, c, d - 1, e - 1)); 
  if(c != -1 && d != -1 && e != -1 && A[2][c] == A[3][d] && A[2][c] == A[4][e]) res = max(res, 2 + algo(a, b, c - 1, d - 1, e - 1)); 
  
  if(a != -1 && b != -1 && c != -1 && d != -1 && A[0][a] == A[1][b] && A[0][a] == A[2][c] && A[0][a] == A[3][d]) res = max(res, 4 + algo(a - 1, b - 1, c - 1, d - 1, e)); 
  if(a != -1 && b != -1 && c != -1 && e != -1 && A[0][a] == A[1][b] && A[0][a] == A[2][c] && A[0][a] == A[4][e]) res = max(res, 4 + algo(a - 1, b - 1, c - 1, d, e - 1)); 
  if(a != -1 && b != -1 && d != -1 && e != -1 && A[0][a] == A[1][b] && A[0][a] == A[3][d] && A[0][a] == A[4][e]) res = max(res, 4 + algo(a - 1, b - 1, c, d - 1, e - 1)); 
  if(a != -1 && c != -1 && d != -1 && e != -1 && A[0][a] == A[2][c] && A[0][a] == A[3][d] && A[0][a] == A[4][e]) res = max(res, 4 + algo(a - 1, b, c - 1, d - 1, e - 1)); 
  if(b != -1 && c != -1 && d != -1 && e != -1 && A[1][b] == A[2][c] && A[1][b] == A[3][d] && A[1][b] == A[4][e]) res = max(res, 4 + algo(a, b - 1, c - 1, d - 1, e- 1)); 
  
  if(a != -1 && b != -1 && c != -1 && d != -1 && e != -1 && A[0][a] == A[1][b] && A[0][a] == A[2][c] && A[0][a] == A[3][d] && A[0][a] == A[4][e]) res = max(res, 8 + algo(a - 1, b - 1, c - 1, d - 1, e - 1));  
  
  N[i1][i2][i3][i4][i5] = res; 
  return res; 
}

void testcase(){
  cin >> n; 
  size.clear(); size.resize(5, 0); 
  A.clear(); A.resize(n); 
  for(int i = 0; i < n; i++) cin >> size[i]; 
  for(int i = 0; i < n; i++){
    for(int j = 0; j < size[i]; j++){
      int k; cin >> k; 
      A[i].push_back(k); 
    }
  }
  
   
  if(n < 2) cout << 0 << endl; 
  else if(n == 2){
    M.clear(); M.resize(size[0] + 1, vector<int>(size[1] + 1, -1));
    cout << algo2(size[0] - 1, size[1] - 1) << endl;
  }
  else{
    if(n == 3){
      N.clear(); N.resize(size[0] + 1, vector<vector<vector<vector<int>>>>(size[1] + 1, vector<vector<vector<int>>>(size[2] + 1, vector<vector<int>>(2, vector<int>(1, -1))))); 
      cout << algo(size[0] - 1, size[1] - 1, size[2] - 1, -1, -1) << endl; ; 
    }
    else if(n == 4){
      N.clear(); N.resize(size[0] + 1, vector<vector<vector<vector<int>>>>(size[1] + 1, vector<vector<vector<int>>>(size[2] + 1, vector<vector<int>>(size[3] + 1, vector<int>(2, -1))))); 
      cout << algo(size[0] - 1, size[1] - 1, size[2] - 1, size[3] -1, -1) << endl;
    }
    else if(n == 5){
      N.clear(); N.resize(size[0] + 1, vector<vector<vector<vector<int>>>>(size[1] + 1, vector<vector<vector<int>>>(size[2] + 1, vector<vector<int>>(size[3] + 1, vector<int>(size[4] + 1, -1))))); 
      cout << algo(size[0] - 1, size[1] - 1, size[2] - 1, size[3] - 1, size[4] - 1) << endl;
    }
  }
  
  
}
int main(){
  ios_base::sync_with_stdio(false); 
  int t; cin >> t; 
  for(int i = 0; i < t; i++) testcase(); 
  return 0; 
}
