#include<bits/stdc++.h>
using namespace std;

struct Process {
    int pid, aT, cpuT, wT, tT, ocpuT;
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
            p[i].ocpuT = p[i].cpuT;
            p[i].pid = i + 1;
        }
    }

    void runSRTN() {
        int time = 0, f = 0, prev = -1;
        while(f < n) {
            int idx = -1, mincpu = INT_MAX;
            for(int i = 0; i < n; i++) {
                if(p[i].aT <= time && p[i].cpuT > 0 && p[i].cpuT < mincpu) {
                    mincpu = p[i].cpuT;
                    idx = i;
                }
            }

            if(idx == -1) idx = prev;
            prev = idx;

            p[idx].cpuT--;
            time++;
            mincpu = p[idx].cpuT;

            if(p[idx].cpuT == 0) {
                p[idx].tT = time - p[idx].aT;
                p[idx].wT = p[idx].tT - p[idx].ocpuT;
                f++;
                mincpu = INT_MAX;
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
    s.runSRTN();
    return 0;
}
