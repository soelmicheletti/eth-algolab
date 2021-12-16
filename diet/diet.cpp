#include<iostream>
#include<vector>
#include<algorithm>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

typedef int IT;
typedef CGAL::Gmpz ET;

typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

using namespace std; 

void testcase(int n, int m){
  
  vector<int> lower_bound(n, -1); 
  vector<int> upper_bound(n, -1); 
  vector<int> price(m, -1);
  vector<vector<int>> M(n, vector<int>(m, -1));
  
  for(int i = 0; i < n; i++){
    int a, b; 
    cin >> a >> b; 
    lower_bound[i] = a; 
    upper_bound[i] = b; 
  }
  
  for(int i = 0; i < m; i++){
    int p; cin >> p; 
    price[i] = p;
    for(int j = 0; j < n; j++){
      int a; cin >> a; 
      M[j][i] = a; 
    }
  }
  
  Program lp (CGAL::SMALLER, true, 0, false, 0); 
    
  
  for(int i = 0; i < n; i++){
    for(int j = 0; j < m; j++){
      lp.set_a(j, 2 * i, M[i][j]); 
    }
    lp.set_b(2 * i, upper_bound[i]);
    for(int j = 0; j < m; j++){
      lp.set_a(j, 2 * i + 1, -1 * M[i][j]);
    }
    lp.set_b(2 * i + 1, -1 * lower_bound[i]);
  }
  for(int i = 0; i < m; i++){
    lp.set_c(i, price[i]);
  }
  lp.set_c0(0);


  Solution s = CGAL::solve_linear_program(lp, ET());
  if(s.is_infeasible()) cout << "No such diet." << endl; 
  else{
    CGAL::Quotient<ET> res = s.objective_value();
    cout << res.numerator() / res.denominator() << endl;
  }
}

int main(){
  ios_base::sync_with_stdio(false); 
  while(true){
    int n, m; 
    cin >> n >> m; 
    if(n == 0 && m == 0) break; 
    else testcase(n, m);
  } 
  return 0; 
}
