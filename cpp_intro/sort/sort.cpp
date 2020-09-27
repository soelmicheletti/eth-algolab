#include<iostream>
#include <bits/stdc++.h> 

using namespace std; 

int main(){
    ios_base::sync_with_stdio(false);
    int t; 
    cin >> t; 

    for(int i = 0; i < t; i++){
        int n; 
        cin >> n; 
        int a[n]; 
        for(int j = 0; j < n; j++){
            cin >> a[j]; 
        }
        int order; 
        cin >> order; 
        if(order == 0){
             sort(a, a+n); 
             for(int j = 0; j < n; j++){
                 cout << a[j] << " "; 
             }
             cout << endl; 
        } else{
            sort(a, a+n, greater<int>()); 
            for(int j = 0; j < n; j++){
                 cout << a[j] << " "; 
             }
            cout << endl; 
        }
    }
    
    return 0; 
}
