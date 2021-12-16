#include<iostream>
#include<vector>
#include<limits.h>
#include<algorithm>
#include<utility>
#include<tuple>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>

using namespace std; 

typedef int IT;
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef int                                            Index;
typedef CGAL::Triangulation_vertex_base_with_info_2<Index,K>   Vb;
typedef CGAL::Triangulation_face_base_2<K>                     Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Triangulation;
typedef K::Point_2 P; 

void testcase(){
  int z, u, v, w, a, g; 
  cin >> z >> u >> v >> w >> a >> g; 
  
  vector<pair<P, int>> gang(g);  
  vector<tuple<int, int, int, int>> G(g); 
  for(int i = 0; i < g; i++){
    int x; int y; int u; int v; int w; 
    cin >> x >> y >> u >> v >> w; 
    gang[i] = {P(x,y), i};
    G[i] = make_tuple(INT_MAX, u, v, w);
  }
  
  Triangulation T; 
  T.insert(gang.begin(), gang.end()); 
  
  for(int i = 0; i < a; i++){
    int x; int y; int z; 
    cin >> x >> y >> z; 
    auto v = T.nearest_vertex(P(x, y));
    int index = v -> info(); 
    get<0>(G[index]) = min(get<0>(G[index]), z); 
  }
  
  Program lp (CGAL::SMALLER, true, 0, true, 24); 
  int cnt = 0; 
  for(int i = 0; i < g; i++){
    if(get<0>(G[i]) == INT_MAX) continue; 
    lp.set_a(cnt, 0, -get<1>(G[i])); 
    lp.set_a(cnt, 1, -get<2>(G[i]));
    lp.set_a(cnt, 2, -get<3>(G[i]));
    lp.set_c(cnt, get<0>(G[i]));
    cnt++; 
  }
  lp.set_b(0, -u);
  lp.set_b(1, -v); 
  lp.set_b(2, -w); 

  Solution s = CGAL::solve_linear_program(lp, ET());
  if(s.is_infeasible() || s.objective_value() > z) cout << "H" << endl; 
  else cout << "L" << endl; 
}

int main(){
  ios_base::sync_with_stdio(false); 
  int t; cin >> t; 
  for(int i = 0; i < t; i++) testcase(); 
  return 0; 
}
