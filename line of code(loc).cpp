#include <bits/stdc++.h>
using namespace std;

int main(){
    ifstream infile("loc.cpp");
    string str;
    int c;
    while(getline(infile,str)){
        c++;
    }
    cout<<c;
}