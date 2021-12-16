#include <iostream>
#include<vector>
#include<limits.h>
#include<tuple>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>

using namespace std; 

typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor,
                boost::property <boost::edge_weight_t, long> > > > > graph; // new! weightmap corresponds to costs

typedef boost::graph_traits<graph>::edge_descriptor             edge_desc;
typedef boost::graph_traits<graph>::out_edge_iterator           out_edge_it; // Iterator

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
    
    int N, M, S; 
    cin >> N >> M >> S; 
    
    vector<int> state(S + 1);
    vector<int> belongs(M);
    vector<vector<int>> offer(N, vector<int>(M, 1));
    int massimo = INT_MIN; 
    for(int i = 1; i <= S; i++){
      cin >> state[i];
    }
    for(int i = 0; i < M; i++){
      cin >> belongs[i]; 
    }
    
    for(int i = 0; i < N; i++){
      for(int j = 0; j < M; j++){
        cin >> offer[i][j];
        if(offer[i][j] > massimo){massimo = offer[i][j];} 
      }
    }
    
    
    const int n = S + M + N + 2;
    const int v_source = 0;
    const int v_target = S + M + N + 2;

    graph G(N);
    edge_adder adder(G);  
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    auto rc_map = boost::get(boost::edge_residual_capacity, G);
    
    // Add the edges
    for(int i = 1; i <= N; i++){
      adder.add_edge(v_source, i, 1, 0);
    }
    for(int i = 1; i <= N; i++){
      for(int j = 1; j <= M; j++){
        adder.add_edge(i, N + j, 1, -offer[i - 1][j - 1] + massimo);
      }
    }
    
    for(int i = 1; i <= M; i++){
      adder.add_edge(N + i, N + M + belongs[i - 1], 1, 0);
    }
    
    for(int i = 1; i <= S; i++){
      adder.add_edge(N + M + i, v_target, state[i], 0);
    }
  
    boost::successive_shortest_path_nonnegative_weights(G, v_source, v_target);
    int cost1 = boost::find_flow_cost(G);
    int s_flow = 0;
    out_edge_it e, eend;
    for(boost::tie(e, eend) = boost::out_edges(boost::vertex(v_source,G), G); e != eend; ++e) {
        s_flow += c_map[*e] - rc_map[*e];     
    }
    cout << s_flow << " " <<  -(cost1 - massimo * s_flow) << endl; 

}


int main() {
    ios_base::sync_with_stdio(false); 
    int t; cin >> t; 
    for(int i = 0; i < t; i++) testcase(); 
    return 0; 
}
