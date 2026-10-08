#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>
#include <algorithm>

using namespace std;

struct Process {
    int id, at, bt, rem_bt, ct, tat, wt, rt;
    bool first_time;
};

struct GanttSegment {
    int id, start_time, end_time;
};

bool compareByArrival(const Process& a, const Process& b) {
    if (a.at == b.at) return a.id < b.id;
    return a.at < b.at;
}

bool compareByID(const Process& a, const Process& b) {
    return a.id < b.id;
}

int main() {
    int n, tq;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> p(n);
    cout << "Enter Arrival Time and Burst Time for each process:\n";
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        cout << "Process P" << p[i].id << " AT: ";
        cin >> p[i].at;
        cout << "Process P" << p[i].id << " BT: ";
        cin >> p[i].bt;
        p[i].rem_bt = p[i].bt;
        p[i].first_time = true;
    }

    cout << "Enter Time Quantum: ";
    cin >> tq;

    sort(p.begin(), p.end(), compareByArrival);

    queue<int> q;
    vector<GanttSegment> gantt;
    
    int current_time = 0, completed = 0, idx = 0;
    vector<bool> inQueue(n, false);

    // Handle initial CPU idle time
    if (idx < n && p[idx].at > current_time) {
        gantt.push_back({-1, current_time, p[idx].at});
        current_time = p[idx].at;
    }

    q.push(idx);
    inQueue[idx++] = true;

    while (completed < n) {
        if (q.empty()) {
            if (idx < n) {
                gantt.push_back({-1, current_time, p[idx].at});
                current_time = p[idx].at;
                q.push(idx);
                inQueue[idx++] = true;
            }
            continue;
        }

        int i = q.front();
        q.pop();

        if (p[i].first_time) {
            p[i].rt = current_time - p[i].at;
            p[i].first_time = false;
        }

        int exec_time = min(p[i].rem_bt, tq);
        gantt.push_back({p[i].id, current_time, current_time + exec_time});
        
        current_time += exec_time;
        p[i].rem_bt -= exec_time;

        // Enqueue newly arrived processes during execution
        while (idx < n && p[idx].at <= current_time) {
            q.push(idx);
            inQueue[idx++] = true;
        }

        if (p[i].rem_bt > 0) {
            q.push(i);
        } else {
            p[i].ct = current_time;
            p[i].tat = p[i].ct - p[i].at;
            p[i].wt = p[i].tat - p[i].bt;
            completed++;
        }
    }

    sort(p.begin(), p.end(), compareByID);

    // --- Render Gantt Chart ---
    cout << "\n========== GANTT CHART ==========\n";
    for (size_t i = 0; i < gantt.size(); i++) cout << "-------";
    cout << "\n";
    
    for (const auto& g : gantt) {
        cout << "| ";
        if (g.id == -1) cout << setw(4) << left << "IDLE";
        else cout << "P" << setw(3) << left << g.id;
    }
    cout << "|\n";

    for (size_t i = 0; i < gantt.size(); i++) cout << "-------";
    cout << "\n";
    
    for (const auto& g : gantt) {
        cout << left << setw(7) << g.start_time;
    }
    cout << gantt.back().end_time << "\n";
    cout << "=================================\n";

    // --- Render Process Table ---
    cout << "\nPROCESS METRICS TABLE:\n";
    cout << left << setw(10) << "Process"
         << setw(10) << "AT" << setw(10) << "BT" << setw(10) << "CT"
         << setw(10) << "TAT" << setw(10) << "WT" << setw(10) << "RT" << "\n";

    float sum_wt = 0, sum_tat = 0;
    for (const auto& process : p) {
        cout << "P" << left << setw(9) << process.id
             << setw(10) << process.at << setw(10) << process.bt
             << setw(10) << process.ct << setw(10) << process.tat
             << setw(10) << process.wt << setw(10) << process.rt << "\n";
             
        sum_wt += process.wt;
        sum_tat += process.tat;
    }

    cout << fixed << setprecision(2);
    cout << "\nAverage Waiting Time    : " << (sum_wt / n) << " ms\n";
    cout << "Average Turnaround Time : " << (sum_tat / n) << " ms\n";

    return 0;
}