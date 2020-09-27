#include<iostream>
#include<string>
#include <bits/stdc++.h>

using namespace std; 

void testcase(){
  string a; cin >> a; 
  string b; cin >> b; 
  cout << a.length() << " " << b.length() << "\n";
  cout << a + b << "\n";
  reverse(a.begin(), a.end());
  reverse(b.begin(), b.end());
  char pa = a.at(0);
  char pb = b.at(0);
  a.at(0) = pb;
  b.at(0) = pa;
  cout << a << " " << b << endl;
}

int main(){
  ios_base::sync_with_stdio(false);
  int t; cin >> t; 
  for(int i = 0; i < t; i++){
    testcase(); 
  }
  return 0; 
}
