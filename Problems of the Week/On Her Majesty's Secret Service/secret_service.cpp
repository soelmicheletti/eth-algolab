#include <iostream>
#include <vector>
#include <string>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/max_cardinality_matching.hpp>


using namespace std; 

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> >      weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor          vertex_desc;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> graph;
typedef boost::graph_traits<graph>::vertex_descriptor                       vertex_desc1;


vector<int> dijkstra_dist(const weighted_graph &G, int s, int t) {
  int n = boost::num_vertices(G);
  std::vector<int> dist_map(n);

  boost::dijkstra_shortest_paths(G, s,
    boost::distance_map(boost::make_iterator_property_map(
      dist_map.begin(), boost::get(boost::vertex_index, G))));

  return dist_map;
}

int maximum_matching(const graph &G) {
  int n = boost::num_vertices(G);
  std::vector<vertex_desc1> mate_map(n);  // exterior property map
  const vertex_desc1 NULL_VERTEX = boost::graph_traits<graph>::null_vertex();

  boost::edmonds_maximum_cardinality_matching(G,
    boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, G)));
  int matching_size = boost::matching_size(G,
    boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, G)));
  int size = 0;
  for (int i = 0; i < n; ++i) {
    if (mate_map[i] != NULL_VERTEX && i < mate_map[i]) size++;
  }
  return size;
}

int n;
int m;
int a; 
int s; 
int c; 
int d; 
vector<int> agents;
vector<int> shelters; 
vector<vector<int>> SP;

bool algo(int lim){
  graph G(a + s);
  
  for(int i = 0; i < a; i++){
    for(int j = 0; j < s; j++){
      if(SP[i][j] <= lim) boost::add_edge(i, a + j, G);
    }
  }
  if(maximum_matching(G) >= a) return true;
  else return false; 
}

bool algo1(int lim){
  graph G(a + 2 * s); 
  for(int i = 0; i < a; i++){
    for(int j = 0; j < s; j++){
      if(SP[i][j] != INT_MAX && SP[i][j] + d <= lim) boost::add_edge(i, a + 2 * j, G);
      if(SP[i][j] != INT_MAX && SP[i][j] + 2 * d <= lim){
        boost::add_edge(i, a + 2 * j + 1, G); 
      }
    }
  }
  if(maximum_matching(G) >= a) return true;
  else return false;
}

void testcase(){
  cin >> n >> m >> a >> s >> c >> d; 
  weighted_graph G(n);
  weight_map weights = boost::get(boost::edge_weight, G);

  edge_desc e;
  for(int i = 0; i < m; i++){
    string w; int x, y, z; 
    cin >> w >>  x >> y >> z; 
    if(w == "S"){
      e = boost::add_edge(x, y, G).first; weights[e]=z;
    }
    else if(w == "L"){
      e = boost::add_edge(x, y, G).first; weights[e]=z;
      e = boost::add_edge(y, x, G).first; weights[e]=z;
    }
  }
  agents.clear(); agents.resize(a); 
  for(int i = 0; i < a; i++) cin >> agents[i];
  shelters.clear(); shelters.resize(s); 
  for(int i = 0; i < s; i++) cin >> shelters[i];
  SP.clear(); SP.resize(a, vector<int>(s, INT_MAX));
  
  int longest = INT_MIN; 
  for(int i = 0; i < a; i++){
    vector<int> path = dijkstra_dist(G, agents[i], n - 1);
    for(int j = 0; j < s; j++){
      SP[i][j] = path[shelters[j]];
      if(SP[i][j] != INT_MAX) longest = max(longest, SP[i][j]);
    } 
  }
  if(a == 1){
    int res = INT_MAX; 
    for(int j = 0; j < s; j++) res = min(res, SP[0][j]);
    cout << res + d << endl; 
  }
  else if(c == 1){
  int res = INT_MAX; 
  int l = 0; 
  int r = longest; 
  while(l <= r){
    int m = (l + r) / 2; 
    if(algo(m) && m > 0 && !algo(m - 1)){ res = m; l = r + 1;}
    else if(algo(m) && m == 0){ res = m; l = r + 1; } 
    else if(algo(m)) r = m - 1; 
    else if(!algo(m)) l = m + 1; 
  }
  
  cout << res + d << endl;
  }
  else if(c == 2){
    int res = INT_MAX; 
    int l = d; 
    int r = longest + 2 * d; 
    while(l <= r){
      int m = (l + r) / 2; 
      if(algo1(m) && m > d && !algo1(m - 1)){ res = m; l = r + 1;}
      else if(algo1(m) && m == d){ res = m; l = r + 1; } 
      else if(algo1(m)) r = m - 1; 
      else if(!algo1(m)) l = m + 1; 
    }
    cout << res << endl;
  }
}

int main(){
  ios_base::sync_with_stdio(false); 
  int t; cin >> t; 
  for(int i = 0; i < t; i++) testcase(); 
  return 0;
}
