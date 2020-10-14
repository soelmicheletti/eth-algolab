#include<iostream>
#include<vector>
#include<tuple>
#include<algorithm>
#include<limits.h>

using namespace std; 

bool custom(tuple<int, int> a, tuple<int, int> b){
  if(get<0>(a) < get<0>(b)) return 1; 
  else if(get<0>(a) > get<0>(b)) return 0; 
  else if(get<1>(a) < get<1>(b)) return 0; 
  return 1; 
}

void testcase(){
  int n, m; 
  cin >> n >> m; 
  vector<tuple<int,int>> C; 
  vector<tuple<int, int>> F; 
  
  
  int m_a = INT_MIN; 
  int m_b = INT_MIN; 
  int min_d = INT_MAX;
  int p1_a = INT_MIN;
  int p1_b = INT_MAX;
  int p2_a = INT_MIN;
  int p2_b = INT_MAX;
  for(int i = 0; i < n; i++){
    int a, b;
    cin >> a >> b; 
    if(a > b){
      C.push_back(make_tuple(a, b));
      if(m - a + b < min_d){
        min_d = m - a + b; 
        m_a = a;
        m_b = b; 
      }
      if(a > p1_a){p1_a = a; p1_b = b;}
      if(b < p2_b){p2_b = b; p2_a = a;}
    } 
    else F.push_back(make_tuple(b, a));
  }
  
  sort(F.begin(), F.end(), custom);
  int res1 = 0; 
  int last = 0; 
  for(int i = 0; i < F.size(); i++){
    int beg = get<1>(F[i]);
    int end = get<0>(F[i]);
    if(beg > last){
      last = end; 
      res1++;
    }
  }
  
  int res2 = 1; 
  last = m_b; 
  int first = m_a; 
  for(int i = 0; i < F.size(); i++){
    int beg = get<1>(F[i]);
    int end = get<0>(F[i]);
    if(beg > last && end < first){
      last = end; 
      res2++;
    }
  }
  
  int res3 = 1; 
  last = p1_b; 
  first = p1_a; 
  for(int i = 0; i < F.size(); i++){
    int beg = get<1>(F[i]);
    int end = get<0>(F[i]);
    if(beg > last && end < first){
      last = end; 
      res3++;
    }
  }
  
  int res4 = 1; 
  last = p2_b; 
  first = p2_a; 
  for(int i = 0; i < F.size(); i++){
    int beg = get<1>(F[i]);
    int end = get<0>(F[i]);
    if(beg > last && end < first){
      last = end; 
      res4++;
    }
  }
  
  cout << max(max(res1, res2), max(res3, res4)) << endl; 
}

int main(){
  ios_base::sync_with_stdio(false);
  int t; cin >> t; 
  while(t--) testcase(); 
  return 0; 
}
