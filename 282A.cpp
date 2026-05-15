#include<iostream>
#include<vector>
using namespace std;

int main() {

    int t;
    cin>>t;
    vector<string> s;

    while(t--) {
        string k;
        cin>>k;
        s.push_back(k);
    }
    int count = 0;

    for(auto i : s) {
        if(i[1] == '+') {
            count++;
        }

        else if(i[1] == '-') {
            count--;
        }
    }

    cout<<count<<endl;

    return 0;
}