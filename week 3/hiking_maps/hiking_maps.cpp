#include<iostream>
#include<vector>
#include<tuple>
#include<limits.h>
#include<algorithm>
#include<queue>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P;
typedef K::Segment_2 S;
typedef K::Line_2 L;
typedef K::Triangle_2 T;


using namespace std; 

bool contains(const vector<P> &t, const P &p){
  return !CGAL::right_turn(t[0], t[1], p) && !right_turn(t[2], t[3], p) && !right_turn(t[4], t[5], p);
}

void testcase(){
  int m, n; 
  cin >> m >> n; 
  
  vector<P> path(m); 
  for(int i = 0; i < m; i++){
    int x, y; 
    cin >> x >> y; 
    path[i] = P(x, y); 
  }
  
  vector<vector<P>> triangle(n); 
  for(int i = 0; i < n; i++){
    vector<P> k(6); 
    for(int j = 0; j < 6; j++){
      int a; cin >> a; 
      int b; cin >> b; 
      k[j] = P(a, b); 
    }
    for(int j = 0; j < 6; j+=2){
      if(CGAL::right_turn(k[j], k[j+1], k[(j+2)%6])) swap(k[j], k[j+1]);
    }
    triangle[i] = k;
  }
  
  vector<vector<int>> S(m - 1);
  vector<int> lunghezza(m - 1, 0); 
  
  for(int i = 0; i < n; i++){
    for(int j = 0; j < m - 1; j++){
      if(contains(triangle[i], path[j]) && contains(triangle[i], path[(j + 1) % m])){
        S[j].push_back(i);
        lunghezza[j]++;
      }
    }
  }
  
  vector<int> p(m - 1, 0); 
  priority_queue<tuple<int, int>, vector<tuple<int, int>>, greater<tuple<int, int>>> Q;
  
  for(int i = 0; i < m - 1; i++){
    Q.push(make_tuple(S[i][0], i));
  }
  
  int max = INT_MIN; 
  for(int i = 0; i < m - 1; i++){
    if(S[i][0] > max){
      max = S[i][0];
    }
  }
  int min = INT_MAX; 
  while(p[get<1>(Q.top())] < lunghezza[get<1>(Q.top())]){
   // cout << "max " << max << " min " << get<0>(P.top()) << " id " << get<1>(P.top()) << endl;
    int now = max - get<0>(Q.top()) + 1; 
    if(now < min){
      min = now; 
    }
    p[get<1>(Q.top())]++; 
    if(S[get<1>(Q.top())][p[get<1>(Q.top())]] > max){
      max = S[get<1>(Q.top())][p[get<1>(Q.top())]];
    }
    int pos = get<1>(Q.top());
    int val = S[get<1>(Q.top())][p[get<1>(Q.top())]];
    Q.pop();
    if(p[pos] == lunghezza[pos]) break;
    Q.push(make_tuple(val, pos));
  }
  
  cout << min << endl;
  
}

int main(){
  int t; cin >> t; 
  for(int i = 0; i < t; i++){
    testcase(); 
  }
  return 0; 
}
