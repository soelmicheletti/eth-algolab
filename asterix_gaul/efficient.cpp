#include<iostream>
#include<vector>
#include<tuple>
#include<algorithm>
#include<limits.h>

using namespace std; 
long D; 
long T; 

vector<tuple<long, long, int>> algo(const vector<tuple<long, long>> &M, int n, int b){
  vector<tuple<long, long, int>> res; 
  for(int i = 0; i < 1 << n; i++){
    long sum = 0; 
    long t = 0; 
    int len = 0; 
    for(int j = 0; j < n; j++){
      if(i & 1 << j){
        sum += get<0>(M[b + j]);
        t += get<1>(M[b + j]);
        len++; 
      }
    }
    if(t < T) res.push_back(make_tuple(sum, t, len)); 
  }
  return res; 
}

vector<long> prec(vector<pair<long,long>> res2) {
  long n = res2.size();
  vector<long> min_time_per_dist(n);
  long curr_min = res2[n-1].second;
  min_time_per_dist[n-1] = curr_min;
  for (long i= n-2; i>=0; i--) {
    curr_min = min(curr_min, res2[i].second);
    min_time_per_dist[i] = curr_min;
  }
  return min_time_per_dist;
}


bool check(const vector<tuple<long, long, int>> &l, const vector<tuple<long, long, int>> &r, long plus){
  vector<pair<long, long>> res1;
  vector<pair<long, long>> res2;
  for(int i = 0; i < (long)l.size(); i++){
    res1.push_back(make_pair(get<0>(l[i]) + get<2>(l[i]) * plus, get<1>(l[i])));
  }
  for(int i = 0; i < (long)r.size(); i++){
    res2.push_back(make_pair(get<0>(r[i]) + get<2>(r[i]) * plus, get<1>(r[i])));
  }
  sort(res2.begin(), res2.end(), [](auto p1, auto p2) {return p1.first < p2.first;});
  vector<long> min_time_per_dist = prec(res2);
  bool success = false;
  
  for (long i=0; i<(long)res1.size(); i++) {
    pair<long,long> curr = res1[i];
    if (curr.first >= D && curr.second < T) {
      success = true;
      break;
    }
    pair<long,long> to_find = {D-curr.first, INT_MIN};
    auto it = lower_bound(res2.begin(), res2.end(), to_find);
    if (it != res2.end() && min_time_per_dist[it-res2.begin()]+curr.second < T) {
      success = true;
      break;
    }
  }
  return success;
}

int bS(vector<long> &s, vector<tuple<long, long, int>> &l, vector<tuple<long, long, int>> &r, int left, int right){
  if(left > right) return -1; 
  if(left == right){
    if(check(l, r, s[left])) return left + 1; 
    else return -1; 
  }
  int mid = (left + right) / 2; 
  if(check(l, r, s[mid]) && mid == 0) return 1; 
  if(check(l, r, s[mid]) && !check(l, r, s[mid - 1])) return mid + 1; 
  if(!check(l, r, s[mid])) return bS(s, l, r, mid + 1, right); 
  if(check(l, r, s[mid])) return bS(s, l, r, left, mid - 1); 
  return -1; 
}

void testcase(){
  int n, m;  
  cin >> n >> m >> D >> T; 
  vector<tuple<long, long>> M; 
  vector<long> s;
  for(int i = 0; i < n; i++){
    long d, t; 
    cin >> d >> t;
    M.push_back(make_tuple(d, t));
  }
  
  for(int i = 0; i < m; i++){
    long k; cin >> k; 
    s.push_back(k);
  }
  
  bool flag = false;
  vector<tuple<long, long, int>> left = algo(M, n / 2, 0);
  vector<tuple<long, long, int>> right = algo(M, n - n / 2, n / 2); 
  if(check(left, right, 0)){
    cout << 0 << endl; 
    flag = true; 
  }
  
  int l = 0; 
  int r = m - 1; 
  if(!flag){
    int res = bS(s, left, right, l, r); 
    if(res != -1){
      flag = true; 
      cout << res << endl; 
    }
  }
  
  if(!flag){
    cout << "Panoramix captured" << endl; 
  }
}

int main(){
  ios_base::sync_with_stdio(false);
  int t; cin >> t; 
  for(int i = 0; i < t; i++){
    testcase(); 
  }
  return 0; 
}
