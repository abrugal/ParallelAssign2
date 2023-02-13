#include <iostream>
#include <thread>
#include <vector>
#include <atomic>
#include <algorithm>
#include <functional>
#include <mutex>
#include <chrono>         // std::chrono::seconds


using namespace std;


std::atomic<int> counter = 0;
std::atomic<int> cupcakeFlag = 1;
mutex m;

void labyrinth(int index) {
	bool hasSeenCupcake = false;
	while (counter < 100) {
		if (index == 0) {
			m.lock();
			if (cupcakeFlag == 1) {
				cupcakeFlag = 0;
				counter++;
			}
			m.unlock();
		}
		else {
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
	for (int i = 0; i < 100; i++) {
		threads.emplace_back(thread(labyrinth, i));
	}

	for (int i = 0; i < 100; i++) {
		threads[i].join();
	}

	if (counter >= 100) {
		cout << "Everyone entered the labyrinth at least once." << endl;
	}
	else {
		cout << "Everyone didn't enter the labyrinth" << endl;
	}
	cout << counter << endl;
}
