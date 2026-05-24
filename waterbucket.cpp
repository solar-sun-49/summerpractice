#include<iostream>
using namespace std;    

void waterbucket(int a, int b, int c) {
    if (c > a && c > b) {
        cout << "NO" << endl;
        return;
    }
    if (c % __gcd(a, b) == 0) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
}   

int main() {
    int t;
    cin >> t;
    while (t--) {
        int a, b, c;
        cin >> a >> b >> c;
        waterbucket(a, b, c);
    }
    return 0;
}   

