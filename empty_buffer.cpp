#include "empty_buffer.h"

// EmptySymbolBuffer

EmptySymbolBuffer::EmptySymbolBuffer(){
    symbol_counter = 0;
}

EmptySymbolBuffer::EmptySymbolBuffer(const std::string& symbols){
    for(uint i = 0; i < symbols.size(); i++)
        operator<<( (Symbol)symbols[i] );
}

void EmptySymbolBuffer::operator>>(Symbol& symbol){
    symbol_counter--;
}

void EmptySymbolBuffer::operator<<(const Symbol symbol){
    symbol_counter++;
}

bool EmptySymbolBuffer::eof(){
    return !symbol_counter;
}

void EmptySymbolBuffer::reset(){
    symbol_counter = 0;
}

uint EmptySymbolBuffer::size(){
    return symbol_counter * 8U;
}

void EmptySymbolBuffer::print() const{}

//EmptyBitBuffer

EmptyBitBuffer::EmptyBitBuffer(){
    bit_counter = 0;
}

EmptyBitBuffer::EmptyBitBuffer(const std::string& bits){
    bit_counter = 0;

    for(uint i = 0; i < bits.size(); i++)
        if(bits[i] == '0')
            operator<<(0x00);
        else
            operator<<(0x01);
}

void EmptyBitBuffer::operator>>(Bit& bit){
    bit_counter--;
}

void EmptyBitBuffer::operator<<(const Bit bit){
    bit_counter++;
}

void EmptyBitBuffer::writeBlock( uchar byte ){}

void EmptyBitBuffer::writeBlock( uint num ){}

void EmptyBitBuffer::readBlock( uchar& byte ){
    byte = 0x00;
}

void EmptyBitBuffer::readBlock( uint& num ){
    num = 0x00000000;
}

bool EmptyBitBuffer::eof(){
    return !bit_counter;
}

void EmptyBitBuffer::reset(){
    bit_counter = 0;
}

uint EmptyBitBuffer::size(){
    return bit_counter;
}

void EmptyBitBuffer::print() const{}