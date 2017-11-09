#include "tree.h"
#include "model.h"
#include "memory_buffer.h"
#include "file_buffer.h"
#include "arithmetic_compressor.h"
#include "pattern_recognizer.h"
#include "pattern_selector.h"
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
		std::vector<std::string> input_file_names;
		std::vector<uint> scores;

		for(int i = 2; i < argc-1; i++)
			input_file_names.push_back(std::string{argv[i]});	

		PatternSelector selector{test_file_name, input_file_names};
		selector.selectMulti();
		scores = selector.getScores();

		uint best_choice = 0;
		uint best_score = -1;
		uint i = 0;

		for(auto score : scores){
			best_score = score < best_score ? score : best_score;
			best_choice = score == best_score ? i : best_choice;
			i++;
		}		

		uint alig1 = 30;
		uint alig2 = 17;

		std::cout << "\n\nComparation Finished!\nResults:\n\n";

		std::cout << std::setw(alig1) << std::left << std::setfill('-') << "+"
				  << std::setw(alig2) << std::left << std::setfill('-') << "+"
				  << "+" << std::endl << std::setfill(' ');

		std::cout << std::setw(alig1) << std::left << "| Pattern File" 
				  << std::setw(alig2) << std::left << "| Compress Size" << "|" << std::endl;

		std::cout << std::setw(alig1) << std::setfill('-') << "+"
				  << std::setw(alig2) << std::setfill('-') << "+"
				  << "+" << std::endl << std::setfill(' ');

		for(int i = 0; i < scores.size(); i++){
			std::cout << "| " << std::setw(alig1-2) << std::left << std::string{argv[i+2]} 
					  << "| " << std::setw(alig2-2)  << std::left << scores[i] << "|" << std::endl;
			
			std::cout << std::setw(alig1) << std::setfill('-') << "+"
			<< std::setw(alig2) << std::setfill('-') << "+"
			<< "+" << std::endl << std::setfill(' ');
		}

		std::cout << "\nBest Match: " << std::string{argv[best_choice+2]}  << std::endl << std::endl;
	}

	return 0;
}