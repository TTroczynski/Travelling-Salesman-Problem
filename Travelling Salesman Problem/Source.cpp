#include <iostream>
#include <fstream>
#include "GeneticAlgorithm.h"

int main(void) {
	
	std::ifstream inFile;

	inFile.open("graph.txt");

	if (!inFile.is_open()) {
		throw std::runtime_error("Input file error");
	}
	int numberOfCities;
	inFile >> numberOfCities;

	int** adjacencyM = new int* [numberOfCities];

	for (int i = 0; i < numberOfCities; i++) {

		adjacencyM[i] = new int[numberOfCities];

		for (int j = 0; j < numberOfCities; j++) {
			if (i == j) {
				//distance from a city to itself is 0
				adjacencyM[i][j] = 0;
			}
			else {
				adjacencyM[i][j] = INT_MAX;
			}
		}
	}

	while (inFile.good()) {
		int fromCity;
		int toCity;
		int distance;

		inFile >> fromCity;
		inFile >> toCity;
		inFile >> distance;

		std::cout << "From " << fromCity << " to " << toCity << " distance = " << distance << std::endl;

		//adjacency matrices are essentially grids that represent cities that can be visited.
		//From A to B, is same as From B to A. The indices represent the cities. 
		//And adjacency matrices can be symmetrical

		adjacencyM[fromCity - 1][toCity - 1] = distance;
		adjacencyM[toCity - 1][fromCity - 1] = distance;
	}

	for (int i = 0; i < numberOfCities; i++) {
		for (int j = 0; j < numberOfCities; j++) {
			std::cout << adjacencyM[i][j] << ' ';
		}
		std::cout << std::endl;
	}

	inFile.close();

	int populationSize = 10;
	int generations = 10;
	int tournamentGroupSize = 3;
	double crossoverProbability = 0.7;
	double mutationProbability = 0.01;

	GeneticAlgorithm ga(populationSize, generations, tournamentGroupSize, crossoverProbability, mutationProbability);

	Solution bestSolution = ga.run(numberOfCities, adjacencyM);

	std::cout << std::endl << "Best Solution = " << bestSolution.toString() << std::endl;

	for (int i = 0; i < numberOfCities; i++) {
		delete[] adjacencyM[i];
	}
	delete[] adjacencyM;
	
	return 0;
}