#ifndef ARITHMETIC_COMPRESSOR_H
#define ARITHMETIC_COMPRESSOR_H

#include "definitions.h"
#include "model.h"
#include "memory_buffer.h"
#include "empty_buffer.h"
#include "probability.h"
#include <bitset>
#include <iomanip>
#include <cmath>


class ArithmeticCompressor{
private:
    static const uint ONE_QUARTER       = 0x20000000U;
    static const uint THREE_QUARTERS    = 0x60000000U;
    static const uint ONE_HALF          = 0x40000000U;

public:
    static void encode(Model& model, SymbolBuffer& input, BitBuffer& output, double& entropy, bool update = true);
    static void decode(Model& model, BitBuffer& input, SymbolBuffer& output, uint size, bool update = true);
};

#endif // ARITHMETIC_COMPRESSOR_H 