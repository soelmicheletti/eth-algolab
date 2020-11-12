#include <iostream>
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

using namespace std; 

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> graph;
typedef boost::graph_traits<graph>::vertex_descriptor                       vertex_desc;

int maximum_matching(const graph &G) {
  int n = boost::num_vertices(G);
  std::vector<vertex_desc> mate_map(n);  // exterior property map
  const vertex_desc NULL_VERTEX = boost::graph_traits<graph>::null_vertex();

  boost::edmonds_maximum_cardinality_matching(G,
    boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, G)));
  int matching_size = boost::matching_size(G,
    boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, G)));
  int res = 0; 
  for (int i = 0; i < n; ++i) {
    // mate_map[i] != NULL_VERTEX: the vertex is matched
    // i < mate_map[i]: visit each edge in the matching only once
    if (mate_map[i] != NULL_VERTEX && i < mate_map[i]) res++;
  }
  return res; 
}

void testcase(){
  int n; 
  cin >> n; 
  graph G(n);
  int count = 0; 
  vector<vector<int>> mask(n, vector<int>(n, -1)); 
  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      cin >> mask[i][j]; 
      if(mask[i][j]) count++; 
    }
  }
  
  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      if(mask[i][j]){
        if(i - 1 >= 0 && j - 2 >= 0 && mask[i - 1][j - 2]) boost::add_edge(i * n + j, (i - 1) * n + j - 2, G); 
        if(i - 1 >= 0 && j + 2 < n && mask[i - 1][j + 2]) boost::add_edge(i * n + j, (i - 1) * n + j + 2, G);
        if(i + 1 < n && j - 2 >= 0 && mask[i + 1][j - 2]) boost::add_edge(i * n + j, (i + 1) * n + j - 2, G);
        if(i + 1 < n && j + 2 < n && mask[i + 1][j + 2]) boost::add_edge(i * n + j, (i + 1) * n + j + 2, G);
        if(i - 2 >= 0 && j - 1 >= 0 && mask[i - 2][j - 1]) boost::add_edge(i * n + j, (i - 2) * n + j - 1, G);
        if(i - 2 >= 0 && j + 1 < n && mask[i - 2][j + 1]) boost::add_edge(i * n + j, (i - 2) * n + j + 1, G); 
        if(i + 2 < n && j - 1 >= 0 && mask[i + 2][j - 1]) boost::add_edge(i * n + j, (i + 2) * n + j - 1, G);
        if(i + 2 < n &&  j + 1 < n && mask[i + 2][j + 1]) boost::add_edge(i * n + j, (i + 2) * n + j + 1, G);
      }
    }
  }
  

  int res = maximum_matching(G);
  cout << count - res << endl; 
}

int main(){
  ios_base::sync_with_stdio(false); 
  int t; cin >> t; 
  for(int i = 0; i < t; i++) testcase(); 
  return 0;
}
