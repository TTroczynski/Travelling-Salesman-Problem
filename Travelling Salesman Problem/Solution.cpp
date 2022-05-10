#include "Solution.h"
#include <sstream>
#include "Utility.h"
#include <iostream>
#include <algorithm>

Solution::Solution(int numberOfCities, int** adjacency) : mNumberOfCities{ numberOfCities }, mAdjacency{ adjacency } {

	for (int i = 0; i < mNumberOfCities; i++) {
		mCities.push_back(i);
	}

	std::random_shuffle(mCities.begin(), mCities.end());
}

Solution::Solution(int numberOfCities, int** adjacency, std::vector<int> cities) : mNumberOfCities{ numberOfCities }, mAdjacency{ adjacency }, mCities{ cities } {

}

double Solution::fitness() const {
	int totalDistance = 0;

	//-1 because we i + 1
	for (int i = 0; i < mNumberOfCities - 1l; i++) {
		int from = mCities[i];
		int to = mCities[i + 1];
		int distance = mAdjacency[to][from];
		totalDistance += distance;
	}

	//from the last back to the first
	int last = mNumberOfCities - 1;
	totalDistance += mAdjacency[0][last];

	return totalDistance * (-1);
}

std::string Solution::toString() const {

	std::ostringstream stream;
	stream << "[";
	for (int city : mCities) {
		stream << city << " ";
	}
	stream << "] fitness = " << fitness();

	return stream.str();
}

//cant really do a single point cross over because we cant allow for repeated occurances of the same cities.
//so we select a single crossover point for the first N number of cities, and then add the cities from the other set
//if they dont already exist until the crossed set is complete.
std::vector<Solution> Solution::singlePointCrossover(Solution other, double crossOverProbability) const {

	bool cross = randomProbability(crossOverProbability);

	if (cross) {
		
		int crossPoint = rand() % mNumberOfCities;

		std::cout << std::endl << "Crossed " << this->toString() << " x " << other.toString() << " at point " << crossPoint << std::endl;

		std::vector<int> cities1;
		std::vector<int> cities2;

		std::copy(this->mCities.begin(), this->mCities.begin() + crossPoint, std::back_inserter(cities1));

		int position = crossPoint;

		//copied all cities in this-> to cities1 up to the crossover point
		//now need to fill in the rest with the other solution vectors cities after the crossover point
		//without adding duplicates
		while (cities1.size() < mNumberOfCities) {
			int currentCity = other.mCities[position];

			bool exists = false;

			for (int c : cities1) {
				if (c == currentCity) {
					exists = true;
					break;
				}
			}

			if (!exists) {
				cities1.push_back(currentCity);
			}

			position++;

			if (position >= mNumberOfCities) {
				position = 0;
			}
		}

		std::copy(other.mCities.begin(), other.mCities.begin() + crossPoint, std::back_inserter(cities2));

		position = crossPoint;

		while (cities2.size() < mNumberOfCities) {
			int currentCity = this->mCities[position];

			bool exists = false;

			for (int c : cities2) {
				if (c == currentCity) {
					exists = true;
					break;
				}
			}

			if (!exists) {
				cities2.push_back(currentCity);
			}

			position++;

			if (position >= mNumberOfCities) {
				position = 0;
			}
		}

		Solution child1(mNumberOfCities, mAdjacency, cities1);
		Solution child2(mNumberOfCities, mAdjacency, cities2);

		std::cout << "Children = " << child1.toString() << " & " << child2.toString() << std::endl;

		return { child1, child2 };
	
	}
	else {
		return { *this, other };
	}

}
void Solution::mutate(double mutationProbability) {

}