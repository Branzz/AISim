#ifndef SIMULATION_H
#define SIMULATION_H
#include "Creature.h"
#include <stdint.h>
#include <vector>

using namespace std;

class Simulation {
public:
	const uint8_t geneSize;
	const unsigned int creatureAmount;
	const unsigned int frameAmount; // simulation duration in milliseconds
	unsigned int currentFrame;
	const unsigned int width; // >= 2*defaultLegLength
	const unsigned int height;
	const unsigned int clockCycleLength;
	const unsigned int generationSize;
	unsigned int currentGeneration;
	vector<unsigned int> generationFrameNumbers;
	// float* in form ((x1,y1),(x2,y2),(x3,y3))
	vector<pair<unsigned int, float**>> generationFrames;
	// [generation][creatures]*
	Creature*** generationCreatures;
	const unsigned int mutationIntensity;
	bool* geneActivationBuffer; // not thread safe
	unsigned int (*fitnessCalculator)(Creature* creature); // uint f(Creature)

	Simulation(const uint8_t geneSize,
		const unsigned int creatureAmount,
		const unsigned int frameAmount,
		const unsigned int width,
		const unsigned int height,
		const unsigned int clockCycleLength,
		const unsigned int generationSize,
		const unsigned int mutationIntensity,
		unsigned int (*fitnessCalculator)(Creature* creature));

	Simulation(Simulation& simulation) :
		geneSize(simulation.geneSize),
		creatureAmount(simulation.creatureAmount),
		frameAmount(simulation.frameAmount),
		currentFrame(simulation.currentFrame),
		width(simulation.width),
		height(simulation.height),
		clockCycleLength(simulation.clockCycleLength),
		generationSize(simulation.generationSize),
		currentGeneration(simulation.currentGeneration),
		generationFrames(simulation.generationSize),
		mutationIntensity(simulation.mutationIntensity),
		fitnessCalculator(simulation.fitnessCalculator),
		generationCreatures(simulation.generationCreatures),
		geneActivationBuffer(simulation.geneActivationBuffer) { }

	~Simulation() {
		for (int i = 0; i < generationFrames.size(); i++) {
			size_t gFSize = sizeof(generationFrames[i]);
			for (int j = 0; j < gFSize; j++)
				delete[] generationFrames[i].second[j];
			delete[] generationFrames[i].second;
		}
		size_t gCSize = sizeof(generationCreatures);
		for (int i = 0; i < gCSize; i++) {
			size_t gCSizeA = sizeof(generationCreatures[i]);
			for (int j = 0; j < gCSizeA; j++) {
				delete[] generationCreatures[i][j];
			}
			delete[] generationCreatures[i];
		}
		delete[] geneActivationBuffer;
		delete &generationFrames;
	}

	void run();

	void saveFrame();

	void calculateFitnesses() {
		for (int i = 0; i < creatureAmount; i++) {
			//creatures[i]->setFitness(getFitness(creatures[i]);
		}
	}

	unsigned int getTimeLength() {
		return frameAmount;
	}

	unsigned int getCurrentTime() {
		return currentFrame;
	}

	unsigned int getWidth() {
		return width;
	}

	unsigned int getHeight() {
		return height;
	}

	unsigned int getClockCycleLength() {
		return clockCycleLength;
	}

private:
	void runFirstGen();
	void createNextGen();
};

#endif
