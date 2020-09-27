#include<iostream>
#include<vector>

using namespace std; 

void printVector(vector<int> a){
    if(a.size() == 0){
        cout << "Empty" << endl; 
    } else{
    for(int i = 0; i < a.size(); i++){
        cout << a[i] << " "; 
    }
    cout << endl; 
    }
}

void testcase(){

    int n; cin >> n; 
    vector<int> a; 
    for(int i = 0; i < n; i++){
        int tmp; cin >> tmp; 
        a.push_back(tmp);    
    }
    int y; cin >> y; 
    a.erase(a.begin() + y); 
    int l; cin >> l; 
    int r; cin >> r; 
    a.erase(a.begin() + l, a.begin() + r + 1); 
    printVector(a);  
}

int main(){
    ios_base::sync_with_stdio(false);
    int t; cin >> t; 
    for(int i = 0; i < t; i++){
        testcase(); 
    }
    return 0; 
}
