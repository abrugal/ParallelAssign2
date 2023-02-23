#include <iostream>
#include <thread>
#include <vector>
#include <atomic>
#include <algorithm>
#include <functional>
#include <mutex>
#include <chrono>         // std::chrono::seconds


using namespace std;
using namespace std::chrono;


std::atomic<int> counter = 0;
std::atomic<int> cupcakeFlag = 1;
mutex m;

void labyrinth(int index) {
	bool hasSeenCupcake = false;
	while (counter < 1000) {

		// Thread 0 checks if there's a cupcake, which means that someone new entered the room
		if (index == 0) {
			m.lock();
			if (cupcakeFlag == 1) {
				cupcakeFlag = 0;
				counter++;
			}
			m.unlock();
		}
		else {
			// Only add the cupcake if it's your first time seeing an empty plate
			m.lock();
			if (cupcakeFlag == 0 && !hasSeenCupcake) {
				cupcakeFlag = 1;
				hasSeenCupcake = true;
			}
			m.unlock();
		}
	}
}

int main()
{
	vector<thread> threads;

	auto start = high_resolution_clock::now();
	for (int i = 0; i < 1000; i++) {
		threads.emplace_back(thread(labyrinth, i));
	}

	for (int i = 0; i < 1000; i++) {
		threads[i].join();
	}

	auto stop = high_resolution_clock::now();
	std::chrono::duration<double> diff = stop - start;

	if (counter >= 1000) {
		cout << "Everyone entered the labyrinth at least once in " << diff.count() << " seconds" << endl;
	}
	else {
		cout << "Everyone didn't enter the labyrinth" << endl;
	}
}
