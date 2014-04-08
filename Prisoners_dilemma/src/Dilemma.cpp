/*
 * Dilemma.cpp
 *
 *  Created on: Apr 8, 2014
 *      Author: reginaldo
 */

#include "Dilemma.h"
#include "Chromossome.h"
#include "../RNumbers/Rand.h"
#include "Fitness.h"

Dilemma::Dilemma() {
	population = new Chromossome[NPOPULATION];
	rand = new Rand();
	rand->SetSeed();
}

Dilemma::~Dilemma() {
	delete [] population;
	delete rand;
}

void Dilemma::createFirstPopulation(){
	for (int i = 0; i < NPOPULATION; ++i)
		population[i] = Chromossome::createChromossome();
}

void Dilemma::calculateFitness(){
	Fitness::calculateFitness(population);
}

void Dilemma::crossover(){

}

void Dilemma::mutation(){

}

void Dilemma::runGA(){
	this->createFirstPopulation();

	Fitness::setFitnessType(PAIR);

	for (int i = 0; i < NGENERATIONS; ++i) {
		this->calculateFitness();
		this->crossover();
		this->mutation();
	}
}

