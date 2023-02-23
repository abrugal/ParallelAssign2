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

	// Run until all threads have seen the vase
	while (counter != 100) {
		m.lock();
		if (threadQueue.empty()) {
			m.unlock();
			return;
		}
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

	// Queue until all threads have entered queue at least once
	while (uniqueNumsInQueue < 100) {
		int randNum = minimum + (std::rand() % (maximum - minimum + 1));

		if (numHasBeenSelected[randNum] == 0) {
			numHasBeenSelected[randNum] = 1;
			uniqueNumsInQueue += 1;
		}

		threadQueue.push(randNum);
	}

	auto start = high_resolution_clock::now();

	for (int i = 0; i < 100; i++) {
		threads.emplace_back(thread(tryToEnterRoom, i));
	}

	for (int i = 0; i < 100; i++) {
		threads[i].join();
	}

	auto stop = high_resolution_clock::now();
	std::chrono::duration<double> diff = stop - start;

	cout << "Everyone saw the vase in " << diff.count() << " seconds." << endl;

}
