#include<iostream>
#include<string>
#include<map>
#include<vector>
#include <bits/stdc++.h>

using namespace std; 

void testcase(){

    int q; cin >> q; 
    map<string, vector<int>> m; 
    for(int i = 0; i < q; i++){
        int x; cin >> x;
        string s; cin >> s;
        if(x == 0){
            m.erase(s);
        } else if(m.count(s) == 0){
            vector<int> v;
            v.push_back(x);
            m.insert(make_pair(s, v)); 
        } else{
           m.at(s).push_back(x);
        }
    }
    string ref; 
    cin >> ref; 
    if(m.count(ref) == 0){
        cout << "Empty" << endl;
    } else{
        vector<int> v = m.at(ref);
        sort(v.begin(), v.end());
        for(int i = 0; i < v.size(); i++){
            cout << v[i] << " ";
        }
        cout << endl;
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
