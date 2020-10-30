#include<iostream>
#include<vector>
#include<algorithm>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

using namespace std; 

typedef int IT;
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;


void testcase(int n, int d){
  Program lp (CGAL::SMALLER, false, 0, false, 0); 
  
  for(int i = 0; i < n; i++){
    double sum = 0; 
    for(int j = 0; j < d; j++){
      int a; cin >> a; 
      lp.set_a(j, i, a);
      sum += a * a; 
    }
    lp.set_a(d, i, floor(sqrt(sum)));
    int b; cin >> b; 
    lp.set_b(i, b); 
  }
  for(int i = 0; i < d; i++) lp.set_a(i, n, 0);
  lp.set_a(d, n, -1);
  lp.set_b(n, 0);
  lp.set_c(d, -1);
  lp.set_c0(0);                                         

  Solution s = CGAL::solve_linear_program(lp, ET());
  if(s.is_infeasible()) cout << "none" << endl; 
  else if(s.is_unbounded()) cout << "inf" << endl; 
  else{
    CGAL::Quotient<ET> res = s.objective_value();
    cout << -1 * res.numerator() / res.denominator() << endl;
  }
}

int main(){
  ios_base::sync_with_stdio(false); 
  while(true){
    int n; cin >> n; 
    if(n == 0) break; 
    int d; cin >> d; 
    testcase(n, d);
  }
  return 0; 
}
