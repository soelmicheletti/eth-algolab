#include<iostream>
#include<vector>
#include<algorithm>
#include<limits.h>
#include<tuple>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

using namespace std; 

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> >      weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor          vertex_desc;

int dijkstra_dist(const weighted_graph &G, int s, int t) {
  int n = boost::num_vertices(G);
  std::vector<int> dist_map(n);

  boost::dijkstra_shortest_paths(G, s,
    boost::distance_map(boost::make_iterator_property_map(
      dist_map.begin(), boost::get(boost::vertex_index, G))));

  return dist_map[t];
}

void testcase(){
  int n, m, s, a, b; 
  cin >> n >> m >> s >> a >> b; 
  vector<vector<int>> A(n, vector<int>(n, INT_MAX)); 
  vector<vector<int>> H(m, vector<int>(s, -1));
  vector<tuple<int, int>> E;
  
  for(int i = 0; i < m; i++){
    int u, v; 
    cin >> u >> v; 
    E.push_back(make_tuple(u, v)); 
    for(int j = 0; j < s; j++){
      int s; cin >> s; 
      H[i][j] = s; 
    }
  }
  
  for(int i = 0; i < s; i++){int k; cin >> k; }
  
  for(int i = 0; i < s; i++){
    weighted_graph G(n);
    weight_map weights = boost::get(boost::edge_weight, G);

    edge_desc ed;
    for(int j = 0; j < m; j++){
      ed = boost::add_edge(get<0>(E[j]), get<1>(E[j]), G).first; weights[ed]=H[j][i];
    }
    vector<edge_desc> mst;
    boost::kruskal_minimum_spanning_tree(G, std::back_inserter(mst));
    for (std::vector<edge_desc>::iterator it = mst.begin(); it != mst.end(); ++it) {
      if(weights[*it] < A[boost::source(*it, G)][boost::target(*it, G)]){
        A[boost::source(*it, G)][boost::target(*it, G)] = weights[*it];
      }
    }
  }
  
  weighted_graph G(n);
  weight_map weights = boost::get(boost::edge_weight, G);

  edge_desc ed;
  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      if(A[i][j] != INT_MAX){
        ed = boost::add_edge(i, j, G).first; weights[ed]=A[i][j];
      }
    }
  }

  cout << dijkstra_dist(G, a, b) << endl; 

}

int main(){
  ios_base::sync_with_stdio(false); 
  int t; cin >> t; 
  while(t--) testcase(); 
}
