#include "GeneticAlgorithm.h"
#include <time.h>
#include <iostream>
#include <set>
#include "Utility.h"

GeneticAlgorithm::GeneticAlgorithm(int populationSize, int generations, int tournamentGroupSize, double crossoverProbability, double mutationProbability):
	mPopulationSize{ populationSize }, mGenerations{ generations }, mTournamentGroupSize{ tournamentGroupSize }, mCrossoverProbability{ crossoverProbability }, mMutationProbability{mutationProbability}
{
}

Solution GeneticAlgorithm::run(int numberOfCities, int** adjacency)
{
	Solution best(numberOfCities, adjacency);
	srand(time(NULL));

	std::vector<Solution> currentGeneration;

	for (int i = 0; i < mPopulationSize; i++) {
		currentGeneration.push_back(Solution(numberOfCities, adjacency));
	}

	std::cout << "First Generation" << std::endl;

	for (Solution s : currentGeneration) {
		std::cout << s.toString() << std::endl;
	}

	double maxFitness = currentGeneration[0].fitness();
	best = currentGeneration[0];
	
	for (int i = 0; i < mGenerations; i++) {
		std::vector<Solution> crossedSolutions = tournamentCrossover(currentGeneration);
		std::cout << "Crossed solutions" << std::endl;

		for (Solution s : crossedSolutions) {
			s.mutate(mMutationProbability);
		}

		currentGeneration = crossedSolutions;

		//would be better to pass the best solution to the next generation
		for (int i = 0; i < mPopulationSize; i++) {
			double fitness = currentGeneration[i].fitness();

			if (fitness > maxFitness) {
				maxFitness = fitness;
				best = currentGeneration[i];
			}
		}

		std::cout << "Best (intermediate) " << best.toString();
	}

	return best;
}

Solution GeneticAlgorithm::tournamentWinner(std::vector<Solution> const& currentGeneration)
{
	std::vector<Solution> candidates;

	std::set<int> randomNumbers = randomDistinctNumbers(mPopulationSize, mTournamentGroupSize);

	for (int rn : randomNumbers) {
		candidates.push_back(currentGeneration[rn]);
	}

	Solution bestCandidate = candidates[0];
	double maxFitness = candidates[0].fitness();

	for (Solution s : candidates) {
		double fitness = s.fitness();

		if (fitness > maxFitness) {
			maxFitness = fitness;
			bestCandidate = s;
		}
	}

	return bestCandidate;
}

std::vector<Solution> GeneticAlgorithm::tournamentCrossover(std::vector<Solution> const& currentGeneration)
{
	std::vector<Solution> newSolutions;

	while (newSolutions.size() < mPopulationSize) {
		Solution winner1 = tournamentWinner(currentGeneration);
		Solution winner2 = tournamentWinner(currentGeneration);

		std::vector<Solution> children = winner1.singlePointCrossover(winner2, mCrossoverProbability);
		newSolutions.push_back(children[0]);
		newSolutions.push_back(children[1]);
	}

	return newSolutions;
}
