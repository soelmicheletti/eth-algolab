#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <boost/pending/disjoint_sets.hpp>
#include <vector>
#include <tuple>
#include <algorithm>
#include <iostream>

using namespace std; 

int n; 
int m; 
vector<double> p; 
vector<vector<double>> M; 

double algo(int pos, int k){
  if(k >= m) return 1; 
  if(pos == n && k < m) return 0; 
  if(M[pos][k] != -1.0) return M[pos][k];
  double res = 0; 
  for(int i = 0; i <= k; i++){
    double nuovo = p[pos] * algo(pos + 1, k + i) + (1.0 - p[pos]) * algo(pos + 1, k - i);
    res = max(res, nuovo); 
  }
  M[pos][k] = res; 
  return res; 
}

void testcase(){
  cin >> n; int k; cin >> k; cin >> m; 
  p.clear(); p.resize(n); 
  for(int i = 0; i < n; i++){
    double l; cin >> l; p[i] = l; 
  }
  M.clear(); M.resize(n, vector<double>(m + 1, -1.0)); 
  cout << algo(0, k) << endl; 
  
}

int main(){
  ios_base::sync_with_stdio(false); 
  std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(5);
  int t; cin >> t;
  for(int i = 0; i < t; i++) testcase(); 
  return 0; 
}
