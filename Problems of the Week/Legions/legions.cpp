#include<iostream>
#include<vector>
#include<algorithm>
#include<utility>
#include<limits.h>
#include<tuple>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

typedef int IT;
typedef CGAL::Gmpz ET;

typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

using namespace std;

void testcase(){
  
  long xs, ys; 
  cin >> xs >> ys; 
  
  int n; cin >> n; 
  vector<tuple<long, long, long, long>> legions(n); 
  
  for(int i = 0; i < n; i++){
    long a, b, c, v; 
    cin >> a >> b >> c >> v; 
    legions[i] = make_tuple(a, b, c, v);
  }
  
  
  Program lp (CGAL::SMALLER, false, 0, false, 0); 
  
  const int T = 0; 
  const int X = 1; 
  const int Y = 2;
  
  for(int i = 0; i < n; i++){
    if(xs * get<0>(legions[i]) + ys * get<1>(legions[i]) + get<2>(legions[i]) >= 0){
      lp.set_a(T, i, sqrt(get<0>(legions[i]) * get<0>(legions[i]) + get<1>(legions[i]) * get<1>(legions[i])) * get<3>(legions[i]));
      lp.set_a(X, i,  -get<0>(legions[i])); 
      lp.set_a(Y, i, -get<1>(legions[i])); 
      lp.set_b(i, get<2>(legions[i])); 
    }
    else{
      lp.set_a(T, i, sqrt(get<0>(legions[i]) * get<0>(legions[i]) + get<1>(legions[i]) * get<1>(legions[i])) * get<3>(legions[i]));
      lp.set_a(X, i,  get<0>(legions[i])); 
      lp.set_a(Y, i, get<1>(legions[i])); 
      lp.set_b(i, -get<2>(legions[i])); 
    }
  }

  
  lp.set_a(T, n, -1); 
  lp.set_a(X, n, 0); 
  lp.set_a(Y, n, 0); 
  lp.set_b(n, 0); 

  lp.set_c(T, -1);                                       
  lp.set_c0(0);                                          

  // solve the program, using ET as the exact type
  Solution s = CGAL::solve_linear_program(lp, ET());
  ET v = s.objective_value_numerator() / s.objective_value_denominator();

    // output solution
  cout << (long)std::floor(CGAL::to_double(-v)) << "\n";
  
}

int main(){
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for(int i = 0; i < t; i++) testcase();
  return 0;
}
