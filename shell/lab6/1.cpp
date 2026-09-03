#include <iostream>
using namespace std;
void fifo(string reference,int frames) {
    int pagefault = 0;

    vector<int> frame(frames);
    int curr = 0;
    for(auto s : reference) {
        if(curr >= frames) curr = 0;
        if(find(frame.begin(),frame.end(),s) == frame.end()) {
            pagefault++;
            frame[curr] = s;
            curr++;

            for(auto v : frame) {
                cout<<v<<" ";
            }

            cout<<endl;
        }

        //make queue of size "frames", if miss then pop and push the new element, else keep it as it is
    }
}


void lru(string reference, int frames) {
    
}

int main() {

    string reference;
    cout<<"Enter the strig input"<<endl;
    cin>>reference;

    int frames;
    cout<<"Enter number of frames"<<endl;
    cin>>frames;

    fifo(reference,frames);

    return 0;
}