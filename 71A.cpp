#include<iostream>
#include<vector>
using namespace std;

int main() {
    int t;cin>>t;
    vector<string> s;
    while(t--) {
        string k;
        cin>>k;
        s.push_back(k);
    }

    for(auto i : s) {
        string newstring = "";
        if(i.length() > 10) {
            newstring+=i[0];
            int z = i.length() - 2;
            newstring+=to_string(z);
            newstring+=i[i.length()-1];

            cout<<newstring<<endl;
        }

        else{
            cout<<i<<endl;
        }
    }

    return 0;
}