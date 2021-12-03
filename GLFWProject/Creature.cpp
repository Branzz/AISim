#include "Creature.h"
#include "Simulation.h"
#include "Gene.h"

Creature::Creature(Simulation* simulation0) {
	Creature(simulation0, new Gene[simulation->geneSize]);
}

Creature::Creature(Simulation* simulation0, Gene* genes0)
	: simulation(simulation0), genes(genes0),
	x(rand() / simulation->getWidth()),
	y(rand() / simulation->getHeight()) { }

void Creature::mutate(unsigned int bitAmount) {
	uint8_t geneSize = simulation->geneSize;
	size_t shortSize = sizeof(short);
	for (int i = 0; i < bitAmount; i++) {
		genes[rand() % geneSize].data ^= (1 << (rand() % shortSize));
	}
	input[inputSize];
	medium[mediumSize];
	output[outputSize];
}

unsigned int Creature::getAge() {
	return (UINT_MAX * simulation->getCurrentTime()) / simulation->getTimeLength();
}

unsigned int Creature::getSouthDist() {
	return (UINT_MAX * y) / simulation->getHeight();
}

unsigned int Creature::getEastDist() {
	return (UINT_MAX * x) / simulation->getWidth();
}

unsigned int Creature::getClock() {
	simulation->getTimeLength() % simulation->getClockCycleLength();
}

void Creature::tickGenes() {
	input[0] = getAge();
	input[1] = getSouthDist();
	input[2] = getEastDist();
	input[3] = getClock();
	for (int i = 0; i < mediumSize; i++) {
		medium[i] = 0;
	}
	for (int i = 0; i < outputSize; i++) {
		output[i] = 0;
	}
	for (int i = 0; i < simulation->geneSize; i++) {
		Gene gene = genes[i];
		float* fromNodes = gene.fromInputOrMedium() ? input : medium;
		const unsigned int fromIndex = gene.fromID() % gene.fromInputOrMedium() ? inputSize : mediumSize;
		float* toNodes = gene.toMediumOrOutput() ? medium : output;
		const unsigned int toIndex = gene.toID() % gene.toMediumOrOutput() ? mediumSize : outputSize;
		fromNodes[fromIndex] += toNodes[toIndex] * gene.value();
	}
}
