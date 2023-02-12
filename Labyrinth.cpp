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
std::atomic<int> terminateThreads = 0;



void labyrinth(int index) {
	bool hasSeenCupcake = false;
	while (true) {
		std::cout << counter << std::endl;

		if (counter >= 100) {
			return;
		}

		if (index == 0 && cupcakeFlag == 1) {
			cupcakeFlag = 0;
			counter++;
		} else if (!hasSeenCupcake && cupcakeFlag == 0) {
			cupcakeFlag = 1;
			hasSeenCupcake = true;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

int main()
{
	vector<thread> threads;

	for (int i = 0; i < 100; i++) {
		threads.emplace_back(thread(labyrinth, i));
	}

	for_each(threads.begin(), threads.end(), mem_fn(&thread::join));

	if (counter >= 100) {
		std::cout << "Everyone entered the labyrinth at least once." << std::endl;
	}
	else {
		std::cout << "Everyone didn't enter the labyrinth" << std::endl;
	}
	std::cout << counter << std::endl;
}
