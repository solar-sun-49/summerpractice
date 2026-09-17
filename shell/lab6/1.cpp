#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;


void fifo(string reference, int frames) {

    vector<int> frame(frames, -1);
    int pagefault = 0;
    int curr = 0;

    for(int i = 0; i < reference.size(); i++) {

        int page = reference[i] - '0';

        if(find(frame.begin(), frame.end(), page) == frame.end()) {

            pagefault++;

            frame[curr] = page;
            curr++;

            if(curr >= frames)
                curr = 0;

            for(auto v : frame) {
                if(v != -1)
                    cout << v << " ";
            }

            cout << endl;
        }
    }

    cout << "Number of page faults : " << pagefault << endl;
}


void lru(string reference, int frames) {

    vector<int> frame;
    int pagefault = 0;

    for(int i = 0; i < reference.size(); i++) {

        int page = reference[i] - '0';

        auto it = find(frame.begin(), frame.end(), page);

        // Page is already present
        if(it != frame.end()) {

            // Move the recently used page to the back
            frame.erase(it);
            frame.push_back(page);
        }

        // Page is not present
        else {

            pagefault++;

            // If frames are full, remove least recently used page
            if(frame.size() == frames) {
                frame.erase(frame.begin());
            }

            frame.push_back(page);

            for(auto v : frame) {
                cout << v << " ";
            }

            cout << endl;
        }
    }

    cout << "Number of page faults : " << pagefault << endl;
}


void optimal(string reference, int frames) {

    vector<int> frame(frames, -1);
    int pagefault = 0;
    int filled = 0;

    for(int i = 0; i < reference.size(); i++) {

        int page = reference[i] - '0';

        // Check if page is already present
        if(find(frame.begin(), frame.end(), page) != frame.end()) {
            continue;
        }

        // Page fault
        pagefault++;

        // If there is an empty frame
        if(filled < frames) {

            frame[filled] = page;
            filled++;

            for(auto v : frame) {
                if(v != -1)
                    cout << v << " ";
            }

            cout << endl;

            continue;
        }

        // Find page used farthest in the future
        int replaceIndex = -1;
        int farthest = -1;

        for(int j = 0; j < frames; j++) {

            int k;

            // Search for next occurrence of frame[j]
            for(k = i + 1; k < reference.size(); k++) {

                int futurePage = reference[k] - '0';

                if(futurePage == frame[j]) {
                    break;
                }
            }

            // Page will never be used again
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

        // Replace page
        frame[replaceIndex] = page;

        // Display frames
        for(auto v : frame) {
            cout << v << " ";
        }

        cout << endl;
    }

    cout << "Number of page faults : " << pagefault << endl;
}


int main() {

    string reference;

    cout << "Enter the string input: ";
    cin >> reference;

    int frames;

    cout << "Enter number of frames: ";
    cin >> frames;


    cout << "\nFIFO\n";
    fifo(reference, frames);

    cout << "\nLRU\n";
    lru(reference, frames);

    cout << "\nOPTIMAL\n";
    optimal(reference, frames);

    return 0;
}