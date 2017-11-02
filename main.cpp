#include "tree.h"
#include "model.h"
#include "memory_buffer.h"
#include "file_buffer.h"
#include "arithmetic_compressor.h"
#include "pattern_recognizer.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <string>

int main(int argc, char* argv[]){

	PatternRecognizer p{5};
	FileSymbolBuffer file{"../files/aaa.txt"};
	std::ofstream output{"../files/teste.txt", std::ofstream::binary};

	p.updatePattern(file);
	p.saveToDisk(output);

	output.close();
	

	std::ifstream input{"../files/teste.txt", std::ofstream::binary};
	PatternRecognizer p2{0};
	p2.loadFromDisk(input);

	input.close();

	return 0;
}