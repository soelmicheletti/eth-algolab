#include <iostream>
#include<vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>

using namespace std;

// Graph Type with nested interior edge properties for Cost Flow Algorithms
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor,
                boost::property <boost::edge_weight_t, long> > > > > graph; // new! weightmap corresponds to costs

typedef boost::graph_traits<graph>::edge_descriptor             edge_desc;
typedef boost::graph_traits<graph>::out_edge_iterator           out_edge_it; // Iterator

// Custom edge adder class
class edge_adder {
 graph &G;

 public:
  explicit edge_adder(graph &G) : G(G) {}
  void add_edge(int from, int to, long capacity, long cost) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    auto w_map = boost::get(boost::edge_weight, G); // new!
    const edge_desc e = boost::add_edge(from, to, G).first;
    const edge_desc rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0; // reverse edge has no capacity!
    r_map[e] = rev_e;
    r_map[rev_e] = e;
    w_map[e] = cost;   // new assign cost
    w_map[rev_e] = -cost;   // new negative cost
  }
};

struct guide{
  int x; 
  int y; 
  int d; 
  int e; 
};

int algo(int m, vector<guide> &P, int a, int k, int b, int c){
  graph G(c + 2);
  edge_adder adder(G);  
  auto c_map = boost::get(boost::edge_capacity, G);
  auto r_map = boost::get(boost::edge_reverse, G);
  auto rc_map = boost::get(boost::edge_residual_capacity, G);
  
  adder.add_edge(c, a, m, 0);
  adder.add_edge(k, c + 1, INT_MAX, 0); 
  
  for(int i = 0; i < P.size(); i++){
    guide g = P[i]; 
    adder.add_edge(g.x, g.y, g.e, g.d); 
  }
    // Option 2: Min Cost Max Flow with successive_shortest_path_nonnegative_weights  
  boost::successive_shortest_path_nonnegative_weights(G, c, c + 1);
  int cost2 = boost::find_flow_cost(G);
  int s_flow = 0;
  out_edge_it e, eend;
  for(boost::tie(e, eend) = boost::out_edges(boost::vertex(c,G), G); e != eend; ++e) {
    s_flow += c_map[*e] - rc_map[*e];     
  }
//  cout << "m = " << m << " cost = " << cost2 << " flow = " << s_flow << endl; 
  if(cost2 > b) return -1; 
  else return s_flow; 
}

void testcase(){
  int c, g, b, a, k;
  cin >> c >> g >> b >> a >> k;
  vector<guide> P(g); 
  for(int i = 0; i < g; i++){
    int x, y, d, e; 
    cin >> x >> y >> d >> e; 
    P[i] = {x, y, d, e}; 
  }
  
  int l = 0; 
  int r = 1000000000; 
  int m = 0; 
  while(l <= r){
    m = (l + r) / 2;
    int res = algo(m, P, a, k, b, c);
    if(res == -1) r = m - 1;
    else if(res < m){m = res; break; }
    else if(res == m && algo(m + 1, P, a, k, b, c) == -1){m = res; break;}
    else l = m + 1; 
  }
  cout << m << endl; 
}

int main() {
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for(int i = 0; i < t; i++) testcase();
  return 0;
}
