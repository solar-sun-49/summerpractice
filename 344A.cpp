#include<iostream>
#include<vector>
using namespace std;

int main() {
    int count = 0;
    int n;
    cin>>n;
    vector<int> magnets;

    for(int i=0;i<n;i++) {
        int x;cin>>x;
        magnets.push_back(x);
    }

    for(int i=0;i<n-1;i++) {
        int x = magnets[i];
        int y = magnets[i+1];

        if(x == y) {
            continue;
        }

        else{
            count++;
        }
    }
    if(n>=1) {
        count++;
    }
    cout<<count<<endl;
}