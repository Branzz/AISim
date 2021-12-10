#ifndef GENE_H
#define GENE_H

#include <stdint.h>

class Gene {
public:

	short data;
	const size_t dataSize = sizeof(data); // should be less than rand max

	bool fromInput; // implies toMedium; false: mediumToOutput
	uint8_t fromID;
	uint8_t toID;
	int8_t value;

	bool activated;

	Gene();

	Gene(short data0);

	void mutate(); // only modifies data
	void resetStoredVars(); // must be called after mutates

};

#endif