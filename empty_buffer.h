#ifndef EMPTY_BUFFER_H
#define EMPTY_BUFFER_H

#include "buffer.h"
#include <iostream>

class EmptySymbolBuffer : public SymbolBuffer{
    
private:
    uint symbol_counter;

public:
    EmptySymbolBuffer();
    EmptySymbolBuffer(const std::string& symbols);
    void operator>>(Symbol& symbol);
    void operator<<(const Symbol symbol);
    bool eof();
    void reset();
    uint size();
    void print() const;
};

class EmptyBitBuffer : public BitBuffer{
    
private:
    uint bit_counter;

public:
    EmptyBitBuffer();
    EmptyBitBuffer(const std::string& bits);
    void operator>>(Bit& bit);
    void operator<<(const Bit bit);
    void writeBlock( uchar byte );
    void writeBlock( uint num );
    void readBlock( uchar& byte );
    void readBlock( uint& num );
    bool eof();
    void reset();
    uint size();
    void print() const;
};

#endif // EMPTY_BUFFER_H