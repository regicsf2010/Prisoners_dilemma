/*
 * Dilemma.h
 *
 *  Created on: Apr 8, 2014
 *      Author: reginaldo
 */

#ifndef DILEMMA_H_
#define DILEMMA_H_

class Chromosome;
class Rand;

struct Stats{
	double popFitnessMean;
	double popFitnessSD;
	double popBestFitness;
};

class Dilemma {
private:
	Chromosome *population;
	Rand *rand;
	Stats *stats;


	void createFirstPopulation();
	void calculateFitness();
	void crossover();
	void mutation();

	double calculateFitnessPopulationMean();
	double calculateFitnessPopulationSD(double fitnessMean);
	double calculateBestFitnessPopulation();
	void sortPopulation();
	static int compare(const void *x, const void *y);
	void writeMatLabScript();

public:
	Dilemma();
	virtual ~Dilemma();


	void runGA();
};

#endif /* DILEMMA_H_ */
