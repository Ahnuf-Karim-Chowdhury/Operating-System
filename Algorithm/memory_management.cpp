#include<bits/stdc++.h>
using namespace std;

class MemoryAllocator {
    vector<int> memoryHoles;
    vector<int> memoryRequests;
    int totalHoles;
    
public:
    void init() {
        cout << "Enter number of memory holes: ";
        cin >> totalHoles;
        cout << "Enter memory hole sizes: ";
        for(int i = 0; i < totalHoles; i++) {
            int size;
            cin >> size;
            memoryHoles.push_back(size);
        }
        
        cout << "Enter number of memory requests: ";
        int numRequests;
        cin >> numRequests;
        cout << "Enter memory requests: ";
        for(int i = 0; i < numRequests; i++) {
            int request;
            cin >> request;
            memoryRequests.push_back(request);
        }
    }
    
    void runFirstFit() {
        vector<int> holes = memoryHoles;
        int externalFragmentation = 0;
        
        cout << "\nFirst Fit Allocation:\n";
        cout << "Request\tAllocated Hole\tRemaining Holes\n";
        
        for(int req : memoryRequests) {
            bool allocated = false;
            
            for(int i = 0; i < holes.size(); i++) {
                if(holes[i] >= req) {
                    cout << req << "\tBlock " << i+1 << " (" << holes[i] << ")\t";
                    holes[i] -= req;
                    cout << "[";
                    for(int h : holes) cout << h << " ";
                    cout << "]\n";
                    allocated = true;
                    break;
                }
            }
            
            if(!allocated) {
                cout << req << "\tNOT ALLOCATED\t[";
                for(int h : holes) cout << h << " ";
                cout << "]\n";
            }
        }
        
        for(int h : holes) externalFragmentation += h;
        cout << "External Fragmentation: " << externalFragmentation << endl;
    }
    
    void runBestFit() {
        vector<int> holes = memoryHoles;
        int externalFragmentation = 0;
        
        cout << "\nBest Fit Allocation:\n";
        cout << "Request\tAllocated Hole\tRemaining Holes\n";
        
        for(int req : memoryRequests) {
            int bestIdx = -1;
            int minDiff = INT_MAX;
            
            for(int i = 0; i < holes.size(); i++) {
                if(holes[i] >= req && (holes[i] - req) < minDiff) {
                    minDiff = holes[i] - req;
                    bestIdx = i;
                }
            }
            
            if(bestIdx != -1) {
                cout << req << "\tBlock " << bestIdx+1 << " (" << holes[bestIdx] << ")\t";
                holes[bestIdx] -= req;
                cout << "[";
                for(int h : holes) cout << h << " ";
                cout << "]\n";
            } else {
                cout << req << "\tNOT ALLOCATED\t[";
                for(int h : holes) cout << h << " ";
                cout << "]\n";
            }
        }
        
        for(int h : holes) externalFragmentation += h;
        cout << "External Fragmentation: " << externalFragmentation << endl;
    }
    
    void runWorstFit() {
        vector<int> holes = memoryHoles;
        int externalFragmentation = 0;
        
        cout << "\nWorst Fit Allocation:\n";
        cout << "Request\tAllocated Hole\tRemaining Holes\n";
        
        for(int req : memoryRequests) {
            int worstIdx = -1;
            int maxSize = -1;
            
            for(int i = 0; i < holes.size(); i++) {
                if(holes[i] >= req && holes[i] > maxSize) {
                    maxSize = holes[i];
                    worstIdx = i;
                }
            }
            
            if(worstIdx != -1) {
                cout << req << "\tBlock " << worstIdx+1 << " (" << holes[worstIdx] << ")\t";
                holes[worstIdx] -= req;
                cout << "[";
                for(int h : holes) cout << h << " ";
                cout << "]\n";
            } else {
                cout << req << "\tNOT ALLOCATED\t[";
                for(int h : holes) cout << h << " ";
                cout << "]\n";
            }
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

/* 
Enter number of memory holes: 5
Enter memory hole sizes: 100 500 200 300 600
Enter number of memory requests: 5
Enter memory requests: 212 417 112 426 */