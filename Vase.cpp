#include <iostream>
#include <thread>
#include <vector>
#include <atomic>
#include <algorithm>
#include <functional>
#include <mutex>
#include <chrono>         // std::chrono::seconds
#include <queue>
#include <cstdlib>


using namespace std;
using namespace std::chrono;


queue<int> threadQueue;
atomic<bool> emptyRoom = true;
atomic<int> counter = 0;
mutex m;
int minimum = 0;
int maximum = 99;


void enterRoom() {
	m.lock();
	threadQueue.pop();
	m.unlock();
}


void tryToEnterRoom(int index) {
	bool hasEntered = false;
	bool inQueue = false;

	// Run until all threads have seen the vase
	while (counter != 100) {

		if (inQueue) {
			m.lock();
			int firstInLine = threadQueue.front();
			m.unlock();

			// Only first in line can enter the room
			if (firstInLine == index) {
				if (emptyRoom) {
					m.lock();
					emptyRoom = false;
					m.unlock();
					if (!hasEntered) {
						hasEntered = true;
						counter = counter + 1;
					}

					enterRoom();

					m.lock();
					emptyRoom = true;
					m.unlock();
					inQueue = false;
				}
			}
		}
		else {
			int randNum = rand() % 2 + 1;
			if (randNum % 2 == 0) {
				m.lock();
				threadQueue.push(index);
				m.unlock();
				inQueue = true;
			}
		}
	}
}


int main()
{
	vector<thread> threads;
	int numHasBeenSelected[100] = { 0 };
	int uniqueNumsInQueue = 0;


	srand(time(0));

	auto start = high_resolution_clock::now();

	for (int i = 0; i < 100; i++) {
		threads.emplace_back(thread(tryToEnterRoom, i));
	}

	for (int i = 0; i < 100; i++) {
		threads[i].join();
	}

	auto stop = high_resolution_clock::now();
	std::chrono::duration<double> diff = stop - start;

	std::cout << "Everyone saw the vase in " << diff.count() << " seconds." << endl;
}
