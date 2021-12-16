#include<iostream>
#include <vector>
#include<limits.h>
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
  int n, m; 
  cin >> n >> m; 
 
  weighted_graph G(n);
  weight_map weights = boost::get(boost::edge_weight, G);
  edge_desc e;
  for(int i = 0; i < m; i++){
      int u, v, w; 
      cin >> u >> v >> w; 
      e = boost::add_edge(u, v, G).first; weights[e]=w;   
  }
  
  vector<edge_desc> mst;  
  boost::kruskal_minimum_spanning_tree(G, std::back_inserter(mst));
  int res = 0; 
  for (std::vector<edge_desc>::iterator it = mst.begin(); it != mst.end(); ++it) {
    res+= weights[*it];
  }
  
  int max = INT_MIN; 
  for(int i = 0; i < n; i++){
    if(dijkstra_dist(G, 0, i) > max) max = dijkstra_dist(G, 0, i); 
  }
  
  cout << res << " " << max << endl; 
  
}

int main(){
  ios_base::sync_with_stdio(false); 
  int t; cin >> t; 
  while(t--) testcase(); 
  return 0; 
}
