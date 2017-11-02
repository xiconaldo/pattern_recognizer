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

	std::cerr << "\n";
	if( argc < 5 ){
		std::cerr << "Too few arguments...\n\n";
		return 0;
	}

	std::string gen_get = std::string{argv[1]};
	std::string input_file_name;
	std::string output_file_name;
	uchar k;

	if(gen_get == "-gen"){

		k = std::stoi(std::string{argv[argc-2]});
		output_file_name = std::string{argv[argc-1]};
		PatternRecognizer p{k};

		std::string input_file_name;
		for(int i = 2; i < argc-2; i++){
			input_file_name = std::string{argv[i]};
			FileSymbolBuffer file{input_file_name};
			p.updatePattern(file);
		}

		std::ofstream output{output_file_name, std::ofstream::binary};
		p.saveToDisk(output);
		output.close();
	}
	else if(gen_get == "-get"){

		std::string test_file_name = std::string{argv[argc-1]};
		std::string input_file_name;
		PatternRecognizer p;
		FileSymbolBuffer test_file{test_file_name};
		
		uint best_choice = 0;
		uint best_score = -1;
		uint score;

		for(int i = 2; i < argc-1; i++){

			input_file_name = std::string{argv[i]};
			std::ifstream input{input_file_name, std::ofstream::binary};

			p.loadFromDisk(input);
			input.close();

			score = p.getScore(test_file);
			test_file.reset();

			std::cout << "Current: " << input_file_name << " - " <<  score << std::endl;
			best_score = score < best_score ? score : best_score;
			best_choice = score == best_score ? i : best_choice;
		}

		std::cout << "Best: " << std::string{argv[best_choice]} << std::endl;

	}

	return 0;
}