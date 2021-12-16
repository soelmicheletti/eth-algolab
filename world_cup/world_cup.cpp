#include<iostream>
#include<vector>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

using namespace std; 

typedef double IT;
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef K::Point_2 P; 
typedef CGAL::Quotient<ET> SolT;

long floor_to_double(const SolT& x){
  double a = std::floor(CGAL::to_double(x));
  while(a+1<=x) ++a;
  while(a>x) --a;
  return a;
}

void testcase(){
  int n, m, c; 
  cin >> n >> m >> c; 
  vector<long> S(n); 
  vector<long> A(n); 
  vector<P> pos_w(n);
  vector<P> all;
  for(int i = 0; i < n; i++){
    long x, y, s, a; 
    cin >> x >> y >> s >> a; 
    P p(x, y); 
    pos_w[i] = p; 
    all.push_back(p);
    S[i] = s; 
    A[i] = a; 
  }
  vector<long> D(m); 
  vector<long> U(m); 
  vector<P> pos_c(m); 
  for(int i = 0; i < m; i++){
    long x, y, d, u; 
    cin >> x >> y >> d >> u; 
    P p(x, y); 
    pos_c[i] = p; 
    all.push_back(p);
    D[i] = d; 
    U[i] = u; 
  }
  vector<vector<double>> rev(n, vector<double>(m, -1));
  for(int i = 0; i < n; i++){
    for(int j = 0; j < m; j++){
      double k; cin >> k; 
      rev[i][j] = k * 100;
    }
  }
  
  Triangulation T;
  T.insert(all.begin(), all.end());
  for(int z = 0; z < c; z++){
    long x, y;
    long r; 
    cin >> x >> y >> r; 
    P p(x, y); 
    auto nearest = T.nearest_vertex(p);
    if(CGAL::squared_distance(p, nearest -> point()) > r * r) continue;
   for(int i = 0; i < n; i++){
      for(int j = 0; j < m; j++){
        bool first = CGAL::squared_distance(p, pos_w[i]) <= r * r; 
        bool second = CGAL::squared_distance(p, pos_c[j]) <= r * r; 
        if(first != second) rev[i][j] -= 1;
      }
    }
  }
   // create an LP with Ax <= b, lower bound 0 and no upper bounds
  Program lp (CGAL::SMALLER, true, 0, false, 0); 
  
  vector<vector<double>> v(n, vector<double>(m, -1)); 
  int tmp = 0; 
  for(int i = 0; i < n; i++){
    for(int j = 0; j < m; j++){
      v[i][j] = tmp++; 
    }
  }
  int constraint = 0; 
  for(int i = 0; i < n; i++){
    for(int j = 0; j < m; j++){
      lp.set_a(v[i][j],constraint, 1); 
    }
   lp.set_b(constraint, S[i]);
    constraint++; 
  }
  
  for(int i = 0; i < m; i++){
    for(int j = 0; j < n; j++){
      lp.set_a(v[j][i], constraint, A[j]);
    }
    lp.set_b(constraint, U[i] * 100); 
    constraint++; 
  }
  
  for(int i = 0; i < m; i++){
    for(int j = 0; j < n; j++){
      lp.set_a(v[j][i], constraint, -1); 
    }
    lp.set_b(constraint, -D[i]); 
    constraint++; 
  }
  
  for(int i = 0; i < m; i++){
    for(int j = 0; j < n; j++){
      lp.set_a(v[j][i], constraint, 1); 
    }
    lp.set_b(constraint, D[i]); 
    constraint++; 
  }
  
  for(int i = 0; i < n; i++){
    for(int j = 0; j < m; j++){
      lp.set_c(v[i][j], -rev[i][j]); 
    }
  }
  lp.set_c0(0);                                          

  Solution s = CGAL::solve_nonnegative_linear_program(lp, ET());
  if(s.is_infeasible()){
    cout << "RIOT!" << std::endl;  
  }
  else {
    cout << floor_to_double(-s.objective_value() / 100) << std::endl;
  }
}

int main(){
 ios_base::sync_with_stdio(false); 
 int t; cin >> t; 
 for(int i = 0; i < t; i++) testcase(); 
 return 0; 
}
