#include <bits/stdc++.h>
using namespace std;

class MemoryAllocator {
    vector<int> memoryHoles;
    vector<int> memoryRequests;
    int totalHoles;

public:
    void init() {
        cout << "Enter number of memory holes: ";
        cin >> totalHoles;
        memoryHoles.resize(totalHoles);
        cout << "Enter memory hole sizes: ";
        for(int i = 0; i < totalHoles; i++)
            cin >> memoryHoles[i];

        int numRequests;
        cout << "Enter number of memory requests: ";
        cin >> numRequests;
        memoryRequests.resize(numRequests);
        cout << "Enter memory requests: ";
        for(int i = 0; i < numRequests; i++)
            cin >> memoryRequests[i];
    }

    void runFirstFit() {
        vector<int> holes = memoryHoles;
        cout << "\nFirst Fit Allocation:\n";
        allocate(holes, "FirstFit");
    }

    void runBestFit() {
        vector<int> holes = memoryHoles;
        cout << "\nBest Fit Allocation:\n";
        allocate(holes, "BestFit");
    }

    void runWorstFit() {
        vector<int> holes = memoryHoles;
        cout << "\nWorst Fit Allocation:\n";
        allocate(holes, "WorstFit");
    }

private:
    void allocate(vector<int>& holes, const string& strategy) {
        int externalFragmentation = 0;
        cout << "Request\tAllocated Hole\tRemaining Holes\n";

        for(int req : memoryRequests) {
            int chosenIdx = -1;
            int bestMetric = (strategy == "WorstFit") ? -1 : INT_MAX;

            for(int i = 0; i < holes.size(); i++) {
                if(holes[i] >= req) {
                    int diff = holes[i] - req;
                    if((strategy == "FirstFit" && chosenIdx == -1) ||
                       (strategy == "BestFit" && diff < bestMetric) ||
                       (strategy == "WorstFit" && holes[i] > bestMetric)) {
                        chosenIdx = i;
                        bestMetric = (strategy == "WorstFit") ? holes[i] : diff;
                        if(strategy == "FirstFit") break;
                    }
                }
            }

            if(chosenIdx != -1) {
                cout << req << "\tBlock " << chosenIdx+1 << " (" << holes[chosenIdx] << ")\t";
                holes[chosenIdx] -= req;
            } else {
                cout << req << "\tNOT ALLOCATED\t";
            }

            cout << "[";
            for(int h : holes) cout << h << " ";
            cout << "]\n";
        }

        for(int h : holes) externalFragmentation += h;
        cout << "External Fragmentation: " << externalFragmentation << endl;
    }
};

int main() {
    MemoryAllocator allocator;
    allocator.init();
    allocator.runFirstFit();
    allocator.runBestFit();
    allocator.runWorstFit();
    return 0;
}
