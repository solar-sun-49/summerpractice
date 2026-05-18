#include <bits/stdc++.h>
using namespace std;

int main() {
	// your code goes here
	
	int t;cin>>t;
	while(t--) {
	    vector<int> temps;
        int n;
        int z = n;
        while(z--) {
            int k;
            cin>>k;
            temps.push_back(k);
        }
        
        sort(temps.begin(),temps.end());
        int min = temps.front();
        int max = temps.back();
        
        for(int i=0;i<n;i++) {
        if(temps.back() == max) {
            temps.pop_back();}
        
        
        for(int i=0;i<n;i++) {
        if(temps.front() == min) {
            temps.erase(temps.begin());}
        }
        
        cout<<temps.size()<<endl;
        
	}
	
    return 0;
}
