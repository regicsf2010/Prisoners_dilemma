/*
 * Chromossome.h
 *
 *  Created on: Apr 8, 2014
 *      Author: reginaldo
 */

#ifndef CHROMOSOME_H_
#define CHROMOSOME_H_

#include "../MasterChromo/MasterChromo.h"
#include "CONSTANTS.h"
#include <bitset>
#include "../RNumbers/Rand.h"
#include <iostream>
using namespace std;

class Chromosome : public MasterChromo<double> {
private:
	bitset<NGENES> genes;

public:
	Chromosome(){};
	virtual ~Chromosome(){};

	inline bool getGene(const int &pos) const{
		return genes[pos];
	}

	inline void setGene(const int &pos, const bool &value) {
		genes.set(pos, value);
	}

	inline void flipGene(const int &pos) {
		genes.flip(pos);
	}

	inline static Chromosome createChromosome(){
		Chromosome c;
		Rand *r = new Rand();
		r->SetSeed();
		for (int i = 0; i < NGENES; ++i)
			if(r->Uniform() > 0.5)
				c.flipGene(i);
		delete r;
		return c;
	}

	inline void print() const {
		cout << genes << endl;
	}
};

#endif /* CHROMOSOME_H_ */
