#ifndef TREE_H
#define TREE_H

#include "definitions.h"
#include <unordered_set>
#include <iostream>

class Tree{

public:
	virtual Tree* addPath(const Context& context) = 0;
	virtual Tree* addPath(const Symbol& symbol) = 0;
	virtual Tree* findPath(const Context& context) = 0;
	virtual Tree* findPath(const Symbol& symbol) = 0;
	virtual void eraseEscape() = 0;
	virtual void clear() = 0;

	virtual Symbol getSymbolOnCount(uint count, const SymbolUSet& exc_mec) const = 0;
	virtual uint getOcurrencesFromPreviousSimblings(const Symbol& symbol) const = 0;
	virtual void getChildrenSet(SymbolUSet& exc_set) const = 0;
	virtual uint ocurrences() const = 0;
	virtual uint contexts() const = 0;
	virtual uint child_count() const = 0;

	virtual void saveToDisk(std::ostream& output) = 0;
	virtual void loadFromDisk(std::istream& input) = 0;
	virtual void print() = 0;
};

#endif // TREE_H