#include<iostream>
#include<vector>
#include<limits.h>
#include<queue>
#include<tuple>
#include<algorithm>
#include <bits/stdc++.h> 

using namespace std;

void testcase(){
  int n; cin >> n; 
  vector<vector<int>> S(n); 
  vector<int> lunghezza(n); 
  for(int i = 0; i < n; i++){
    int k; cin >> k; 
    vector<int> nuovo(k); 
    S[i] = nuovo; 
    lunghezza[i] = k; 
  }
  
  for(int i = 0; i < n; i++){
    for(int j = 0; j < lunghezza[i]; j++){
      int k; cin >> k; 
      S[i][j] = k; 
    }
  }
  vector<int> p(n); 
  for(int i = 0; i < n; i++){
    p[i] = 0; 
  }
  int min = INT_MAX; 
  
  priority_queue<tuple<int, int>, vector<tuple<int, int>>, greater<tuple<int, int>>> P; 
  
  for(int i = 0; i < n; i++){
    P.push(make_tuple(S[i][0], i));
  }

  
  int max = INT_MIN; 
  for(int i = 0; i < n; i++){
    if(S[i][0] > max){
      max = S[i][0];
    }
  }
  

  while(p[get<1>(P.top())] < lunghezza[get<1>(P.top())]){
   // cout << "max " << max << " min " << get<0>(P.top()) << " id " << get<1>(P.top()) << endl;
    int now = max - get<0>(P.top()) + 1; 
    if(now < min){
      min = now; 
    }
    p[get<1>(P.top())]++; 
    if(S[get<1>(P.top())][p[get<1>(P.top())]] > max){
      max = S[get<1>(P.top())][p[get<1>(P.top())]];
    }
    int pos = get<1>(P.top());
    int val = S[get<1>(P.top())][p[get<1>(P.top())]];
    P.pop();
    if(p[pos] == lunghezza[pos]) break;
    P.push(make_tuple(val, pos));
  }

  cout << min << endl;
}



int main(){
  ios_base::sync_with_stdio(false); 
  int t; cin >> t; 
  for(int i = 0; i < t; i++){
    testcase(); 
  }
  return 0; 
}
