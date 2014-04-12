/*
 * Fitness.h
 *
 *  Created on: Apr 8, 2014
 *      Author: reginaldo
 */

#ifndef FITNESS_H_
#define FITNESS_H_

#include "Chromosome.h"
#include "../RNumbers/Rand.h"

enum FitnessType {
	PAIR, HALF_POPULATION, ALL_POPULATION
};
enum FitnessEvaluation {
	INDIVIDUAL, GROUP
};

class Fitness {
private:
	Fitness() {};
	static FitnessType fitType;
	static FitnessEvaluation fitEval;
	static double CC, DD, CD, DC;
	static Rand *rand;

	inline static void configureDecisions() {
		switch (fitEval) {
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

	inline static double evaluateDecision(bool val1, bool val2) {
		if (val1) {
			if (val2)
				return DD;
			else
				return DC;
		} else {
			if (val2)
				return CD;
			else
				return CC;
		}
	}

	inline static double bonus(bool &oldVal, bool actualVal, int &count) {
		if (!actualVal && !oldVal) {
			count++;
			if (count == SEQUENCE_BONUS - 1) {
				count = 0;
				oldVal = true;
				return BONUS;
			}
		}
		oldVal = actualVal;
		count = 0;
		return 0;
	}

public:
	virtual ~Fitness();

	inline static void setFitnessConfiguration(FitnessType fitType, FitnessEvaluation fitEval) {
		Fitness::fitType = fitType;
		Fitness::fitEval = fitEval;
	}

	inline static void calculateFitness(Chromosome *population) {
		Fitness::configureDecisions();
		switch (Fitness::fitType) {
		case PAIR:
			for (int i = 0; i < NPOPULATION; i += 2) {
				double fitness1 = 0, fitness2 = 0;
				int count1 = 0, count2 = 0;
				bool oldVal1 = true, oldVal2 = true;

				for (int j = 0; j < NGENES; ++j) {
					fitness1 += evaluateDecision(population[i].getGene(j), population[i + 1].getGene(j));
					fitness1 += bonus(oldVal1, population[i].getGene(j), count1);
					fitness2 += evaluateDecision(population[i + 1].getGene(j), population[i].getGene(j));
					fitness2 += bonus(oldVal2, population[i + 1].getGene(j), count2);
				}
				population[i].setFitness(fitness1 / NGENES);
				population[i + 1].setFitness(fitness2 / NGENES);
			}
			break;
		case HALF_POPULATION:
			rand->SetSeed();
			for (int i = 0; i < NPOPULATION; ++i) {
				double parcialFitness = 0, realFitness = 0;
				int selected = 0, count = 0;
				bool oldVal1 = true;

				for (int j = 0; j < NPOPULATION / 2; ++j) {
					selected = rand->RandInt(NPOPULATION);
					while (i == selected)
						selected = rand->RandInt(NPOPULATION);

					for (int g = 0; g < NGENES; ++g) {
						parcialFitness += evaluateDecision(population[i].getGene(g), population[selected].getGene(g));
						parcialFitness += bonus(oldVal1, population[i].getGene(g), count);
					}
					realFitness += (parcialFitness / NGENES);
					parcialFitness = 0;
				}
				population[i].setFitness(realFitness / (NPOPULATION / 2));
			}
			break;
		case ALL_POPULATION:
			for (int i = 0; i < NPOPULATION; ++i) {
				double parcialFitness = 0, realFitness = 0;
				bool oldVal1 = true;
				int count = 0;

				for (int j = 0; j < NPOPULATION; ++j) {
					if (i == j)
						continue;

					for (int g = 0; g < NGENES; ++g) {
						parcialFitness += evaluateDecision(population[i].getGene(g), population[j].getGene(g));
						parcialFitness += bonus(oldVal1, population[i].getGene(g), count);
					}
					realFitness += (parcialFitness / NGENES);
					parcialFitness = 0;
				}
				population[i].setFitness(realFitness / (NPOPULATION - 1));
			}
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
Rand *Fitness::rand = new Rand();

#endif /* FITNESS_H_ */
