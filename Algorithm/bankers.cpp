#include <bits/stdc++.h>
using namespace std;

class BankersAlgorithm {
    int n, m; // number of processes and resources
    vector<vector<int>> max, alloc, need;
    vector<int> available;

public:
    void init() {
        cout << "Enter number of processes: ";
        cin >> n;
        cout << "Enter number of resources: ";
        cin >> m;

        max.resize(n, vector<int>(m));
        alloc.resize(n, vector<int>(m));
        need.resize(n, vector<int>(m));
        available.resize(m);

        for(int i = 0; i < n; i++) {
            cout << "Process " << i+1 << ":\n";
            for(int j = 0; j < m; j++) {
                cout << "  Max for resource " << j+1 << ": ";
                cin >> max[i][j];
            }
            for(int j = 0; j < m; j++) {
                cout << "  Allocated from resource " << j+1 << ": ";
                cin >> alloc[i][j];
                need[i][j] = max[i][j] - alloc[i][j];
            }
        }

        cout << "Enter total available resources:\n";
        for(int j = 0; j < m; j++) {
            cout << "  Resource " << j+1 << ": ";
            cin >> available[j];
        }
    }

    void checkSafeState() {
        vector<int> work = available;
        vector<bool> finish(n, false);
        vector<int> safeSeq;

        while(safeSeq.size() < n) {
            bool found = false;
            for(int i = 0; i < n; i++) {
                if(!finish[i]) {
                    bool canRun = true;
                    for(int j = 0; j < m; j++) {
                        if(need[i][j] > work[j]) {
                            canRun = false;
                            break;
                        }
                    }
                    if(canRun) {
                        for(int j = 0; j < m; j++)
                            work[j] += alloc[i][j];
                        finish[i] = true;
                        safeSeq.push_back(i);
                        found = true;
                        break;
                    }
                }
            }
            if(!found) break;
        }

        if(safeSeq.size() == n) {
            cout << "The system is in a safe state.\nSafe sequence: < ";
            for(int i : safeSeq)
                cout << "P" << i+1 << " ";
            cout << ">\n";
        } else {
            cout << "The system is NOT in a safe state.\n";
        }
    }
};

int main() {
    BankersAlgorithm ba;
    ba.init();
    ba.checkSafeState();
    return 0;
}
