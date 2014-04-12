/*
 * Dilemma.h
 *
 *  Created on: Apr 8, 2014
 *      Author: reginaldo
 */

#ifndef DILEMMA_H_
#define DILEMMA_H_

class Chromossome;
class Rand;

struct Stats{
	double fitnessPopMean;
	double fitnessPopSD;
};

class Dilemma {
private:
	Chromossome *population;
	Rand *rand;
	Stats *stats;


	void createFirstPopulation();
	void calculateFitness();
	void crossover();
	void mutation();

	double calculateFitnessPopulationMean();
	double calculateFitnessPopulationSD(double fitnessMean);
	void writeMatLabScript();

public:
	Dilemma();
	virtual ~Dilemma();


	void runGA();
};

#endif /* DILEMMA_H_ */
