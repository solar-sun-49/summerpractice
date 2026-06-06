#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main() {
    int t;cin>>t;
    while(t--) {
        int n;cin>>n;
        vector<int> pos;
        for(int i=0;i<n;i++) {
            int k;cin>>k;
            pos.push_back(k);
        }

        sort(pos.begin(),pos.end());


        int avg = (pos[0] + pos[pos.size()-1])/2;


        if((pos[0] + pos[pos.size()-1])%2 != 0) {
            avg++;
        }

        int check = max(avg - pos[0],pos[pos.size()-1]-avg);

        // for(auto i : pos) {
        //     cout<<i<<" ";
        // }

        cout<<check<<endl;

        
    }

    return 0;
}