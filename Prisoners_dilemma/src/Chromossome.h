/*
 * Chromossome.h
 *
 *  Created on: Apr 8, 2014
 *      Author: reginaldo
 */

#ifndef CHROMOSSOME_H_
#define CHROMOSSOME_H_

#include "../MasterChromo/MasterChromo.h"
#include "CONSTANTS.h"
#include <bitset>
#include "../RNumbers/Rand.h"
#include <iostream>
using namespace std;

class Chromossome : public MasterChromo<double> {
private:
	bitset<NGENES> genes;

public:
	Chromossome(){};
	virtual ~Chromossome(){};

	inline bool getGene(const int &pos) const{
		return genes[pos];
	}

	inline void setGene(const int &pos, const bool &value) {
		genes.set(pos, value);
	}

	inline void flipGene(const int &pos) {
		genes.flip(pos);
	}

	inline static Chromossome createChromossome(){
		Chromossome c;
		Rand *r = new Rand();
		r->SetSeed();
		for (int i = 0; i < NGENES; ++i) {
			if(r->Uniform() > 0.5)
				c.flipGene(i);
		}
		delete r;
		return c;
	}

	inline void print() const {
		cout << genes << endl;
	}

};

#endif /* CHROMOSSOME_H_ */
