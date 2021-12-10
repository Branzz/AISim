#include "Simulation.h"

Simulation::Simulation(const uint8_t geneSize0,
	const unsigned int creatureAmount0,
	const unsigned int frameAmount0,
	const unsigned int width0,
	const unsigned int height0,
	const unsigned int clockCycleLength0,
	const unsigned int generationSize0,
	const unsigned int mutationIntensity0,
	unsigned int (*fitnessCalculator0)(Creature* creature))
	: geneSize(geneSize0),
	creatureAmount(creatureAmount0),
	frameAmount(frameAmount0),
	currentFrame(0),
	width(max(2 * Creature::defaultLegLength, width0)),
	height(max(2 * Creature::defaultLegLength, height0)),
	clockCycleLength(clockCycleLength0),
	generationSize(generationSize0),
	currentGeneration(0),
	generationFrames(generationSize0),
	mutationIntensity(mutationIntensity0),
	fitnessCalculator(fitnessCalculator0) {

	generationCreatures[generationSize];
	geneActivationBuffer[Creature::mediumSize];

}

void Simulation::runFirstGen() {
	generationCreatures[currentGeneration /* 0 */][creatureAmount];
	for (int i = 0; i < creatureAmount; i++)
		generationCreatures[currentGeneration][i] = new Creature(this);
//	currentFrames[frameAmount];
}

void Simulation::createNextGen() {
	float averageFitness = 0;
	for (int i = 0; i < creatureAmount; i++)
		averageFitness += (*fitnessCalculator)(generationCreatures[currentGeneration - 1][i]);
	averageFitness /= creatureAmount;
	generationCreatures[currentGeneration][creatureAmount];
	for (int i = 0, j = 0; j * 2 + 1 < creatureAmount; i = (i + 1) % creatureAmount) {
		Creature creature = *generationCreatures[currentGeneration - 1][i];
		if (creature.getFitness() >= averageFitness) { // ("or equal to" for bool fitness?/all equal)
			generationCreatures[currentGeneration][j * 2    ] = new Creature(this, creature.getGenes());
			generationCreatures[currentGeneration][j * 2 + 1] = new Creature(this, creature.getGenes());
			j++;
		}
		// Prediction: if this is in an infinite loop, the fitness messed up/maxxed out
	}
}

bool trackingGeneration() {
	return true;
}

void Simulation::run() {
	runFirstGen();
	while (currentGeneration < frameAmount) {
		// spawn them randomly
		if (trackingGeneration()) {
			saveFrame();
		}
		createNextGen();
		currentGeneration++;
	}
}

void Simulation::saveFrame() {
	float** currentFrames; // mild memory leak (RAM overflow?)
	for (int i = 0; i < creatureAmount; i++) {
		currentFrames[i][6];
		for (int j = 0; j < 6; j++)
			currentFrames[i][j] = generationCreatures[currentGeneration][i]->corners[j];
	}
	generationFrames.push_back(pair<unsigned int, float**>(currentFrame, currentFrames));
}
