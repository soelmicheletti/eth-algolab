#include <iostream>
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

void testcase(){
  int n, m, l; 
  cin >> n >> m >> l; 
  const int N= n + 1 ;
  const int v_source = 0;
  
  graph G(N);
  edge_adder adder(G);  
  auto c_map = boost::get(boost::edge_capacity, G);
  auto r_map = boost::get(boost::edge_reverse, G);
  auto rc_map = boost::get(boost::edge_residual_capacity, G);
    
  int massimo = INT_MIN; 
  vector<tuple<int, int, int>> P(m + 1); 
  for(int i = 1; i <= m; i++){
    int x, y, q; 
    cin >> x >> y >> q; 
    if(q > massimo) massimo = q; 
    P[i] = make_tuple(x, y, q); 
  }
  
  for(int i = 1; i <= m; i++){
    int x = get<0>(P[i]); 
    int y = get<1>(P[i]); 
    int q = get<2>(P[i]);
    adder.add_edge(x + 1, y + 1, 1, -q + massimo * (y - x));
  }
  
  for(int i = 1; i <= n - 1; i++){
    adder.add_edge(i, i + 1, l, massimo);
  }
  
  adder.add_edge(v_source, 1, l, 0); 
  boost::successive_shortest_path_nonnegative_weights(G, v_source, n);
  int cost2 = boost::find_flow_cost(G);
  cout << -(cost2 - massimo * (n - 1) * l) << endl; 
}

int main() {
    ios_base::sync_with_stdio(false); 
    int t; cin >> t; 
    for(int i = 0; i < t; i++) testcase(); 
    return 0;
}
