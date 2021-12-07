#include "Creature.h"
#include "Simulation.h"
#include "Gene.h"

Creature::Creature(Simulation* simulation0) {
	Creature(simulation0, new Gene[simulation->geneSize]);
}

Creature::Creature(Simulation* simulation0, Gene* genes0)
	: simulation(simulation0), genes(genes0) {

	corners[6];
	input[inputSize];
	medium[mediumSize];
	output[outputSize];
}

void Creature::mutate(unsigned int bitAmount) {
	for (int i = 0; i < bitAmount; i++) {
		genes[rand() % simulation->geneSize].mutate();
	}
	for (int i = 0; i < simulation->geneSize; i++) {
		genes[i].resetStoredVars();
	}
	reactivateGenes();
}

void Creature::reactivateGenes() {
	memset(simulation->geneActivationBuffer, 0, mediumSize);
	for (int i = 0; i < simulation->geneSize; i++) {
		Gene gene = genes[i];
		if (gene.fromInput) {
			simulation->geneActivationBuffer[gene.toID % mediumSize] |= 0b01;
		} else { // from medium
			simulation->geneActivationBuffer[gene.fromID % mediumSize] |= 0b10;
		}
	}
	for (int i = 0; i < simulation->geneSize; i++) {
		Gene gene = genes[i];
		gene.activated = simulation->geneActivationBuffer[gene.toID % mediumSize] == 0b11;
	}

	for (int i = 0; i < simulation->geneSize; i++) {
		Gene gene = genes[i];
		if (gene.activated) {
			if (gene.fromInput) {
				inputActivation |= 1 << gene.fromID % inputSize;
				mediumActivation |= 1 << gene.toID % mediumSize;
			}
			else { // from medium
				mediumActivation |= 1 << gene.fromID % mediumSize;
				outputActivation |= 1 << gene.toID % outputSize;
			}
		}
	}

}

unsigned int Creature::getAge() {
	return (UINT_MAX * simulation->getCurrentTime()) / simulation->getTimeLength();
}

unsigned int Creature::getSouthDist() {
	return (UINT_MAX * max(corners[1], max(corners[3], corners[5]))) / simulation->getHeight();
}

unsigned int Creature::getEastDist() {
	return (UINT_MAX * max(corners[0], max(corners[2], corners[4]))) / simulation->getWidth();
}

unsigned int Creature::getClock() {
	simulation->getTimeLength() % simulation->getClockCycleLength();
}

void Creature::tickGenes() {
	if (inputActivation && 0b0001)
		input[0] = getAge();
	if (inputActivation && 0b0010)
		input[1] = getSouthDist();
	if (inputActivation && 0b0100)
		input[2] = getEastDist();
	if (inputActivation && 0b1000)
		input[3] = getClock();
	memset(medium, 0, mediumSize);
	memset(output, 0, outputSize);
	for (int i = 0; i < simulation->geneSize; i++) {
		Gene gene = genes[i];
		if (gene.activated && gene.fromInput) {
			medium[gene.toID % mediumSize]
				+= input[gene.fromID % inputSize] * gene.value;
		}
	}
	for (int i = 0; i < mediumSize; i++) {
		if (mediumActivation & (1 << i))
			medium[i] = tanh(medium[i] / TRUNCATION_FACTOR);
	}
	for (int i = 0; i < simulation->geneSize; i++) {
		Gene gene = genes[i];
		if (gene.activated && !gene.fromInput) { // from medium
			output[gene.toID % outputSize]
				+= medium[gene.fromID % mediumSize] * gene.value;
		}
	}
	for (int i = 0; i < mediumSize; i++) {
		if (mediumActivation & (1 << i))
			output[i] = tanh(output[i] / TRUNCATION_FACTOR);
	}
}

void Creature::updateCorners() {
	/*
	(x1, y1)-12-(x2, y2)
		 31\	/23
		  (x3, y3)
	*/
	// vector translation (a point moves along its slopes with the 2 other points)
	int x12 = corners[2] - corners[0];
	int x23 = corners[4] - corners[2];
	int x31 = corners[0] - corners[4];
	int y12 = corners[3] - corners[1];
	int y23 = corners[5] - corners[3];
	int y31 = corners[1] - corners[5];
	float dist12 = lengthNormalizer(sqrt(x12 * x12 + y12 * y12));
	float dist12scale1 = output[0] * dist12;
	float dist12scale2 = output[1] * dist12;
	float dist23 = lengthNormalizer(sqrt(x23 * x23 + y23 * y23));
	float dist23scale1 = output[2] * dist23;
	float dist23scale2 = output[3] * dist23;
	float dist31 = lengthNormalizer(sqrt(x31 * x31 + y31 * y31));
	float dist31scale1 = output[4] * dist31;
	float dist31scale2 = output[5] * dist31;
	corners[0] += x12 * dist12scale1 - x31 * dist31scale2;
	corners[1] += y12 * dist12scale1 - y31 * dist31scale2;
	corners[2] += x23 * dist23scale1 - x12 * dist12scale2;
	corners[3] += y23 * dist23scale1 - y12 * dist12scale2;
	corners[4] += x31 * dist31scale1 - x23 * dist23scale2;
	corners[5] += y31 * dist31scale1 - y23 * dist23scale2;
}

static const float epsilon = 0.01F;
static const float lnEpsilon = log(epsilon);
static const float maxMovement = 1;
/*
Normal curve with tails at 0 and asymptotic min at epsilon
*/
float Creature::lengthNormalizer(float legLength) {
	return (maxMovement + epsilon) * (exp(pow((legLength), 2) * lnEpsilon) / defaultLegLengthSqrd) - epsilon;
}