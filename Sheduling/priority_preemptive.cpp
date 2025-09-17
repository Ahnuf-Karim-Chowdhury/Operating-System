#include<bits/stdc++.h>
using namespace std;

struct Process {
    int pid, aT, cpuT, ocpuT, prio, wT, tT;
};

class Scheduler {
    Process p[100];
    int n;

public:
    void init() {
        cout << "Enter total process: ";
        cin >> n;
        for(int i = 0; i < n; i++) {
            cout << "Arrival, CPU time and Priority for P" << i+1 << ": ";
            cin >> p[i].aT >> p[i].cpuT >> p[i].prio;
            p[i].ocpuT = p[i].cpuT;
            p[i].pid = i + 1;
        }
    }

    void runPriorityPreemptive() {
        int time = 0, f = 0;
        while(f < n) {
            int idx = -1, minPrio = INT_MAX;
            for(int i = 0; i < n; i++) {
                if(p[i].aT <= time && p[i].cpuT > 0 && p[i].prio < minPrio) {
                    minPrio = p[i].prio;
                    idx = i;
                }
            }

            if(idx == -1) {
                time++;
                continue;
            }

            p[idx].cpuT--;
            time++;

            if(p[idx].cpuT == 0) {
                p[idx].tT = time - p[idx].aT;
                p[idx].wT = p[idx].tT - p[idx].ocpuT;
                f++;
            }
        }

        for(int i = 0; i < n; i++) {
            cout << "P" << p[i].pid << " WT: " << p[i].wT << " TT: " << p[i].tT << endl;
        }
    }
};

int main() {
    Scheduler s;
    s.init();
    s.runPriorityPreemptive();
    return 0;
}
