#include<iostream>
#include<vector>
#include<limits.h>
#include<algorithm>
#include<tuple>

using namespace std; 

/*int algo(vector<vector<vector<int>>> &M, vector<int> &surface, vector<int> &weight, vector<int> &price, int S, int W, int p, int res){
  if(p >= surface.size() && S <= 0) return res;
  if(p >= surface.size()) return INT_MIN;
  if(M[p][max(S, 0)][W] >=  0){return M[p][max(S, 0)][W];}
  if(weight[p] > W){int tmp = algo(M, surface, weight, price, S, W, p + 1, res); M[p][max(S, 0)][W] = tmp; return tmp;}
  int first = algo(M, surface, weight, price, S - surface[p], W - weight[p], p + 1, res + price[p]);
  int second = algo(M, surface, weight, price, S, W, p + 1, res); 
  M[p][min(S, 0)][W] = max(first, second);
  return max(first, second);
}*/

void testcase(){
  int n, S, W; 
  cin >> n >> S >> W; 
  vector<int> surface(n); 
  vector<int> weight(n); 
  vector<int> price(n); 
  vector<vector<vector<int>>> M(n + 1, vector<vector<int>>(S + 1, vector<int>(W + 1, INT_MIN  )));
  for(int i = 0; i < n; i++){
    int s, w, p; 
    cin >> s >> w >> p; 
    surface[i] = s; 
    weight[i] = w; 
    price[i] = p; 
  }
  
  for(int i = 0; i <= W; i++) M[0][0][i] = 0;
  
  for(int i = 1; i <= n; i++){
    for(int j = 0; j <= S; j++){
      for(int k = 0; k <= W; k++){
        if(k >= weight[i - 1]){
          M[i][j][k] = max(price[i - 1] + M[i - 1][max(0, j - surface[i - 1])][k - weight[i - 1]], M[i - 1][j][k]);
        }
        else M[i][j][k] = M[i - 1][j][k]; 
      }
    }
  }
  
  cout << M[n][S][W] << endl;
}

int main(){
  ios_base::sync_with_stdio(false); 
  int t; cin >> t; 
  for(int i = 0; i < t; i++) testcase(); 
  return 0; 
}
