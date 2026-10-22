#include <iostream>
#include<vector>

using namespace std;

class process {
        public:

    int pid;
    int priority;
    int at;
    int bt;
    int tat;
    int wt;
    int ct;
    int rt;
    bool completed;
    int responseTime;
    bool started;

    process() {
      
    }

    process(int pid,int at,int bt,int priority) {
        this->pid = pid;
        this->at = at;
        this->bt = bt;
        this->priority = priority;
        tat = 0;
        wt = 0;
        ct=0;
    }

};

void priorityScheduling(vector<process> processes) {
    int n = processes.size();
    int currTime = 0, completed = 0, prev_pid = -1;

    while (completed < n) {
        int idx = -1;
        int min_priority = INT_MAX; 

        for (int i = 0; i < n; i++) {
            if (processes[i].at <= currTime && !processes[i].completed) {
                if (processes[i].priority < min_priority) {
                    min_priority = processes[i].priority;
                    idx = i;
                } else if (processes[i].priority == min_priority) {
                    if (processes[i].at < processes[idx].at) {
                        idx = i; // Tie breaker: FCFS
                    }
                }
            }
        }

        if (idx != -1) {
           

            if (!processes[idx].started) {
                processes[idx].responseTime = currTime - processes[idx].at;
                processes[idx].started = true;
            }

            processes[idx].rt--;
            currTime++;

            if (processes[idx].rt == 0) {
                processes[idx].ct = currTime;
                processes[idx].tat = processes[idx].ct - processes[idx].at;
                processes[idx].wt = processes[idx].tat - processes[idx].bt;
                processes[idx].completed = true;
                completed++;
            }
            prev_pid = processes[idx].pid;
        } else {
            currTime++;
        }
    }

    for(auto i : processes) {
        cout<<i.pid<<" | "<<i.ct<<" | "<<i.tat<<" | "<<i.wt <<endl;
    }
}


int main() {
    vector<process> processes;

    int n;cout<<"Enter number of processes : ";
    cin>>n;
    processes.reserve(n);

    for(int i=0;i<n;i++) {
        int temp1,temp2,temp3,temp4;
        cout<<"Enter PID : ";
        cin>>temp1;
        cout<<"Enter arrival time : ";
        cin>>temp2;
        cout<<"Enter burst time : ";
        cin>>temp3;
        cout<<"Enter priority : ";
        cin>>temp4;
        process p(temp1,temp2,temp3,temp4);
        processes.push_back(p);
    }

    priorityScheduling(processes);


}