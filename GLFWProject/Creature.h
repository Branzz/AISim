#include <stdlib.h>
#include <stdint.h>

#ifndef CREATURE_H
#define CREATURE_H
#include "Simulation.h"
#include "Gene.h"

class Creature {
public:

	Simulation* simulation;
	Gene* genes;
	unsigned int x;
	unsigned int y;
	unsigned int fitness;

	// Nodes
	float* input;
	float* medium;
	float* output;

	const unsigned int inputSize = 4;
	const unsigned int mediumSize = 3;
	const unsigned int outputSize = 6; // 3 legs; 2 directions

	Creature(Simulation* simulation);

	Creature(Simulation* simulation, Gene* genes);

	~Creature() {
		delete[] genes;
		delete[] input;
		delete[] medium;
		delete[] output;
	}

	void mutate(unsigned int bitAmount);

	unsigned int getFitness() {
		return fitness;
	}

	Gene* getGenes() {
		return genes;
	}

	// input "senses" - positive value
	unsigned int getAge();
	unsigned int getSouthDist();
	unsigned int getEastDist();
	unsigned int getClock();

	// output "motions"
	
	void flexLeg(int leg, bool direction) {

	}

	// go through each gene and make a movement
	void tickGenes();

};

#endif
