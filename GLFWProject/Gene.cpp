#include <stdlib.h>

#include "Gene.h"

Gene::Gene() { Gene(rand()); }

Gene::Gene(short data0) : data(data0), activated(true) {
	resetStoredVars();
}

void Gene::mutate() {
	data ^= (1 << (rand() % dataSize));
}

/*
 from type: (0: input or 1: medium) - 1 bit
 from ID: max(input node count, medium node count) = 4
 	= 2, round to 3 bits (% count)
 to type: (0: medium or 1: output) - 1 bit
 to ID: max(medium node count, output node count) = 6 = 3 bits (% count)
 value: 8 bits used; closest 2 power is 16, so 8 bits, making it one short
 */
void Gene::resetStoredVars() {
	fromInput	= data & 0b1'000'0'000'00000000;
	fromID		= data & 0b0'111'0'000'00000000 >> 12;
	toID		= data & 0b0'000'0'111'00000000 >> 8;
	value		= data & 0b0'000'0'000'11111111;
}
