// FCFS CPU scheduling implementation
// The process that arrives first is served first.

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

class Process {
public:
    int pid;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;

    Process() {
        cout << "Enter PID : ";
        cin >> pid;
        cout << "Enter arrival time : ";
        cin >> arrivalTime;
        cout << "Enter burst time : ";
        cin >> burstTime;
    }
};

int main() {
    cout << "Enter number of processes : ";
    int n;
    cin >> n;

    vector<Process> processes;
    processes.reserve(n);

    for (int i = 0; i < n; i++) {
        Process p;
        processes.push_back(p);
    }

    // Sort by arrival time, and if tied, by PID
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        if (a.arrivalTime == b.arrivalTime)
            return a.pid < b.pid;
        return a.arrivalTime < b.arrivalTime;
    });

    int currentTime = 0;
    double totalWaitingTime = 0;
    double totalTurnaroundTime = 0;

    cout << "\nFCFS Scheduling Order\n";

    for (int i = 0; i < n; i++) {
        // If CPU is idle, start at process arrival
        if (currentTime < processes[i].arrivalTime) {
            currentTime = processes[i].arrivalTime;
        }

        int startTime = currentTime;
        int endTime = currentTime + processes[i].burstTime;

        processes[i].completionTime = endTime;
        processes[i].turnaroundTime = endTime - processes[i].arrivalTime;
        processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;

        totalTurnaroundTime += processes[i].turnaroundTime;
        totalWaitingTime += processes[i].waitingTime;

        cout << "Process " << processes[i].pid
             << " : start = " << startTime
             << ", finish = " << endTime
             << ", turnaround = " << processes[i].turnaroundTime
             << ", waiting = " << processes[i].waitingTime << endl;

        currentTime = endTime;
    }

    cout << fixed << setprecision(2);
    cout << "\nAverage Waiting Time = " << totalWaitingTime / n << endl;
    cout << "Average Turnaround Time = " << totalTurnaroundTime / n << endl;

    return 0;
}