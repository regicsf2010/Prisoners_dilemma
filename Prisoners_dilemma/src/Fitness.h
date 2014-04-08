/*
 * Fitness.h
 *
 *  Created on: Apr 8, 2014
 *      Author: reginaldo
 */

#ifndef FITNESS_H_
#define FITNESS_H_

#include "Chromossome.h"

enum FitnessType{PAIR, HALF_POPULATION, ALL_POPULATION, NONE};

class Fitness {
private:
	static FitnessType fitType;

public:
	Fitness(){};
	virtual ~Fitness();


	inline static void setFitnessType(FitnessType fitType){
		Fitness::fitType = fitType;
	}

	inline static void calculateFitness(Chromossome *population){
		switch(Fitness::fitType){
		case PAIR:
			break;
		case HALF_POPULATION:
			break;
		case ALL_POPULATION:
			break;
		case NONE:
			// nothing to be done
			break;
		}
	}

};

FitnessType Fitness::fitType = NONE;

#endif /* FITNESS_H_ */
