#include <bits/stdc++.h>
#include <thread>
#include <mutex>
using namespace std;

class ReaderWriter {
    int readerCount = 0;
    mutex mtx, writeLock;

public:
    void reader(int id) {
        for(int i = 0; i < 3; i++) {
            {
                lock_guard<mutex> lock(mtx);
                readerCount++;
                if(readerCount == 1)
                    writeLock.lock();
            }

            cout << "Reader " << id << " is reading\n";
            this_thread::sleep_for(chrono::milliseconds(100));

            {
                lock_guard<mutex> lock(mtx);
                readerCount--;
                if(readerCount == 0)
                    writeLock.unlock();
            }

            this_thread::sleep_for(chrono::milliseconds(100));
        }
    }

    void writer(int id) {
        for(int i = 0; i < 2; i++) {
            writeLock.lock();
            cout << "Writer " << id << " is writing\n";
            this_thread::sleep_for(chrono::milliseconds(200));
            writeLock.unlock();

            this_thread::sleep_for(chrono::milliseconds(150));
        }
    }
};

int main() {
    ReaderWriter rw;
    thread r1(&ReaderWriter::reader, &rw, 1);
    thread r2(&ReaderWriter::reader, &rw, 2);
    thread w1(&ReaderWriter::writer, &rw, 1);

    r1.join();
    r2.join();
    w1.join();
    return 0;
}
