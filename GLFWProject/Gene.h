#include <stdint.h>

class Gene {
public:
	/*
	 * from type (0: input or 1: medium) - 1 bit
	 * from ID - max(input node count, medium node count) = 4
			= 2, round to 3 bits (% count)
	 * to type (0: medium or 1: output) - 1 bit
	 * to ID - max(medium node count, output node count) = 6 = 3 bits (% count)
	 * value - 8 bits used; closest 2 power is 16, so 8 bits, making it one short
	 */

	short data;

	Gene();

	Gene(short data);

	bool fromInputOrMedium() {
		return data & 0b1'000'0'000'00000000;
	}

	uint8_t fromID() {
		return data & 0b0'111'0'000'00000000 >> 15;
	}

	bool toMediumOrOutput() {
		return data & 0b0'000'1'000'00000000;
	}

	uint8_t toID() {
		return data & 0b0'000'0'111'00000000 >> 11;
	}

	int8_t value() {
		return data & 0b0'000'0'000'11111111;
	}

};