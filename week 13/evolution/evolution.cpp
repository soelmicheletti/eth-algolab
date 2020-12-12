#include<iostream>
#include<vector>
#include<algorithm>
#include<utility>
#include<string>
#include<map>

using namespace std; 

int n; 
int q; 
vector<string> int_to_string; 
map<string, int> string_to_int; 
vector<string> res;
vector<int> age; 
int root;
vector<vector<int>> G;

void algo(vector<vector<pair<int, int>>> &query_from, int s, vector<int> &path){
  for(int i = 0; i < query_from[s].size(); i++){
    int b = query_from[s][i].first; 
    int index = query_from[s][i].second;
    int left = 0; 
    int right = path.size() - 1; 
    while(left <= right){
      int m = (left + right) / 2; 
      //cout << "m = " << m << " with age = " << age[G[m][ind]] << endl;
      if(age[path[m]] > b) left = m + 1; 
      else if(age[path[m]] <= b && m > 0 && age[path[m - 1]] > b){
        res[index] = int_to_string[path[m]];
        left = right + 1; 
      }
      else if(age[path[m]] <= b && path[m] == root){
        res[index] = int_to_string[path[m]];
        left = right + 1; 
      }
      else if(age[path[m]] <= b) right = m - 1; 
    }
  }
  
  for(int i = 0; i < G[s].size(); i++){
    path.push_back(G[s][i]);
    algo(query_from, G[s][i], path);
  }
  path.pop_back();
}

void testcase(){
  cin >> n >> q; 
  int_to_string.clear(); int_to_string.resize(n); 
  string_to_int.clear(); 
  age.clear(); age.resize(n); 
  
  for(int i = 0; i < n; i++){
    string s; int a; 
    cin >> s >> a; 
    age[i] = a; 
    int_to_string[i] = s; 
    string_to_int.insert(make_pair(s, i)); 
  }
  
  G.clear(); G.resize(n); 
  vector<bool> is_root(n, true); 
  for(int i = 0; i < n - 1; i++){
    string s, p;
    cin >> s >> p;
    G[string_to_int.find(p) -> second].push_back(string_to_int.find(s) -> second);
    is_root[string_to_int.find(s) -> second] = false;
  }
  root = -1;
  for(int i = 0; i < n; i++){
    if(is_root[i]) root = i;
  }
  
  vector<vector<pair<int, int>>> query_from(n);
  res.clear(); res.resize(q);
  for(int i = 0; i < q; i++){
    string s; int b;
    cin >> s >> b;
    query_from[string_to_int.find(s) -> second].push_back(make_pair(b, i));
  }
  vector<int> path;
  path.push_back(root);
  algo(query_from, root, path);
  for(int i = 0; i < q; i++){
    cout << res[i] << " ";
  }
  cout << endl;
}

int main(){
  ios_base::sync_with_stdio(false); 
  int t; cin >> t; 
  for(int i = 0; i < t; i++) testcase(); 
  return 0; 
}
