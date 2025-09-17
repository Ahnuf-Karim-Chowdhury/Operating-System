#include<bits/stdc++.h>
using namespace std;

struct Process {
    int pid, aT, cpuT, wT, tT, st;
};

class Scheduler {
    Process p[100];
    int n;

public:
    void init() {
        cout << "Enter total process: ";
        cin >> n;
        for(int i = 0; i < n; i++) {
            cout << "Arrival and CPU time for P" << i+1 << ": ";
            cin >> p[i].aT >> p[i].cpuT;
            p[i].pid = i + 1;
            p[i].st = 0;
        }
    }

    void runSJF() {
        int time = 0, f = 0;
        while(f < n) {
            int idx = -1, mincpu = INT_MAX;
            for(int i = 0; i < n; i++) {
                if(p[i].aT <= time && p[i].st == 0 && p[i].cpuT < mincpu) {
                    mincpu = p[i].cpuT;
                    idx = i;
                }
            }
            if(idx == -1) {
                time++;
                continue;
            }
            p[idx].st = 1;
            time += p[idx].cpuT;
            p[idx].tT = time - p[idx].aT;
            p[idx].wT = p[idx].tT - p[idx].cpuT;
            f++;
        }

        for(int i = 0; i < n; i++) {
            cout << "P" << p[i].pid << " WT: " << p[i].wT << " TT: " << p[i].tT << endl;
        }
    }
};

int main() {
    Scheduler s;
    s.init();
    s.runSJF();
    return 0;
}
