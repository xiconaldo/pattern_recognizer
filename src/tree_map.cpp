#include "tree_map.h"

bool CompareSymbol::operator()(const Symbol& s1, const Symbol& s2) const{
	return s1 < s2;
}

TreeMap* TreeMap::addPath(const Context& context){
	
	TreeMap* child_node = this;
	TreeMap* parent_node;

	for(Symbol s : context){
        parent_node = child_node;
		child_node = parent_node->findChild(s);
		if(!child_node) child_node = parent_node->addChild(s);
	}

	return child_node;
}

TreeMap* TreeMap::addPath(const Symbol& symbol){
    
    contexts_count_++;

	TreeMap* node = this->findChild(symbol);
	if(!node) node = this->addChild(symbol);
    node->num_ocurrences_++;
    
	return node;
}

TreeMap* TreeMap::findPath(const Context& context){

	TreeMap* node = this;

	for(Symbol s : context){
		node = node->findChild(s);
		if(!node) return nullptr;
	}

	return node;
}

TreeMap* TreeMap::findPath(const Symbol& symbol){
	return this->findChild(symbol);
}

void TreeMap::eraseEscape(){
	
	contexts_count_ -= children[ESC]->num_ocurrences_;
	delete children[ESC];
	children.erase(ESC);
		
}

void TreeMap::clear(){
	num_ocurrences_ = 0;
	contexts_count_ = 0;

	for( auto element : children ){
		element.second->clear();
		delete element.second;
	}
	children.clear();
}

/////////

Symbol TreeMap::getSymbolOnCount(uint count, const SymbolUSet& exc_mec) const{
	
	uint aux = 0;

	for( auto k = children.begin(); k != children.end(); k++){
		if( !exc_mec.count(k->first) ) aux += k->second->ocurrences();
		if( aux > count) return k->first;
	}

	if( !children.empty() ) return children.rbegin()->first;
	return ESC;
}

uint TreeMap::getOcurrencesFromPreviousSimblings(const Symbol& symbol) const{
	
	uint count = 0;
	auto k = children.begin();
	auto limit = children.lower_bound(symbol);

	for( ; k != limit; k++)
	  	count += k->second->num_ocurrences_;

	return count;
}

void TreeMap::getChildrenSet(SymbolUSet& exc_set) const{
	for(auto it = children.begin(); it != children.end(); it++)
		if(it->first != ESC) exc_set.insert(it->first);
}

/////////////////

uint TreeMap::ocurrences() const{
	return num_ocurrences_;
}

uint TreeMap::contexts() const{
	return contexts_count_;
}

uint TreeMap::child_count() const{
	return children.size();
}


///////////////////////


TreeMap* TreeMap::addChild(const Symbol& symbol){
	return (children[symbol] = new TreeMap);
}

TreeMap* TreeMap::findChild(const Symbol& symbol){
	return children.count(symbol) ? children[symbol] : nullptr;
}


void TreeMap::saveToDisk(std::ostream& output){

	output.write( (char*)&num_ocurrences_, sizeof(num_ocurrences_) );
	output.write( (char*)&contexts_count_, sizeof(contexts_count_) );

	for( auto element : children){
		output.write( (char*)&element.first, sizeof(element.first) );
		element.second->saveToDisk(output);
	}

}

void TreeMap::loadFromDisk(std::istream& input){
	
	Symbol next;

	input.read( (char*)&num_ocurrences_, sizeof(num_ocurrences_) );
	input.read( (char*)&contexts_count_, sizeof(contexts_count_) );
	uint num_contexts = contexts_count_;

	while(num_contexts > 0){
		input.read( (char*)&next, sizeof(next) );
		this->addChild(next);
		children[next]->loadFromDisk(input);
		num_contexts -= children[next]->num_ocurrences_;
	}

}

void TreeMap::print(){

	static int depth = -1;
	static std::vector<int> path;
	static Symbol symbol_ = 0;

	depth++;

	for(int i = 0; i < depth; i++){
		if(i == depth-1)
			std::cout << "+--";
		else if( path[i] == 0)
			std::cout << "|  ";
		else
			std::cout << "   ";
	}

	std::cout << "{" << symbol_ << ", " << num_ocurrences_ << ", " << contexts_count_ << "}\n";

	for(int i = 0; i < depth; i++){
		if( path[i] == 0)
			std::cout << "|  ";
		else
			std::cout << "   ";
	}

	if(!this->children.empty())
		std::cout << "|  ";

	std::cout << std::endl;


	int i = 0;
	Symbol aux;

	for( auto ch : children){

		if(i++ == children.size()-1)
			path.push_back(1);
		else
			path.push_back(0);

		aux = symbol_;
		symbol_ = ch.first;
		ch.second->print();
		symbol_ = aux;
		path.pop_back();

	}

	depth--;
}