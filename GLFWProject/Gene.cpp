#include <stdlib.h>

#include "Gene.h"

Gene::Gene() { data = rand(); }

Gene::Gene(short data0) : data(data0) {}
