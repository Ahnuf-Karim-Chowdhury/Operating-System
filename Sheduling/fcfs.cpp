#include<bits/stdc++.h>
using namespace std;

struct Process {
    int pid, cpuT, aT, wT, tT;
};

bool sortByAT(Process a, Process b) {
    return a.aT < b.aT;
}

bool sortByPID(Process a, Process b) {
    return a.pid < b.pid;
}

class Scheduler {
    Process p[100];
    int n;

public:
    void init() {
        cout << "Enter total process: ";
        cin >> n;
        for(int i = 0; i < n; i++) {
            cout << "Enter CPU time and arrival time for P" << i+1 << ": ";
            cin >> p[i].cpuT >> p[i].aT;
            p[i].pid = i + 1;
        }
    }

    void runFCFS() {
        sort(p, p + n, sortByAT);
        int time = 0;
        for(int i = 0; i < n; i++) {
            p[i].tT = time + p[i].cpuT - p[i].aT;
            p[i].wT = p[i].tT - p[i].cpuT;
            time += p[i].cpuT;
        }
        sort(p, p + n, sortByPID);
        for(int i = 0; i < n; i++) {
            cout << "P" << p[i].pid << " -> WT: " << p[i].wT << " TT: " << p[i].tT << endl;
        }
    }
};

int main() {
    Scheduler s;
    s.init();
    s.runFCFS();
    return 0;
}
