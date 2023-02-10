// Labyrinth.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

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
std::mutex m;
int threadHasSeenCupcake[100];
std::atomic<int> terminateThreads = 0;



void labyrinth(int index) {
	while (true) {
		//if (terminateThreads) {
		//	return;
		//}
		std::cout << counter << std::endl;

		if (counter >= 100) {
			return;
		}

		int hasSeenCupcake = threadHasSeenCupcake[index];

		if (index == 0 && cupcakeFlag == 1) {
			cupcakeFlag = 0;
			counter++;
			continue;
		}

		if (hasSeenCupcake == 1) {
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
			continue;
		}
		else if (cupcakeFlag == 0) {
			cupcakeFlag = 1;
			m.lock();
			threadHasSeenCupcake[index] = 1;
			m.unlock();
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
			continue;
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

	std::cout << "Gonna sleep" << std::endl;

	//std::this_thread::sleep_for(std::chrono::seconds(10));
	//terminateThreads = 1;
	std::cout << "Awake" << std::endl;

	for_each(threads.begin(), threads.end(), mem_fn(&thread::join));

	if (counter >= 100) {
		std::cout << "Everyone entered the labyrinth at least once." << std::endl;
	}
	else {
		std::cout << "Everyone didn't enter the labyrinth" << std::endl;
	}
	std::cout << counter << std::endl;

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
