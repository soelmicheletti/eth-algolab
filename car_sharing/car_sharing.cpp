#include <iostream>
#include<vector>
#include<set>
#include<map>
#include<limits.h>
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

struct request{
  int s; 
  int t; 
  int d; 
  int a; 
  int p; 
};

void testcase(){
  int N, S; 
  cin >> N >> S; 
  vector<int> supply(S); 
  int sum = 0; 
  for(int i = 0; i < S; i++){
    int k; cin >> k; 
    supply[i] = k; 
    sum += k; 
  }
  vector<request> book(N); 
  vector<set<int>> nodes(S); 
  int max_a = INT_MIN; 
  for(int i = 0; i < N; i++){
    int s, t, d, a, p; 
    cin >> s >> t >> d >> a >> p; 
    book[i] = {s - 1, t - 1, d, a, p}; 
    nodes[s - 1].insert(d); 
    nodes[t - 1].insert(a); 
    max_a = max(max_a, a); 
  }
  
  int size = 0; 
  vector<map<int, int>> M(S);  
  for(int i = 0; i < S; i++){
    nodes[i].insert(0);
    nodes[i].insert(max_a);
    map<int, int> L; 
    int p = 0; 
    size += nodes[i].size(); 
    for(auto v = nodes[i].begin(); v != nodes[i].end(); v++){
      L.insert(pair<int, int>(*v, p)); 
      p++; 
    }
    M[i] = L; 
  }
  
  vector<int> offset(S); 
  offset[0] = 1;
  for(int i = 1; i < S; i++){
    int k = nodes[i - 1].size(); 
    offset[i] = offset[i - 1] + k;
  }
  
  graph G(size + 2);
  edge_adder adder(G);  
  auto c_map = boost::get(boost::edge_capacity, G);
  //auto r_map = boost::get(boost::edge_reverse, G);
  auto rc_map = boost::get(boost::edge_residual_capacity, G);
  for(int i = 0; i < S; i++){
    adder.add_edge(0, offset[i], supply[i], 0); 
  }  
  for(int i = 0; i < S; i++){
    auto start = nodes[i].begin(); 
    auto dest = nodes[i].begin();
    dest++; 
    for(int j = 0; j < (int)nodes[i].size() - 1; j++){
      adder.add_edge(offset[i] + j, offset[i] + j + 1, INT_MAX, 100 * (*dest - *start)); 
      start++; 
      dest++; 
    }
  }
  
  for(int i = 0; i < S - 1; i++){
    adder.add_edge(offset[i + 1] - 1, size + 1, INT_MAX, 0);
  }
  adder.add_edge(size, size + 1, INT_MAX, 0);
  

  for(int i = 0; i < N; i++){
    request T = book[i]; 
    adder.add_edge(offset[T.s] + M[T.s].find(T.d) -> second, offset[T.t] + M[T.t].find(T.a) -> second, 1, -T.p + 100 * (T.a - T.d)); 
  }

  boost::successive_shortest_path_nonnegative_weights(G, 0, size + 1);
  int cost2 = boost::find_flow_cost(G);
  cout << -(cost2 - 100 * max_a * sum) << endl; 
}

int main() {
  ios_base::sync_with_stdio(false); 
  int t; cin >> t; 
  for(int i = 0; i < t; i++) testcase(); 
  return 0;
}
