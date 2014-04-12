/*
 * main.cpp
 *
 *  Created on: Apr 8, 2014
 *      Author: reginaldo
 */
#include <iostream>
#include "Dilemma.h"
using namespace std;
#define EXIT 0;

int main(void){
	Dilemma *d = new Dilemma();
	d->runGA();
	cout << "Finished!" << endl;
	return EXIT;
}


