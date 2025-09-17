#include <bits/stdc++.h>
#include <thread>
#include <mutex>
#include <condition_variable>
using namespace std;

class ProducerConsumer {
    queue<int> buffer;
    const unsigned int maxSize = 5;
    mutex mtx;
    condition_variable full, empty;

public:
    void produce(int id) {
        for(int i = 0; i < 5; i++) {
            unique_lock<mutex> lock(mtx);
            empty.wait(lock, [this](){ return buffer.size() < maxSize; });

            buffer.push(i);
            cout << "Producer " << id << " produced: " << i << endl;

            full.notify_all();
            this_thread::sleep_for(chrono::milliseconds(100));
        }
    }

    void consume(int id) {
        for(int i = 0; i < 5; i++) {
            unique_lock<mutex> lock(mtx);
            full.wait(lock, [this](){ return !buffer.empty(); });

            int item = buffer.front();
            buffer.pop();
            cout << "Consumer " << id << " consumed: " << item << endl;

            empty.notify_all();
            this_thread::sleep_for(chrono::milliseconds(150));
        }
    }
};

int main() {
    ProducerConsumer pc;
    thread p1(&ProducerConsumer::produce, &pc, 1);
    thread c1(&ProducerConsumer::consume, &pc, 1);

    p1.join();
    c1.join();
    return 0;
}
