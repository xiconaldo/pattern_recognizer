#ifndef PATTERN_RECOGNIZER_H
#define PATTERN_RECOGNIZER_H

#include "definitions.h"
#include "model.h"
#include "memory_buffer.h"
#include "probability.h"
#include "arithmetic_compressor.h"
#include <bitset>
#include <iomanip>
#include <iostream>
#include <cmath>


class PatternRecognizer{
private:
   Model model;

public:
    PatternRecognizer(uchar k = 2, uint tree_mode = 0U);
    ~PatternRecognizer();
    void updatePattern(SymbolBuffer& input);
    void loadFromDisk(std::istream& input);
    void saveToDisk(std::ostream& output);
    uint getScore(SymbolBuffer& input);
    Model& getModel();
};

#endif // PATTERN_RECOGNIZER_H 