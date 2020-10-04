#include<iostream>
#include<vector>
#include<algorithm>
#include<limits.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/number_utils.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt PK;


using namespace std;

typedef  CGAL::Min_circle_2_traits_2<PK>  Traits;
typedef  CGAL::Min_circle_2<Traits>      Min_circle;
typedef PK::Point_2 P;

double ceil_to_double(const PK::FT& x)
{
  double a = ceil(CGAL::to_double(x));
  while (a < x) a += 1;
  while (a-1 >= x) a -= 1;
  return a;
}

void testcase(int n){
  vector<P> points(n);
  for(int i = 0; i < n; i++){
    long u, v;
    cin >> u >> v;
    points[i] = P(u, v);
  }
  
  Min_circle mc(points.begin(), points.end(), true);
  Traits::Circle c = mc.circle();
  std::cout << (long)(ceil_to_double(CGAL::sqrt(c.squared_radius()))) << "\n";
  
}

int main(){
  ios_base::sync_with_stdio(false);
  bool flag = true;
  while(flag){
    int n; cin >> n;
    if(n == 0){
      flag = false;
      break;
    }
    else{
      testcase(n);
    }
  }
  return 0;
}
