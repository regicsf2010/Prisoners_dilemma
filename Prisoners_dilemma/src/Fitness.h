/*
 * Fitness.h
 *
 *  Created on: Apr 8, 2014
 *      Author: reginaldo
 */

#ifndef FITNESS_H_
#define FITNESS_H_

#include "Chromossome.h"

enum FitnessType{PAIR, HALF_POPULATION, ALL_POPULATION};
enum FitnessEvaluation{INDIVIDUAL, GROUP};

class Fitness {
private:
	static FitnessType fitType;
	static FitnessEvaluation fitEval;
	static double CC, DD, CD, DC;

	inline static void configureDecisions(){
		switch(fitEval){
		case INDIVIDUAL:
			CD = 1.0;
			CC = 0.7;
			DD = 0.4;
			DC = 0.1;
			break;
		case GROUP:
			CD = 0.6;
			CC = 1.0;
			DD = 0.1;
			DC = 0.6;
			break;
		}
	}

	inline static double evaluateDecision(bool val1, bool val2){
		if(val1){
			if(val2)
				return DD;
			else
				return DC;
		} else{
			if(val2)
				return CD;
			else
				return CC;
		}
	}

public:
	Fitness(){};
	virtual ~Fitness();


	inline static void setFitnessConfiguration(FitnessType fitType, FitnessEvaluation fitEval){
		Fitness::fitType = fitType;
		Fitness::fitEval = fitEval;
	}

	inline static void calculateFitness(Chromossome *population){
		Fitness::configureDecisions();
		switch(Fitness::fitType){
		case PAIR:
			break;
		case HALF_POPULATION:
			break;
		case ALL_POPULATION:
			break;
		}
	}

};

FitnessType Fitness::fitType = PAIR;
FitnessEvaluation Fitness::fitEval = INDIVIDUAL;
double Fitness::CC = 0;
double Fitness::CD = 0;
double Fitness::DC = 0;
double Fitness::DD = 0;

#endif /* FITNESS_H_ */
