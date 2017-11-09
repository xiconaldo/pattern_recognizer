#ifndef PATTERN_SELECTOR_H
#define PATTERN_SELECTOR_H

#include <atomic>
#include <thread>
#include <fstream>
#include <vector>
#include "pattern_recognizer.h"
#include "file_buffer.h"

class PatternSelector{
    
private:
    std::string test_file_name;
    std::vector<std::string> input_file_names;
    std::vector<uint> score;

    uint num_threads;
    uint num_blocks;
    std::atomic<uint> block{0U};

public:
    PatternSelector(const std::string& test_file_name,
                    const std::vector<std::string>& input_file_names);

    void selectMulti();
    void select();
    std::vector<uint> getScores();
    void printProgress();
};

#endif // PATTERN_SELECTOR_H