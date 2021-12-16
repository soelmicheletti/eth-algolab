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

void primo(int a, int b){
  Program lp (CGAL::SMALLER, true, 0, false, 0); 
  
  const int X = 0; 
  const int Y = 1;
  lp.set_a(X, 0,  1); lp.set_a(Y, 0, 1); lp.set_b(0, 4);  
  lp.set_a(X, 1, 4); lp.set_a(Y, 1, 2); lp.set_b(1, a * b);
  lp.set_a(X, 2, -1); lp.set_a(Y, 2, 1); lp.set_b(2, 1);
  lp.set_c(Y, -1 * b);
  lp.set_c(X, a);
  lp.set_c0(0);                                          // +64

  Solution s = CGAL::solve_linear_program(lp, ET());
  if(s.is_infeasible()) cout << "no" << endl; 
  else{
    CGAL::Quotient<ET> res = s.objective_value();
    cout << -1 * res.numerator() / res.denominator() << endl;
  }   
}

void secondo(int a, int b){
  Program lp (CGAL::SMALLER, false, 0, true, 0); 
  
  const int X = 0; 
  const int Y = 1;
  const int Z = 2; 
  lp.set_a(X, 0,  -1); lp.set_a(Y, 0, -1); lp.set_a(Z, 0, 0); lp.set_b(0, 4);  
  lp.set_a(X, 1, -4); lp.set_a(Y, 1, -2); lp.set_a(Z, 1, -1); lp.set_b(1, a * b);
  lp.set_a(X, 2, 1); lp.set_a(Y, 2, -1); lp.set_a(Z, 2, 0); lp.set_b(2, 1);
  lp.set_c(Y, b);
  lp.set_c(X, a);
  lp.set_c(Z, 1);
  lp.set_c0(0);                                         

  Solution s = CGAL::solve_linear_program(lp, ET());
  if(s.is_infeasible()) cout << "no" << endl; 
  else if(s.is_unbounded()) cout << "unbounded" << endl; 
  else{
    CGAL::Quotient<ET> res = s.objective_value();
    cout << res.numerator() / res.denominator() << endl;
  }   
}

int main(){
  ios_base::sync_with_stdio(false); 
  while(true){
    int p; cin >> p; 
    if(p == 0) break; 
    int a, b; cin >> a >> b; 
    if(p == 1) primo(a, b); 
    else if(p == 2) secondo(a, b);
  }
}
