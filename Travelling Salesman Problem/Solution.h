#pragma once
#include <vector>
#include <string>
class Solution
{
private:
	int mNumberOfCities;
	int** mAdjacency;
	//chromosomes in the genetic algorithm
	std::vector<int> mCities;

public:
	Solution(int numberOfCities, int** adjacency);
	Solution(int numberOfCities, int** adjacency, std::vector<int> cities);
	double fitness() const;
	std::string toString() const;

	std::vector<Solution> singlePointCrossover(Solution other, double crossOverProbability) const;
	void mutate(double mutationProbability);
};

