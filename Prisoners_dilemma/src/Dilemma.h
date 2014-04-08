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

class Dilemma {
private:
	Chromossome *population;
	Rand *rand;

	void createFirstPopulation();
	void calculateFitness();
	void crossover();
	void mutation();

public:
	Dilemma();
	virtual ~Dilemma();


	void runGA();
};

#endif /* DILEMMA_H_ */
