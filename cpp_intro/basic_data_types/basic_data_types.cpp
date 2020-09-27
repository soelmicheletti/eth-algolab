#include<iostream>
#include<iomanip>

using namespace std; 

int main(){
    ios_base::sync_with_stdio(false);
    int t; 
    cin >> t; 
    
    for(int i = 0; i < t; i++){
        int first; 
        cin >> first; 
        long second; 
        cin >> second; 
        string third; 
        cin >> third; 
        double fourth; 
        cin >> fourth; 
        cout << fixed << showpoint;
        cout << setprecision(2); 
        cout << first << " " << second << " " << third << " " << fourth << endl; 
    }

    return 0; 
}
