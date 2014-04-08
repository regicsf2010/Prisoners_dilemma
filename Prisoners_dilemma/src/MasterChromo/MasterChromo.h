/*
 * MasterChomo.h
 *
 *  Created on: Mar 27, 2014
 *      Author: reginaldo
 */

#ifndef MASTERCHROMO_H_
#define MASTERCHROMO_H_

template <class T>

class MasterChromo {
private:
	T fitness;

public:
	MasterChromo(){}
	virtual ~MasterChromo(){}

	inline T getFitness() const {
		return this->fitness;
	}

	inline virtual void setFitness(const T &fitness) {
		this->fitness = fitness;
	}
};

#endif /* MASTERCHROMO_H_ */
