#ifndef CREATURE_H
#define CREATURE_H
#include <stdlib.h>
#include <stdint.h>
#include "Simulation.h"
#include "Gene.h"

class Creature {
public:

	Simulation* simulation;
	Gene* genes;
	static const unsigned int defaultLegLength = 20;
	static const unsigned int defaultLegLengthSqrd = defaultLegLength * defaultLegLength;
	unsigned int* corners; // 3 points
	unsigned int fitness;

	// Nodes
	float* input;
	float* medium;
	float* output;

	static const unsigned int inputSize = 4;
	static const unsigned int mediumSize = 3;
	static const unsigned int outputSize = 6; // 3 legs; 2 directions

	static const int TRUNCATION_FACTOR = 256;

	Creature(Simulation* simulation);

	Creature(Simulation* simulation, Gene* genes);

	Creature(Creature& creature) :
		simulation(creature.simulation),
		genes(creature.genes),
		input(creature.input),
		medium(creature.medium),
		output(creature.output),
		corners(creature.corners),
		fitness(creature.fitness) { }

	~Creature() {
		delete[] genes;
		delete[] input;
		delete[] medium;
		delete[] output;
	}

	void spawn();

	void mutate(unsigned int bitAmount);
	void reactivateGenes();

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

	void tickGenes();

	// output "motions"
	void updateCorners();

protected:
	float distanceFromDefaultLegLength(double dist);
	float lengthNormalizer(float legLength);

private:
	int8_t inputActivation;
	int8_t mediumActivation;
	int8_t outputActivation;

};

#endif
