#include<iostream>
#include<set>

using namespace std; 


void testcase(){
    int q; cin >> q; 
    set <int> s; 
    
    for(int i = 0; i < q; i++){
        int a; cin >> a; 
        int b; cin >> b; 
        if(a == 0){
            s.insert(b); 
        } else if(a == 1){
            auto it = s.find(b); 
            if(it != s.end()){
                s.erase(it); 
            }
        }
    }

    if(s.empty()){
        cout << "Empty" << endl; 
    } else{
        for(int x : s){
            cout << x << " ";
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
