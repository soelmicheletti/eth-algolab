#include<iostream>
#include<vector>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

using namespace std; 

typedef double IT;
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

bool sufficient(int h, int t, vector<tuple<double, double, double>> &H, vector<tuple<double, double, double>> &T, int d){
  Program lp(CGAL::SMALLER, false, 0, false, 0);
  int s = 0; 
  for(int i = 0; i < h; i++){
    int p = 1; 
    for(int g1 = 0; g1 <= d; g1++){
      for(int g2 = 0; g2 <= d - g1; g2++){
        for(int g3 = 0; g3 <= d - g1 - g2; g3++){
          lp.set_a(p, s, pow(get<0>(H[i]), g1) * pow(get<1>(H[i]), g2) * pow(get<2>(H[i]), g3));
          p++; 
        }
      }
    }
    lp.set_a(0, s, 1);
    lp.set_b(s, 0); 
    s++; 
  }
  
  for(int i = 0; i < t; i++){
    int p = 1; 
    for(int g1 = 0; g1 <= d; g1++){
      for(int g2 = 0; g2 <= d - g1; g2++){
        for(int g3 = 0; g3 <= d - g1 - g2; g3++){
          lp.set_a(p, s, - 1 * pow(get<0>(T[i]), g1) * pow(get<1>(T[i]), g2) * pow(get<2>(T[i]), g3));
          p++; 
        }
      }
    }
    lp.set_a(0, s, 1); 
    lp.set_b(s, 0); 
    s++; 
  }
    lp.set_l(0, true, 1); 
    CGAL::Quadratic_program_options options;
    options.set_pricing_strategy(CGAL::QP_BLAND);
    Solution res = CGAL::solve_linear_program(lp, ET(), options);
    return !res.is_infeasible();
  
}


void testcase(){
  int h, t; 
  cin >> h >> t; 
  vector<tuple<double, double, double>> H(h); 
  vector<tuple<double, double, double>> T(t); 
  for(int i = 0; i < h; i++){
    double x, y, z; 
    cin >> x >> y >> z; 
    H[i] = make_tuple(x, y, z); 
  }
  for(int i = 0; i < t; i++){
    double x, y, z; 
    cin >> x >> y >> z; 
    T[i] = make_tuple(x, y, z); 
  }
  
  bool flag = false; 
  for(int i = 0; i < 30; i++){
    if(sufficient(h, t, H, T, i)){
      flag = true; 
      cout << i << endl; 
      i = 41; 
    }
  }
  if(!flag) cout << "Impossible!" << endl; 
}

int main(){
    ios_base::sync_with_stdio(false);
    int t; cin >> t; 
    for(int i = 0; i < t; i++){
        testcase(); 
    }
    return 0; 
}
