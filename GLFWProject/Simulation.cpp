#include "Simulation.h"

Simulation::Simulation(const uint8_t geneSize0,
	const unsigned int creatureAmount0,
	const unsigned int timeLength0,
	const unsigned int width0,
	const unsigned int height0,
	const unsigned int clockCycleLength0,
	const unsigned int generationSize0,
	const unsigned int mutationIntensity0)
	: geneSize(geneSize0),
	creatureAmount(creatureAmount0),
	timeLength(timeLength0),
	currentTime(0),
	width(width0),
	height(height0),
	clockCycleLength(clockCycleLength0),
	generationSize(generationSize0),
	currentGeneration(0),
	generationFrames(generationSize0, 0),
	mutationIntensity(mutationIntensity0) {

	generationCreatures[generationSize];
	geneActivationBuffer[Creature::mediumSize];

	runFirstGen();

}

void Simulation::runFirstGen() {
	generationCreatures[currentGeneration][creatureAmount];
	for (int i = 0; i < creatureAmount; i++)
		generationCreatures[currentGeneration][i] = new Creature(this);
}

void Simulation::createNextGen() {
	currentGeneration++;
	float averageFitness = 0;
	for (int i = 0; i < creatureAmount; i++)
		averageFitness += generationCreatures[currentGeneration - 1][i]->getFitness();
	averageFitness /= creatureAmount;
	generationCreatures[currentGeneration][creatureAmount];
	for (int i = 0, j = 0; j * 2 + 1 < creatureAmount; i = (i + 1) % creatureAmount) {
		Creature creature = *generationCreatures[currentGeneration - 1][i];
		if (creature.getFitness() >= averageFitness) { // ("or equal to" for bool fitness?)
			generationCreatures[currentGeneration][j * 2] = new Creature(this, creature.getGenes());
			generationCreatures[currentGeneration][j * 2]->mutate(mutationIntensity);
			generationCreatures[currentGeneration][j * 2 + 1] = new Creature(this, creature.getGenes());
			generationCreatures[currentGeneration][j * 2 + 1]->mutate(mutationIntensity);
			j++;
		}
		// Prediction: if this is in an infinite loop, the fitness messed up/maxxed out
	}

}

bool trackingGeneration() {
	return true;
}

void Simulation::run() {
	createNextGen();
	// spawn them randomly
	if (trackingGeneration()) {

	}
}

void Simulation::saveFrame() {
	
}

unsigned int getFitness(Creature creature) {
	return 0;
}
