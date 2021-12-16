#include<iostream>
#include<vector>
#include<algorithm>
#include<utility>
#include<limits.h>
#include<cmath>

using namespace std; 

int n; 
int k; 
int m; 
vector<int> fighter; 

int algo(vector<vector<vector<vector<vector<int>>>>> &M, int pos, int last_left, int last_right, int left, int right){
  if(pos == n) return 0; 
  if(M[pos][last_left][last_right][left][right] != -1) return M[pos][last_left][last_right][left][right]; 
  if(last_left == k && last_right == k){
    int first = 1000 - pow(2, abs(left + 1 - right)) + algo(M, pos + 1, fighter[pos], last_right, left + 1, right);
    int second = 1000 - pow(2, abs(left - right - 1)) + algo(M, pos + 1, last_left, fighter[pos], left, right + 1); 
    M[pos][last_left][last_right][left][right] = max(first, second); 
    return max(first, second); 
  }
  else if(last_left == k){
    int first = 1000 - pow(2, abs(left + 1 - right)) + algo(M, pos + 1, fighter[pos], last_right, left + 1, right);
    int second = 0; 
    if(last_right == fighter[pos]) second = 1000 - pow(2, abs(left - right - 1)) + algo(M, pos + 1, last_left, fighter[pos], left, right + 1); 
    else second = 2000 - pow(2, abs(left - right - 1)) + algo(M, pos + 1, last_left, fighter[pos], left, right + 1); 
    M[pos][last_left][last_right][left][right] = max(first, second); 
    return max(first, second); 
  }
  else if(last_right == k){
    int first = 0; 
    if(last_left == fighter[pos]) first = 1000 - pow(2, abs(left + 1 - right)) + algo(M, pos + 1, fighter[pos], last_right, left + 1, right); 
    else first = 2000 - pow(2, abs(left + 1 - right)) + algo(M, pos + 1, fighter[pos], last_right, left + 1, right); 
    int second = 1000 - pow(2, abs(left - right - 1)) + algo(M, pos + 1, last_left, fighter[pos], left, right + 1); 
    M[pos][last_left][last_right][left][right] = max(first, second); 
    return max(first, second); 
  }
  else{
    int first = 0; 
    if(last_left == fighter[pos]) first = 1000 - pow(2, abs(left + 1 - right)) + algo(M, pos + 1, fighter[pos], last_right, left + 1, right); 
    else first = 2000 - pow(2, abs(left + 1 - right)) + algo(M, pos + 1, fighter[pos], last_right, left + 1, right); 
    int second = 0; 
    if(last_right == fighter[pos]) second = 1000 - pow(2, abs(left - right - 1)) + algo(M, pos + 1, last_left, fighter[pos], left, right + 1); 
    else second = 2000 - pow(2, abs(left - right - 1)) + algo(M, pos + 1, last_left, fighter[pos], left, right + 1); 
    M[pos][last_left][last_right][left][right] = max(first, second); 
    return max(first, second); 
  }
}

int algo1(vector<vector<vector<vector<vector<vector<int>>>>>> &M, int pos, int left1, int left2, int right1, int right2, int diff){
  if(pos == n) return 0; 
  if(diff >= 0 && M[pos][left1][left2][right1][right2][diff] != -1) return M[pos][left1][left2][right1][right2][diff]; 
  else if(diff < 0 && M[pos][left1][left2][right1][right2][n - diff] != -1) return M[pos][left1][left2][right1][right2][n - diff];
  int first = 0; 
  int left3 = fighter[pos];
  if(left1 != left2 && left1 != left3 && left2 != left3 && left1 != k) first = 3000 - pow(2, abs(diff + 1)) + algo1(M, pos + 1, left2, left3, right1, right2, diff + 1);
  else if(left1 != left2 && left1 != left3 && left2 != left3 && left1 == k) first = 2000 - pow(2, abs(diff + 1)) + algo1(M, pos + 1, left2, left3, right1, right2, diff + 1); 
  else if(left1 != left2 && left1 != left3 && left2 == left3 && left1 != k) first = 2000 - pow(2, abs(diff + 1)) + algo1(M, pos + 1, left2, left3, right1, right2, diff + 1); 
  else if(left1 != left2 && left1 != left3 && left2 == left3 && left1 == k) first = 1000 - pow(2, abs(diff + 1)) + algo1(M, pos + 1, left2, left3, right1, right2, diff + 1); 
  else if(left1 != left2 && left1 == left3 && left2 != left3) first = 2000 - pow(2, abs(diff + 1)) + algo1(M, pos + 1, left2, left3, right1, right2, diff + 1); 
  else if(left1 == left2 && left1 != left3 && left2 != left3 && left1 != k) first = 2000 - pow(2, abs(diff + 1)) + algo1(M, pos + 1, left2, left3, right1, right2, diff + 1); 
  else if(left1 == left2 && left1 != left3 && left2 != left3 && left1 == k) first = 1000 - pow(2, abs(diff + 1)) + algo1(M, pos + 1, left2, left3, right1, right2, diff + 1); 
  else if(left1 == left2 && left1 == left3 && left2 == left3) first = 1000 - pow(2, abs(diff + 1)) + algo1(M, pos + 1, left2, left3, right1, right2, diff + 1); 
  
  
  int second = 0;
  int right3 = fighter[pos]; 
  if(right1  != right2 && right1  != right3 && right2 != right3 && right1  != k) second = 3000 - pow(2, abs(diff - 1)) + algo1(M, pos + 1, left1, left2, right2, right3, diff - 1); 
  else if(right1  != right2 && right1  != right3 && right2 != right3 && right1  == k) second = 2000 - pow(2, abs(diff - 1)) + algo1(M, pos + 1, left1, left2, right2, right3, diff - 1); 
  else if(right1  != right2 && right1  != right3 && right2 == right3 && right1  != k) second = 2000 - pow(2, abs(diff - 1)) + algo1(M, pos + 1, left1, left2, right2, right3, diff - 1); 
  else if(right1  != right2 && right1  != right3 && right2 == right3 && right1  == k) second = 1000 - pow(2, abs(diff - 1)) + algo1(M, pos + 1, left1, left2, right2, right3, diff - 1); 
  else if(right1  != right2 && right1  == right3 && right2 != right3) second = 2000 - pow(2, abs(diff - 1)) + algo1(M, pos + 1, left1, left2, right2, right3, diff - 1);  
  else if(right1  == right2 && right1  != right3 && right2 != right3 && right1  != k) second = 2000 - pow(2, abs(diff - 1)) + algo1(M, pos + 1, left1, left2, right2, right3, diff - 1); 
  else if(right1  == right2 && right1  != right3 && right2 != right3 && right1  == k) second = 1000 - pow(2, abs(diff - 1)) + algo1(M, pos + 1, left1, left2, right2, right3, diff - 1); 
  else if(right1  == right2 && right1  == right3 && right2 == right3) second = 1000 - pow(2, abs(diff - 1)) + algo1(M, pos + 1, left1, left2, right2, right3, diff - 1); 
  
  if(diff >= 0) M[pos][left1][left2][right1][right2][diff] = max(first, second);
  else M[pos][left1][left2][right1][right2][n - diff] = max(first, second); 
  return max(first, second); 
}

void testcase(){
  cin >> n >> k >> m;
  fighter.clear(); fighter.resize(n, 0); 
  for(int i = 0; i < n; i++) cin >> fighter[i]; 
  if(m == 2){
  vector<vector<int>> primo(n + 1, vector<int>(n + 1, -1)); 
  vector<vector<vector<int>>> secondo(k + 1, primo); 
  vector<vector<vector<vector<int>>>> terzo(k + 1, secondo); 
  vector<vector<vector<vector<vector<int>>>>> M(n + 1, terzo); 
  cout << algo(M, 0, k, k, 0, 0) << endl; 
  }
  else{
  vector<int> primo(2 * (n + 1), -1); 
  vector<vector<int>> secondo(k + 1, primo); 
  vector<vector<vector<int>>> terzo(k + 1, secondo);
  vector<vector<vector<vector<int>>>> quarto(k + 1, terzo); 
  vector<vector<vector<vector<vector<int>>>>> quinto(k + 1, quarto); 
  vector<vector<vector<vector<vector<vector<int>>>>>> M(n + 1, quinto);
  cout << algo1(M, 0, k, k, k, k, 0) << endl; 
  }
}

int main(){
  ios_base::sync_with_stdio(false); 
  int t; cin >> t; 
  for(int i = 0; i < t; i++) testcase(); 
  return 0; 
}
