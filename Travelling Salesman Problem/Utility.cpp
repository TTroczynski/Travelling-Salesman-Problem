#include "Utility.h"
#include <stdexcept>

double randomDouble() {
	return (double)(rand() % 1000) / 1000;
}
bool randomProbability(double probability) {
	if (probability < 0 || probability > 1) {
		throw std::runtime_error("Probability should be between 0 and 1");
	}

	double r = randomDouble();
	if (r < probability) {
		return true;
	}
	return false;
}
double precision(int low, int high, int numberOfBits) {
	double prec = (double)(high - low) / (double)(pow(2, numberOfBits) - 1);
	return prec;
}
std::set<int> randomDistinctNumbers(int upperLimit, int howManyNumbers) {
	std::set<int> numbers;
	while (numbers.size() < howManyNumbers) {
		numbers.insert(rand() % upperLimit);
	}
	return numbers;
}