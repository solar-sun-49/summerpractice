#include <iostream>
#include <vector>
using namespace std;

int main() {

    int n,m;
    cout<<"Enter number of processes : ";
    cin>>n;
    cout<<"Enter number of resource types : ";
    cin>>m;

    vector<vector<int>> allocation(n,vector<int> (m));
    vector<vector<int>> max(n,vector<int> (m));
    vector<int> available(m);
    vector<vector<int>> need(n,vector<int> (m));
    vector<vector<int>> request(n,vector<int> (m));

    cout<<endl<<"Enter the available resource(space in between) : ";
    for(int i=0;i<m;i++) {
        int temp;
        cin>>temp;
        available[i] = temp;
    }

    cout<<endl<<endl<<"Enter the allocated(space in between) : "<<endl;
    for(int i=0;i<n;i++) {
        cout<<"Enter for process "<<i+1<<" : ";
        for(int j=0;j<m;j++) {
            int temp;
            cin>>temp;
            allocation[i][j] = temp;
        }
    }

    cout<<endl<<endl<<"Enter the max(space in between) : "<<endl;
    for(int i=0;i<n;i++) {
        cout<<"Enter for process "<<i+1<<" : ";
        for(int j=0;j<m;j++) {
            int temp;
            cin>>temp;
            max[i][j] = temp;
        }
    }

    cout<<endl<<endl<<"Enter the request(space in between) : "<<endl;
    for(int i=0;i<n;i++) {
        cout<<"Enter for process "<<i+1<<" : ";
        for(int j=0;j<m;j++) {
            int temp;
            cin>>temp;
            request[i][j] = temp;
        }
    }

    //calculating the need matrix

    for(int i=0;i<n;i++) {
        for(int j=0;j<m;j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    while(true) {
    cout<<endl<<endl<<"What do you want to implement, Press : "<<endl;
    cout<<"1 -> Avoidance"<<endl<<"2 -> Detection"<<endl<<"3 -> Exit"<<endl;


    int menu;cin>>menu;

    if(menu == 1) {
        int count = 0;
        vector<bool> finish(n,false);
        vector<int> work(m);
        for(int i=0;i<m;i++) {
            work[i] = available[i];
        }

        
        while(count < n) {
                    bool found = false;

        for(int i=0;i<n;i++) {
            bool flag = true;
            if(!finish[i]) {
                for(int j=0;j<m;j++) {
                    if(need[i][j] > work[j]) {
                        flag = false;
                        break;
                    }
                }

                if(flag == true) {
                    for(int j=0;j<m;j++) {
                        work[j]+=allocation[i][j];
                    }

                    finish[i] = true;
                    count++;
                    found = true;
                }
            }
        }

        if(!found) {
            break;
        }
    }

        bool safety = true;

        for(auto i : finish) {
            if(i == false) {
                safety = false;
            }
        }

        if(safety) {
            cout<<"***SYSTEM IN SAFE STATE***"<<endl;
        }

        else{
            cout<<"***NOT SAFE STATE - UNSAFE STATE***"<<endl;
        }
    }

    else if(menu == 2) {
        int count = 0;
        vector<bool> finish(n,false);
        vector<int> work(m);
        for(int i=0;i<m;i++) {
            work[i] = available[i];
        }

        for(int i=0; i<n; i++) {
                bool hasAllocation = false;
                for(int j=0; j<m; j++) {
                    if(allocation[i][j] != 0) {
                        hasAllocation = true;
                        break;
                    }
                }
                if(!hasAllocation) finish[i] = true;
            }


        while(count < n) {
                    bool found = false;

        for(int i=0;i<n;i++) {
            bool flag = true;
            if(!finish[i]) {
                for(int j=0;j<m;j++) {
                    if(request[i][j] > work[j]) {
                        flag = false;
                        break;
                    }
                }

                if(flag == true) {
                    for(int j=0;j<m;j++) {
                        work[j]+=allocation[i][j];
                    }

                    finish[i] = true;
                    count++;
                    found = true;
                }
            }
        }

        if(found == false) {
            break;
        }
    }

        bool deadlock = false;

        for(auto i : finish) {
            if(i == false) {
                deadlock = true;
                break;
            }
        }

        if(deadlock) {
            cout<<"***SYSTEM IN DEADLOCK***"<<endl;
        }

        else{
            cout<<"***NO DEADLOCK***"<<endl;
        }

    }

    else if(menu == 3) {
        break;
    }

    else {
        cout<<"Wrong input, enter value again : "<<endl;
    }

}


    return 0;   
}