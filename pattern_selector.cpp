#include "pattern_selector.h"

PatternSelector::PatternSelector(const std::string& test_file_name,
                                 const std::vector<std::string>& input_file_names) {
        
    this->test_file_name = test_file_name;
    this->input_file_names = input_file_names;
    num_blocks = input_file_names.size();
    num_threads = 4;
    
    for(uint i = 0; i < num_blocks; i++)
        score.push_back(0U);
}

void PatternSelector::selectMulti(){
    std::vector<std::thread*> threads(num_threads);
    
    for(int i = 0; i < num_threads; i++){
        threads[i] = new std::thread(&PatternSelector::select, this);
    }

    printProgress();

    for(int i = 0; i < num_threads; i++){
        threads[i]->join();
        delete threads[i];
    }
}

void PatternSelector::select(){

    uint work_block;

    while(true){
        work_block = block++;
        if(work_block >= num_blocks) break;
        
        PatternRecognizer p;
        FileSymbolBuffer test_file{test_file_name};
        std::ifstream input{input_file_names[work_block], std::ofstream::binary};

        p.loadFromDisk(input);
        input.close();
        score[work_block] = p.getScore(test_file);
    }
}

std::vector<uint> PatternSelector::getScores(){
    return score;
}

void PatternSelector::printProgress(){

    uint work_block;
    std::cerr << "Comparing Patterns...\n";

    while(true){

        work_block = block;

        std::cerr << "\rCompleted: " << (work_block >= num_threads ? work_block-num_threads : 0) << "/" << num_blocks;

        if(work_block == num_blocks+num_threads) break;
    
        std::this_thread::sleep_for (std::chrono::seconds(2));
    }

}