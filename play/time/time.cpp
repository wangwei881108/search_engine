#include <iostream>
#include <chrono>
#include <random>
#include <vector>

using namespace std;

int main(){
	
	typedef chrono::high_resolution_clock seedClock;
	seedClock::time_point beginning = seedClock::now();
	uniform_real_distribution<double> distribution(0.0, 1.0);
	double randNum;

	vector<int> indices;
	vector<bool> isMapped;	
	vector<int> mapped(5, true);
	vector<int> unmapped(5, true);
	
	for (int i=0; i<10; i++){
	        seedClock::duration d = seedClock::now() - beginning;
                mt19937 generator(d.count());
                randNum = distribution(generator);
		cout << randNum << ", " ;
	}

	cout << endl;

	return 0;
}
