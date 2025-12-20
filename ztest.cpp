#include<bits/stdc++.h>
using namespace std;


int main(){
    freopen("1.in","r",stdin);
    freopen("1.out","w",stdout);

    string str;
    while(getline(cin, str)){
        cout << str.substr(1, str.size() - 2) << endl;
    }
    return 0;
}