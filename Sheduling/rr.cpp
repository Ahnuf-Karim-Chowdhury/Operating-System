#include<bits/stdc++.h>
using namespace std;
struct process {
    int pid, aT, cpuT, ocpuT, wT, tT;
} p[100];

int main() {
    int n, tq;
    cout << "Enter total process: ";
    cin >> n;
    cout << "Enter time quantum: ";
    cin >> tq;

    for(int i = 0; i < n; i++) {
        cout << "Arrival and CPU time for P" << i+1 << ": ";
        cin >> p[i].aT >> p[i].cpuT;
        p[i].ocpuT = p[i].cpuT;
        p[i].pid = i+1;
    }

    int time = 0, f = 0;
    queue<int> q;
    vector<bool> inQueue(n, false);

    while(f < n) {
        for(int i = 0; i < n; i++) {
            if(p[i].aT <= time && !inQueue[i] && p[i].cpuT > 0) {
                q.push(i);
                inQueue[i] = true;
            }
        }

        if(q.empty()) {
            time++;
            continue;
        }

        int idx = q.front(); q.pop();
        int execTime = min(tq, p[idx].cpuT);
        p[idx].cpuT -= execTime;
        time += execTime;

        for(int i = 0; i < n; i++) {
            if(p[i].aT <= time && !inQueue[i] && p[i].cpuT > 0) {
                q.push(i);
                inQueue[i] = true;
            }
        }

        if(p[idx].cpuT > 0) {
            q.push(idx);
        } else {
            p[idx].tT = time - p[idx].aT;
            p[idx].wT = p[idx].tT - p[idx].ocpuT;
            f++;
        }
    }

    for(int i = 0; i < n; i++)
        cout << "P" << p[i].pid << " WT: " << p[i].wT << " TT: " << p[i].tT << endl;
}
