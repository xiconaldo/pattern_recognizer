#include "pattern_recognizer.h"

PatternRecognizer::PatternRecognizer(uchar k, uint tree_mode) :
    model(k, tree_mode)
{}

PatternRecognizer::~PatternRecognizer(){}

void PatternRecognizer::updatePattern(SymbolBuffer& input){

    Symbol symbol;
	Context context;

    while( !input.eof() ){
        input >> symbol;
        model.updateModel(context, symbol);
        context.push_back(symbol);
        if(context.size() > model.getK()) context.pop_front();
    }
}

void PatternRecognizer::loadFromDisk(std::istream& input){
    model.clearModel();
    model.loadFromDisk(input);
}

void PatternRecognizer::saveToDisk(std::ostream& output){
    model.saveToDisk(output);
}

uint PatternRecognizer::getScore(SymbolBuffer& input){

    double entropy;
    EmptyBitBuffer output{};
    ArithmeticCompressor::encode(model, input, output, entropy, false);

    return output.size();

}

Model& PatternRecognizer::getModel(){
    return model;
}