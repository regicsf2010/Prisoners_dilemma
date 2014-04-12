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
#include <math.h>
#include <fstream>
using namespace std;

Dilemma::Dilemma() {
	population = new Chromossome[NPOPULATION];
	stats = new Stats[NGENERATIONS];
	rand = new Rand();
	rand->SetSeed();
}

Dilemma::~Dilemma() {
	delete[] population;
	delete[] stats;
	delete rand;
}

void Dilemma::createFirstPopulation() {
	for (int i = 0; i < NPOPULATION; ++i)
		population[i] = Chromossome::createChromossome();
}

void Dilemma::calculateFitness() {
	Fitness::calculateFitness(population);
}

void Dilemma::crossover() {
	Chromossome *parents = new Chromossome[NPOPULATION];
	int selected = -1, sorted = -1;
	// TOURNAMENT
	for (int i = 0; i < NPOPULATION; ++i) {
		selected = rand->RandInt(NPOPULATION);
		for (int j = 1; j < NRING; ++j) {
			sorted = rand->RandInt(NPOPULATION);
			if (population[selected].getFitness()
					< population[sorted].getFitness()) {
				selected = sorted;
			}
		}
		parents[i] = population[selected];
	}

	// CROSSOVER
	int cutPosition = -1;
	bool aux = false;
	for (int i = 0; i < NPOPULATION; i += 2) {
		if (rand->Uniform() < CROSSOVER_PROB) {
			cutPosition = rand->RandInt(NGENES - 1) + 1;
			for (int j = cutPosition; j < NGENES; ++j) {
				aux = parents[i].getGene(j);
				parents[i].setGene(j, parents[i + 1].getGene(j));
				parents[i + 1].setGene(j, aux);
			}
		}
	}

	// GERACIONAL
	for (int i = 0; i < NPOPULATION; ++i)
		population[i] = parents[i];

	delete[] parents;
}

void Dilemma::mutation() {
	for (int i = 0; i < NPOPULATION; ++i)
		for (int j = 0; j < NGENES; ++j)
			if (rand->Uniform() <= MUTATION_PROB)
				population[i].flipGene(j);
}

double Dilemma::calculateFitnessPopulationMean() {
	double fitnessPopulationMean = 0;
	for (int i = 0; i < NPOPULATION; ++i)
		fitnessPopulationMean += population[i].getFitness();
	fitnessPopulationMean /= NPOPULATION;
	return fitnessPopulationMean;
}

double Dilemma::calculateFitnessPopulationSD(double fitnessMean) {
	double fitnessPopulationSD = 0;
	for (int i = 0; i < NPOPULATION; ++i) {
		fitnessPopulationSD += pow(population[i].getFitness() - fitnessMean, 2);
	}
	fitnessPopulationSD /= (NPOPULATION - 1);
	return sqrt(fitnessPopulationSD);
}

void Dilemma::runGA() {
	this->createFirstPopulation();

	Fitness::setFitnessConfiguration(ALL_POPULATION, GROUP);

	for (int i = 0; i < NGENERATIONS; ++i) {
		this->calculateFitness();
		double mean = calculateFitnessPopulationMean();
		stats[i].fitnessPopMean = mean;
		stats[i].fitnessPopSD = calculateFitnessPopulationSD(mean);
		this->crossover();
		this->mutation();
	}

	writeMatLabScript();

}

void Dilemma::writeMatLabScript() {
	ofstream pen;
	pen.open("script.m");
	pen << "x=1:1:" << NGENERATIONS << ";\n";

	pen << "y=[";
	for (int i = 0; i < NGENERATIONS; ++i)
		pen << stats[i].fitnessPopMean << " ";
	pen << "];\n";

	pen << "wup=[";
	for (int i = 0; i < NGENERATIONS; ++i)
		pen << stats[i].fitnessPopMean + stats[i].fitnessPopSD << " ";
	pen << "];\n";

	pen << "wdown=[";
	for (int i = 0; i < NGENERATIONS; ++i)
		pen << stats[i].fitnessPopMean - stats[i].fitnessPopSD << " ";
	pen << "];\n";

	pen << "plot(x,y,'-gs',x,wup,x,wdown);\n";
	pen << "title('Prisoners Dilemma');\n";
	pen << "xlabel('GENERATION');\n";
	pen << "ylabel('FITNESS MEAN PER GENERATION');\n";
	pen.close();
}

