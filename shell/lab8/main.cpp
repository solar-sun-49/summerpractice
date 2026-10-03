#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <iomanip>

using namespace std;

class process {
public:
    int pid;
    int arrivalTime;
    int burstTime;
    int remainingTime; // Required for Preemptive algorithms
    int waitingTime;
    int turnaroundTime;
    int completionTime;
    int priority;
    int responseTime;
    
    bool isStarted;    // Tracks if response time has been calculated
    bool isCompleted;  // Tracks if the process is fully executed

    process(int pid, int arrivalTime, int burstTime, int priority) {
        this->pid = pid;
        this->arrivalTime = arrivalTime;
        this->burstTime = burstTime;     // FIX: This was missing in your code
        this->remainingTime = burstTime; // Initialize remaining time
        this->priority = priority;

        waitingTime = 0;
        turnaroundTime = 0;
        completionTime = 0;
        responseTime = 0;
        isStarted = false;
        isCompleted = false;
    }
};

// Helper function to print metrics cleanly
void printMetrics(string algoName, const vector<process>& processes) {
    int n = processes.size();
    double totalTAT = 0, totalWT = 0, totalRT = 0;

    cout << "\n=======================================================================\n";
    cout << "--- " << algoName << " ---\n";
    cout << "PID\tAT\tBT\tPri\tCT\tTAT\tWT\tRT\n";

    for (int i = 0; i < n; i++) {
        totalTAT += processes[i].turnaroundTime;
        totalWT += processes[i].waitingTime;
        totalRT += processes[i].responseTime;

        cout << processes[i].pid << "\t"
             << processes[i].arrivalTime << "\t"
             << processes[i].burstTime << "\t"
             << processes[i].priority << "\t"
             << processes[i].completionTime << "\t"
             << processes[i].turnaroundTime << "\t"
             << processes[i].waitingTime << "\t"
             << processes[i].responseTime << "\n";
    }

    cout << fixed << setprecision(2);
    cout << "\nAvg Turnaround Time : " << totalTAT / n << " ms\n";
    cout << "Avg Waiting Time    : " << totalWT / n << " ms\n";
    cout << "Avg Response Time   : " << totalRT / n << " ms\n";
    cout << "========================================================================\n";
}


// 1. Shortest Remaining Time First (SRTF - preemptive)
void shortestRemainingTimeFirst(vector<process> processes) {
    int n = processes.size();
    int currTime = 0, completed = 0, prev_pid = -1;

    while (completed < n) {
        int idx = -1;
        int min_rem = 1e9;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currTime && !processes[i].isCompleted) {
                if (processes[i].remainingTime < min_rem) {
                    min_rem = processes[i].remainingTime;
                    idx = i;
                } else if (processes[i].remainingTime == min_rem) {
                    if (processes[i].arrivalTime < processes[idx].arrivalTime) {
                        idx = i; // Tie breaker: FCFS
                    }
                }
            }
        }

        if (idx != -1) {
            if (prev_pid != -1 && prev_pid != processes[idx].pid) currTime += 5; // 5ms Context Switch

            if (!processes[idx].isStarted) {
                processes[idx].responseTime = currTime - processes[idx].arrivalTime;
                processes[idx].isStarted = true;
            }

            processes[idx].remainingTime--;
            currTime++;

            if (processes[idx].remainingTime == 0) {
                processes[idx].completionTime = currTime;
                processes[idx].turnaroundTime = processes[idx].completionTime - processes[idx].arrivalTime;
                processes[idx].waitingTime = processes[idx].turnaroundTime - processes[idx].burstTime;
                processes[idx].isCompleted = true;
                completed++;
            }
            prev_pid = processes[idx].pid;
        } else {
            currTime++;
        }
    }
    printMetrics("1. Shortest Remaining Time First (SRTF)", processes);
}


// 2. Longest Job First (LJF - non-preemptive)
void longestJobFirst(vector<process> processes) {
    int n = processes.size();
    int currTime = 0, completed = 0, prev_pid = -1;

    while (completed < n) {
        int idx = -1;
        int max_burst = -1;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currTime && !processes[i].isCompleted) {
                if (processes[i].burstTime > max_burst) {
                    max_burst = processes[i].burstTime;
                    idx = i;
                } else if (processes[i].burstTime == max_burst) {
                    if (processes[i].arrivalTime < processes[idx].arrivalTime) {
                        idx = i; // Tie breaker: FCFS
                    }
                }
            }
        }

        if (idx != -1) {
            if (prev_pid != -1 && prev_pid != processes[idx].pid) currTime += 5; // 5ms Context Switch

            processes[idx].responseTime = currTime - processes[idx].arrivalTime;
            currTime += processes[idx].burstTime;
            
            processes[idx].completionTime = currTime;
            processes[idx].turnaroundTime = processes[idx].completionTime - processes[idx].arrivalTime;
            processes[idx].waitingTime = processes[idx].turnaroundTime - processes[idx].burstTime;
            processes[idx].isCompleted = true;
            
            completed++;
            prev_pid = processes[idx].pid;
        } else {
            currTime++;
        }
    }
    printMetrics("2. Longest Job First (LJF)", processes);
}


// 3. Highest Response Ratio Next (HRRN - non-preemptive)
void highestResponseRatioNext(vector<process> processes) {
    int n = processes.size();
    int currTime = 0, completed = 0, prev_pid = -1;

    while (completed < n) {
        int idx = -1;
        double max_rr = -1.0;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currTime && !processes[i].isCompleted) {
                double rr = (double)(currTime - processes[i].arrivalTime + processes[i].burstTime) / processes[i].burstTime;
                if (rr > max_rr) {
                    max_rr = rr;
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            if (prev_pid != -1 && prev_pid != processes[idx].pid) currTime += 5; // 5ms Context Switch

            processes[idx].responseTime = currTime - processes[idx].arrivalTime;
            currTime += processes[idx].burstTime;
            
            processes[idx].completionTime = currTime;
            processes[idx].turnaroundTime = processes[idx].completionTime - processes[idx].arrivalTime;
            processes[idx].waitingTime = processes[idx].turnaroundTime - processes[idx].burstTime;
            processes[idx].isCompleted = true;
            
            completed++;
            prev_pid = processes[idx].pid;
        } else {
            currTime++;
        }
    }
    printMetrics("3. Highest Response Ratio Next (HRRN)", processes);
}


// 4. Priority Scheduling (Preemptive)
void priorityScheduling(vector<process> processes) {
    int n = processes.size();
    int currTime = 0, completed = 0, prev_pid = -1;

    while (completed < n) {
        int idx = -1;
        int min_priority = 1e9; // Note: Assuming smaller number = higher priority

        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currTime && !processes[i].isCompleted) {
                if (processes[i].priority < min_priority) {
                    min_priority = processes[i].priority;
                    idx = i;
                } else if (processes[i].priority == min_priority) {
                    if (processes[i].arrivalTime < processes[idx].arrivalTime) {
                        idx = i; // Tie breaker: FCFS
                    }
                }
            }
        }

        if (idx != -1) {
            if (prev_pid != -1 && prev_pid != processes[idx].pid) currTime += 5; // 5ms Context Switch

            if (!processes[idx].isStarted) {
                processes[idx].responseTime = currTime - processes[idx].arrivalTime;
                processes[idx].isStarted = true;
            }

            processes[idx].remainingTime--;
            currTime++;

            if (processes[idx].remainingTime == 0) {
                processes[idx].completionTime = currTime;
                processes[idx].turnaroundTime = processes[idx].completionTime - processes[idx].arrivalTime;
                processes[idx].waitingTime = processes[idx].turnaroundTime - processes[idx].burstTime;
                processes[idx].isCompleted = true;
                completed++;
            }
            prev_pid = processes[idx].pid;
        } else {
            currTime++;
        }
    }
    printMetrics("4. Priority Scheduling (Preemptive)", processes);
}


// 5. Round Robin (RR)
void roundRobin(vector<process> processes, int quantum) {
    int n = processes.size();
    int currTime = 0, completed = 0, prev_pid = -1;
    queue<int> q;

    // Sort by arrival time to properly insert into the queue
    sort(processes.begin(), processes.end(), [](const process& a, const process& b) {
        return a.arrivalTime < b.arrivalTime;
    });

    int i = 0;
    while (i < n && processes[i].arrivalTime <= currTime) {
        q.push(i);
        i++;
    }

    while (completed < n) {
        if (q.empty()) {
            currTime++;
            while (i < n && processes[i].arrivalTime <= currTime) {
                q.push(i);
                i++;
            }
            continue;
        }

        int idx = q.front();
        q.pop();

        if (prev_pid != -1 && prev_pid != processes[idx].pid) {
            currTime += 5; // 5ms Context Switch
            // Push any process that arrives *during* context switch to the queue
            while (i < n && processes[i].arrivalTime <= currTime) {
                q.push(i);
                i++;
            }
        }

        if (!processes[idx].isStarted) {
            processes[idx].responseTime = currTime - processes[idx].arrivalTime;
            processes[idx].isStarted = true;
        }

        int execTime = min(processes[idx].remainingTime, quantum);
        currTime += execTime;
        processes[idx].remainingTime -= execTime;

        // Push processes that arrived while the current one was executing
        while (i < n && processes[i].arrivalTime <= currTime) {
            q.push(i);
            i++;
        }

        if (processes[idx].remainingTime == 0) {
            processes[idx].completionTime = currTime;
            processes[idx].turnaroundTime = processes[idx].completionTime - processes[idx].arrivalTime;
            processes[idx].waitingTime = processes[idx].turnaroundTime - processes[idx].burstTime;
            processes[idx].isCompleted = true;
            completed++;
        } else {
            q.push(idx); // Process not finished, re-add to back of the queue
        }

        prev_pid = processes[idx].pid;
    }
    
    printMetrics("5. Round Robin (Quantum = " + to_string(quantum) + "ms)", processes);
}


int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;
    
    vector<process> processes;
    processes.reserve(n);

    for (int i = 0; i < n; i++) {
        int temp1, temp2, temp3, temp4;
        cout << "\nProcess " << i + 1 << " details:" << endl;
        cout << "Enter PID: "; cin >> temp1;
        cout << "Enter Arrival Time (ms): "; cin >> temp2;
        cout << "Enter CPU Burst Time (ms): "; cin >> temp3;
        cout << "Enter Priority (smaller number = higher priority): "; cin >> temp4;

        process p(temp1, temp2, temp3, temp4);
        processes.push_back(p);
    }

    // Call algorithms passing a copy (pass-by-value triggers copy implicitly)
    shortestRemainingTimeFirst(processes);
    longestJobFirst(processes);
    highestResponseRatioNext(processes);
    priorityScheduling(processes);
    roundRobin(processes, 50);

    return 0;
}