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
	const unsigned int timeLength; // simulation duration in milliseconds
	unsigned int currentTime;
	const unsigned int width;
	const unsigned int height;
	const unsigned int clockCycleLength;
	const unsigned int generationSize;
	unsigned int currentGeneration;
	// float* in form ((x1,y1),(x2,y2),(x3,y3))
	vector<float**> generationFrames;
	// [generation][creatures]*
	Creature*** generationCreatures;
	const unsigned int mutationIntensity;

	Simulation(const uint8_t geneSize,
		const unsigned int creatureAmount,
		const unsigned int timeLength,
		const unsigned int width,
		const unsigned int height,
		const unsigned int clockCycleLength,
		const unsigned int generationSize,
		const unsigned int mutationIntensity);

	~Simulation() {
		for (int i = 0; i < generationFrames.size(); i++) {
			size_t gFSize = sizeof(generationFrames[i]);
			for (int j = 0; j < gFSize; j++)
				delete[] generationFrames[i][j];
			delete[] generationFrames[i];
		}
		size_t gCSize = sizeof(generationCreatures);
		for (int i = 0; i < gCSize; i++) {
			size_t gCSizeA = sizeof(generationCreatures[i]);
			for (int j = 0; j < gCSizeA; j++) {
				delete[] generationCreatures[i][j];
			}
			delete[] generationCreatures[i];
		}
		delete& generationFrames;
	}

	void run();

	void saveFrame();

	void calculateFitnesses() {
		for (int i = 0; i < creatureAmount; i++) {
			//creatures[i]->setFitness(getFitness(creatures[i]);
		}
	}

	unsigned int getTimeLength() {
		return timeLength;
	}

	unsigned int getCurrentTime() {
		return currentTime;
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
