#include<iostream>
#include<vector>
using namespace std;

class process{
    public:

    int pid;
    int arrivalTime;
    int burstTime;
    int waitingTime;
    int turnaroundTime;
    int completionTime;
    int priority;
    int responseTime;

    process(int pid,int arrivalTime,int burstTime,int priority) {
        this->pid = pid;
        this->arrivalTime = arrivalTime;
        this->priority = priority;

        waitingTime = 0;
        turnaroundTime = 0;
        completionTime = 0;
        responseTime = 0;
    }
};

void longestJobFirst(vector<process> processes) {
    sort(processes.begin(), processes.end(), [](const process& a, const process& b) {
        if (a.arrivalTime != b.arrivalTime) {
            return a.arrivalTime < b.arrivalTime;
        }
        return a.burstTime > b.burstTime;
    });

    int n = processes.size();

    int currTime = 0;
    int totalTuraround = 0;
    int totalWaiting = 0;
    int totalResponse = 0;

    for(int i=0;i<n;i++) {
        if(currTime < processes[i].arrivalTime) {
            currTime = processes[i].arrivalTime;
        }

        currTime += processes[i].burstTime;

        processes[i].completionTime = currTime;
        processes[i].turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;
        
        totalTuraround += processes[i].turnaroundTime;
        totalWaiting += processes[i].waitingTime;


        cout<<"Process : " << processes[i].pid << "| Arrival Time : " << processes[i].arrivalTime << "| Completion time : " << processes[i].completionTime << "| Turnaround time : " <<processes[i].turnaroundTime << "| Waiting time : " << processes[i].waitingTime<<endl;
        
        
    }

    cout<<"Avg Turnaround Time : "<<totalTuraround/n<<endl;
    cout<<"Avg Waiting Time : "<<totalWaiting/n<<endl;
}

int main() {

    cout<<"Enter number of processes : ";int n;cin>>n;
    vector<process> processes;
    processes.reserve(n);

    for(int i=0;i<n;i++) {
        int temp1,temp2,temp3;
        cout<<"Enter PID : ";cin>>temp1;
        cout<<"Enter Arrival Time : ";cin>>temp2;
        cout<<"Enter Burst Time : ";cin>>temp3;

        process p(temp1,temp2,temp3,0);
        processes.push_back(p);

    }

    longestJobFirst(processes);

    return 0;
}