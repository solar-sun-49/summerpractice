//reference -> the given string
//frames -> number of frames
//pagefault -> number of page misses


#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string>

using namespace std;

void fifo(string reference, int frames) {
    int pagefault = 0;

    vector<int> frame(frames);
    int curr = 0;

    for(auto s : reference) {
        if(curr >= frames)
            curr = 0;

        if(find(frame.begin(), frame.end(), s) == frame.end()) {
            pagefault++;
            frame[curr] = s;
            curr++;

            for(auto v : frame) {
                cout << v << " ";
            }

            cout << endl;
        }
    }

    cout << "Number of page faults : " << pagefault << endl;
}


void optimal(string reference, int frames) {
    vector<int> frame(frames);
    int pagefault = 0;
    int filled = 0;

    for(int i = 0; i < reference.size(); i++) {
        int page = reference[i];

        // Check if page is already present
        if(find(frame.begin(), frame.end(), page) != frame.end()) {
            continue;
        }

        pagefault++;

        // If there is an empty frame, put the page there
        if(filled < frames) {
            frame[filled] = page;
            filled++;

            for(auto v : frame) {
                cout << v << " ";
            }
            cout << endl;
            continue;
        }

        // Find the page which will be used farthest in the future
        int replaceIndex = -1;
        int farthest = -1;

        for(int j = 0; j < frames; j++) {
            int k;
            // Search for next use of frame[j]
            for(k = i + 1; k < reference.size(); k++) {
                if(reference[k] == frame[j]) {
                    break;
                }
            }
            // Page is never used again
            if(k == reference.size()) {
                replaceIndex = j;
                break;
            }
            // Page used farthest in future
            if(k > farthest) {
                farthest = k;
                replaceIndex = j;
            }
        }
        frame[replaceIndex] = page;

        // Display current frames
        for(auto v : frame) {
            cout << v << " ";
        }
        cout << endl;
    }
    cout << "Number of page faults : " << pagefault << endl;
}


void lru(string reference, int frames) {

    vector<int> frame(frames);
    int pagefault = 0;

    for(auto s : reference) {

        auto it = find(frame.begin(), frame.end(), s);

        if(it != frame.end()) {
            int page = *it;
            frame.erase(it);
            frame.push_back(page);
        }

        else {

            pagefault++;
            frame.erase(frame.begin());
            frame.push_back(s);

            for(auto i : frame) {
                cout << i << " ";
            }

            cout << endl;
        }
    }

    cout << "Page faults : " << pagefault << endl;
}


int main() {

    string reference;

    cout << "Enter the string input" << endl;
    cin >> reference;

    int frames;

    cout << "Enter number of frames" << endl;
    cin >> frames;

    // fifo(reference, frames);

    // cout << endl << endl;

    // lru(reference, frames);

    cout << endl;
    optimal(reference, frames);

    return 0;
}