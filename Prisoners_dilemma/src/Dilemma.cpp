/*
 * Dilemma.cpp
 *
 *  Created on: Apr 8, 2014
 *      Author: reginaldo
 */

#include "Dilemma.h"
#include "Chromosome.h"
#include "../RNumbers/Rand.h"
#include "Fitness.h"
#include <math.h>
#include <fstream>
using namespace std;

Dilemma::Dilemma() {
	population = new Chromosome[NPOPULATION];
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
		population[i] = Chromosome::createChromosome();
}

void Dilemma::calculateFitness() {
	Fitness::calculateFitness(population);
}

void Dilemma::crossover() {
	Chromosome *parents = new Chromosome[NPOPULATION];
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

double Dilemma::calculateBestFitnessPopulation(){
	qsort(population, NPOPULATION, sizeof(population[0]), compare);
	return population[0].getFitness();
}

int Dilemma::compare(const void *x, const void *y){
	const Chromosome xx = *(Chromosome*)x;
	const Chromosome yy = *(Chromosome*)y;
	if(xx.getFitness() < yy.getFitness()) return 1;
	if(xx.getFitness() > yy.getFitness()) return -1;
	return 0;
}

void Dilemma::runGA() {
	this->createFirstPopulation();

	Fitness::setFitnessConfiguration(PAIR, GROUP);

	for (int i = 0; i < NGENERATIONS; ++i) {
		this->calculateFitness();
		stats[i].popFitnessMean = calculateFitnessPopulationMean();
		stats[i].popFitnessSD = calculateFitnessPopulationSD(stats[i].popFitnessMean);
		stats[i].popBestFitness = calculateBestFitnessPopulation();
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
		pen << stats[i].popFitnessMean << " ";
	pen << "];\n";

	pen << "wup=[";
	for (int i = 0; i < NGENERATIONS; ++i)
		pen << stats[i].popFitnessMean + stats[i].popFitnessSD << " ";
	pen << "];\n";

	pen << "wdown=[";
	for (int i = 0; i < NGENERATIONS; ++i)
		pen << stats[i].popFitnessMean - stats[i].popFitnessSD << " ";
	pen << "];\n";

	pen << "best=[";
	for (int i = 0; i < NGENERATIONS; ++i)
		pen << stats[i].popBestFitness << " ";
	pen << "];\n";

	pen << "plot(x,y,'-gs',x,wup,'-b',x,wdown,'-b',x,best,'-rs');\n";
	pen << "title('Prisoners Dilemma');\n";
	pen << "xlabel('GENERATION');\n";
	pen << "ylabel('FITNESS MEAN PER GENERATION');\n";
	pen.close();
}

