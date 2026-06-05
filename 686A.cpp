#include<iostream>
#include<vector>
using namespace std;

int main() {
    long long n,x;
    cin>>n>>x;

    vector<char> sign;
    vector<int> nos;
    
    for(long long i=0;i<n;i++) {
        char temp1;long long temp2;
        cin>>temp1>>temp2;
        sign.push_back(temp1);
        nos.push_back(temp2);
    }

    long long k = sign.size();
    long long distress = 0;
    for(long long i=0;i<k;i++) {
        if(sign[i] == '+') {
            x+=nos[i];
        }

        else{
            if(x >= nos[i]) {
                x-=nos[i];
            }

            else{
                distress++;
            }
        }
    }
    cout<<x<<" "<<distress<<endl;
    return 0;
}