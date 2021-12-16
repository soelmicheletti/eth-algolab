#include<iostream>
#include<vector>
#include<algorithm>
#include<tuple>
#include<limits.h>
#include<utility>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <iomanip>

using namespace std; 

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::Edge_iterator  Edge_iterator;

void testcase(int n){
  cout << fixed << setprecision(0);
  vector<K::Point_2> pts;
  pts.reserve(n);
  for (int i = 0; i < n; ++i) {
    int x, y; 
    cin >> x >> y; 
    pts.push_back(K::Point_2(x, y));
  }
  Triangulation t;
  t.insert(pts.begin(), pts.end());
  
  int m; cin >> m; 
  
  for(int i = 0; i < m; i++){
    int x, y; 
    cin >> x >> y; 
    K::FT d = CGAL::squared_distance(K::Point_2(x, y),t.nearest_vertex(K::Point_2(x, y))->point()); 
    cout << d << endl;
  }
  
}

int main(){
  ios_base::sync_with_stdio(false); 
  while(true){
    int n; cin >> n; 
    if(n == 0) break; 
    testcase(n); 
  }
  return 0; 
}
