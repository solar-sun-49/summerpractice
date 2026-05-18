#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;

int main() {
    string s;cin>>s;
    unordered_map<char, int> map;

    for(int i=0;i<s.length();i++) {
        map[s[i]]++;
    }

    if(map.size() % 2 != 0) {
        cout<<"IGNORE HIM!"<<endl;
    }

    else{
        cout<<"CHAT WITH HER!"<<endl;
    }

    return 0;
}