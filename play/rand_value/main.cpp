#include <iostream>
#include <random>
#include <chrono>

int main(){
	typedef std::chrono::high_resolution_clock myclock;
	myclock::time_point beginning = myclock::now();

	std::mt19937 generator(beginning.time_since_epoch().count());
	
	std::uniform_real_distribution<double> distribution(0.0,1.0);
	double number = distribution(generator);
	std::cout << "the first: " << number << std::endl;

	for(int i=0; i<3; i++){
		myclock::duration d = myclock::now() - beginning;
		unsigned seed = d.count();
		generator.seed(seed);
		std::cout << "As time passing: " << distribution(generator) << std::endl;
	}
	

}
