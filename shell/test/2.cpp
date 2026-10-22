#include <iostream>
#include<vector>

using namespace std;

class process {
        public:

    int pid;
    int at;
    int bt;
    int tat;
    int wt;
    int ct;

    process() {
       wt =0;
       tat =0;
       ct = 0;
    }

    process(int pid,int at,int bt) {
        this->pid = pid;
        this->at = at;
        this->bt = bt;
        tat = 0;
        wt = 0;
        ct=0;
    }

};

int main() {

    int n;cout<<"Enter number of processes : "<<endl;
    cin>>n;


    vector<process> processes;
    processes.reserve(n);

    for(int i=0;i<n;i++) {
        int temp1,temp2,temp3;
        cout<<"Enter PID : ";
        cin>>temp1;
        cout<<"Enter arrival time : ";
        cin>>temp2;
        cout<<"Enter burst time : ";
        cin>>temp3;
        process p(temp1,temp2,temp3);
        processes.push_back(p);
        
    }


    
    int SUMtat = 0;
    int SUMwt = 0;

    vector<bool> completed(n,false);
    int curr = 0;
    int done = 0;
    int idx = 0;


    while(done < n) {
        int min = INT_MAX;
        for(int i=0;i<n;i++) {
            if(processes[i].at < min && !completed[i]) {
                min = processes[i].at;
                idx = i;
            }

            if(processes[i].at == processes[idx].at && !completed[i]) {
                if(processes[i].bt < processes[idx].bt) {
                    idx = i;
                }
            }
        }

        curr+=processes[idx].bt;
        processes[idx].ct = curr;
        processes[idx].tat = processes[idx].ct - processes[idx].at;
        processes[idx].wt = processes[idx].tat - processes[idx].bt;
        done++;
        completed[idx] = true;

        SUMtat += processes[idx].tat;
        SUMwt += processes[idx].wt;

    }


    for(auto i : processes) {
        cout<<i.pid<<" | "<<i.at << " | " <<i.bt << " | "<<i.ct<<" | "<<i.tat<<" | "<<i.wt<<endl;
    }

    cout<<"avg tat " <<SUMtat/n;
    cout<<"avg wt "<<SUMwt/n;
    

    return 0;
}