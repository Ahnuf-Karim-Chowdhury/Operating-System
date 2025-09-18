#include <bits/stdc++.h>
using namespace std;

class MemoryAllocator {
    vector<int> memoryHoles;
    vector<int> memoryRequests;

public:
    MemoryAllocator(const vector<int>& holes, const vector<int>& requests) {
        memoryHoles = holes;
        memoryRequests = requests;
    }

    void runFirstFit() {
        vector<int> holes = memoryHoles;
        int internalFragmentation = 0;
        int externalFragmentation = 0;

        cout << "\nFirst Fit Allocation:\n";
        cout << "Request\tAllocated Hole\tRemaining Holes\n";

        for (int req : memoryRequests) {
            bool allocated = false;

            for (int i = 0; i < holes.size(); i++) {
                if (holes[i] >= req) {
                    internalFragmentation += holes[i] - req;
                    cout << req << "\tBlock " << i + 1 << " (" << holes[i] << ")\t";
                    holes[i] -= req;
                    allocated = true;
                    break;
                }
            }

            if (!allocated) {
                cout << req << "\tNOT ALLOCATED\t";
            }

            cout << "[ ";
            for (int h : holes) cout << h << " ";
            cout << "]\n";
        }

        int largestRequest = *max_element(memoryRequests.begin(), memoryRequests.end());
        for (int h : holes) {
            if (h < largestRequest) externalFragmentation += h;
        }

        cout << "Internal Fragmentation: " << internalFragmentation << endl;
        cout << "External Fragmentation: " << externalFragmentation << endl;
    }

    void runBestFit() {
        vector<int> holes = memoryHoles;
        int internalFragmentation = 0;
        int externalFragmentation = 0;

        cout << "\nBest Fit Allocation:\n";
        cout << "Request\tAllocated Hole\tRemaining Holes\n";

        for (int req : memoryRequests) {
            int bestIdx = -1;
            int minDiff = INT_MAX;

            for (int i = 0; i < holes.size(); i++) {
                if (holes[i] >= req && (holes[i] - req) < minDiff) {
                    minDiff = holes[i] - req;
                    bestIdx = i;
                }
            }

            if (bestIdx != -1) {
                internalFragmentation += holes[bestIdx] - req;
                cout << req << "\tBlock " << bestIdx + 1 << " (" << holes[bestIdx] << ")\t";
                holes[bestIdx] -= req;
            } else {
                cout << req << "\tNOT ALLOCATED\t";
            }

            cout << "[ ";
            for (int h : holes) cout << h << " ";
            cout << "]\n";
        }

        int largestRequest = *max_element(memoryRequests.begin(), memoryRequests.end());
        for (int h : holes) {
            if (h < largestRequest) externalFragmentation += h;
        }

        cout << "Internal Fragmentation: " << internalFragmentation << endl;
        cout << "External Fragmentation: " << externalFragmentation << endl;
    }

    void runWorstFit() {
        vector<int> holes = memoryHoles;
        int internalFragmentation = 0;
        int externalFragmentation = 0;

        cout << "\nWorst Fit Allocation:\n";
        cout << "Request\tAllocated Hole\tRemaining Holes\n";

        for (int req : memoryRequests) {
            int worstIdx = -1;
            int maxSize = -1;

            for (int i = 0; i < holes.size(); i++) {
                if (holes[i] >= req && holes[i] > maxSize) {
                    maxSize = holes[i];
                    worstIdx = i;
                }
            }

            if (worstIdx != -1) {
                internalFragmentation += holes[worstIdx] - req;
                cout << req << "\tBlock " << worstIdx + 1 << " (" << holes[worstIdx] << ")\t";
                holes[worstIdx] -= req;
            } else {
                cout << req << "\tNOT ALLOCATED\t";
            }

            cout << "[ ";
            for (int h : holes) cout << h << " ";
            cout << "]\n";
        }

        int largestRequest = *max_element(memoryRequests.begin(), memoryRequests.end());
        for (int h : holes) {
            if (h < largestRequest) externalFragmentation += h;
        }

        cout << "Internal Fragmentation: " << internalFragmentation << endl;
        cout << "External Fragmentation: " << externalFragmentation << endl;
    }
};

int main() {
    vector<int> holes = {100, 500, 200, 300, 600};
    vector<int> requests = {212, 417, 112, 426};

    MemoryAllocator allocator(holes, requests);
    allocator.runFirstFit();
    allocator.runBestFit();
    allocator.runWorstFit();

    return 0;
}
