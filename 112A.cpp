#include<iostream>
#include<string.h> // Required for strcmp
using namespace std;

int main() {
    // Allocate space for up to 99 characters + 1 null terminator
    char s1[100]; 
    char s2[100];

    cin >> s1;
    cin >> s2;

    int k = strcmp(s1, s2);
    if(k > 0) {
        cout<<1<<endl;
    }
    else if(k < 0) {
        cout<<-1<<endl;
    }

    else cout<<0<<endl;

    return 0;
}