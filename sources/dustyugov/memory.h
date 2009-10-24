/**
 * memory.h - Specification of memory model
 * Define classes and methods to operate with memory of simulated architecture
 * Copyright 2009 MDSP team
 */
#ifndef MEMORY_H
#define MEMORY_H 

#include <iostream>
#include <vector>
#include "types.h"
#include <cassert>

#define DEFAULT_OUT HEX

using namespace std;

/* Enumeration for Byte & Byteline classes' output*/
enum output_type { BIN, DEC, HEX};

/**
 * class Byte implements 
 */

class Byte
{
    hostUInt8 byte_val;
    static enum output_type output;
    
public:
    /* Constructors */  
    Byte( hostUInt8 val = 0):byte_val( val){} 
    Byte( const Byte& byte):byte_val( byte.getByteVal()){}

    /* Get/set methods */
    hostUInt8 getByteVal() const
    { 
        return this->byte_val;
    }

    void setByteVal( hostUInt8 val) 
    { 
         this->byte_val = val;
    }
    
    enum output_type getOutputVal() const
    {
        return this->output;
    }

    /* Set methods for output options*/
    void setBinOut()
    {
        this->output = BIN;
    }


    void setDecOut()
    {
        this->output = DEC;
    }

    void setHexOut()
    {
        this->output = HEX;
    }
    /* Clear methods for output options*/
    void clrBinOut()
    {
        this->output = DEFAULT_OUT; // default output is hex
    }

    void clrDecOut()
    {
        this->output = DEFAULT_OUT;// default output is hex
    }

    void clrHexOut()
    {
        this->output = DEFAULT_OUT;// default output is hex
    }
    /* Member overloaded operators */
    bool operator== ( const Byte& byte)
    {
        return this->getByteVal() == byte.getByteVal();
    }

    bool operator!= ( const Byte& byte)
    {
        return this->getByteVal() != byte.getByteVal();
    }

    friend ostream& operator<< ( ostream&, const Byte&);
    friend Byte operator>> ( const Byte&, int);
    friend Byte operator<< ( const Byte&, int);
    friend Byte operator& ( const Byte&, const Byte&);
};

/* Overloaded output operator*/
inline ostream& operator<< ( ostream& os, const Byte& byte)
{   
    switch ( byte.getOutputVal())
    {
case BIN:
    for ( short i = 7; i >= 0; i--) 
    { 
        os << ( ( 1 << i) & byte.getByteVal() ? '1' : '0'); 
    }
case DEC:
        os << byte.getByteVal();
case HEX:
    os.setf( ios::hex);
    os << byte.getByteVal();
    os.setf( ios::dec);
    }
    return os;
}

/* Non-member overloaded operators */
inline Byte operator>> ( const Byte& byte, int count)
{	
    Byte temp;
    temp.setByteVal( byte.getByteVal() >> count);
    return temp;
}

inline Byte operator<< ( const Byte& byte, int count)
{	
    Byte temp;
    temp.setByteVal( byte.getByteVal() << count);
    return temp;
}

inline Byte operator& ( const Byte& left, const Byte& right)
{	
    Byte temp;
    temp.setByteVal( left.getByteVal() & right.getByteVal());
    return temp;
}


/**
 * class ByteLine implements a logical set of bytes 
 */

class ByteLine
{
    vector<Byte> *byte_line;
	static enum output_type output;
        
public:
    /* Constructors */
    ByteLine( const ByteLine& line);
    ByteLine( const Byte& byte);
        
    /* Destructor */
    virtual ~ByteLine()
    { 
        delete byte_line;
    }
    
    /* Get/set methods */
    hostUInt8 getByteVal( unsigned int byte_num) const;
    
    void setByteVal( unsigned int byte_num, hostUInt8 byte_val);

    void addByte( const Byte& byte);

    int getSizeOfLine() const
    { 
        return ( *byte_line).size();
    }

    enum output_type getOutputVal() const
    {
        return this->output;
    }

    /* Set methods for output options*/
    void setBinOut()
    {
        this->output = BIN;
    }


    void setDecOut()
    {
        this->output = DEC;
    }

    void setHexOut()
    {
        this->output = HEX;
    }
    /* Clear methods for output options*/
    void clrBinOut()
    {
        this->output = DEFAULT_OUT; // default output is hex
    }

    void clrDecOut()
    {
        this->output = DEFAULT_OUT;// default output is hex
    }

    void clrHexOut()
    {
        this->output = DEFAULT_OUT;// default output is hex
    }

    ByteLine& operator = ( ByteLine&);
    Byte operator[] ( int);
    friend ostream& operator<< ( ostream&,  ByteLine&);
    friend ByteLine operator+ ( const Byte&, const Byte&);
    friend ByteLine operator+ (  const ByteLine&,  const Byte&);
    
    
};

inline Byte ByteLine::operator []( int count)
{
    if ( ( *byte_line).empty())
    {
        cout << "ERROR: Byte line is empty!\n";
        assert( 0);
    }
    if ( count > this->getSizeOfLine())
    {
        cout << "ERROR: Size of byte line is less than target byte number!\n";
        assert( 0);
    }
    return ( *byte_line).at( count);
}

inline ByteLine& ByteLine::operator = ( ByteLine& line)
{
    if ( this != &line)
    {
        delete byte_line;
        byte_line = new vector<Byte>( line.getSizeOfLine());
        for ( int i = 0 ;i < line.getSizeOfLine() ; i++)
        {
        ( *byte_line).at( i).setByteVal( line.getByteVal( i));
        }
    }
    return *this;
}

inline ostream& operator<< ( ostream& os,  ByteLine& line)
{   
    for ( int i = 0; i < line.getSizeOfLine(); i++)
    {
			switch ( line.getOutputVal())
	{
case BIN:
	(line[i]).setBinOut();
        os << line[ i] << " | ";
case DEC:
	(line[i]).setDecOut();
	    os << line[ i] << " | ";
case HEX:
	(line[i]).setHexOut();
	    os << line[ i] << " | ";
    }
	}
    return os;
}

inline ByteLine operator+ ( const Byte& a, const Byte& b)
{	
    ByteLine temp( a);
    temp.addByte( b);
    return temp;	
}
inline ByteLine operator+ (  const ByteLine& a,  const Byte& b)
{
    ByteLine temp( a);
    temp.addByte( b);
    return temp;
}

/**
 * class MemVal implements a object to interaction with memory 
 */

class MemVal: public ByteLine
{
    ByteLine* byte_line;
    
public:
    /* Constructors and destructor */
    MemVal( unsigned int number_of_bytes_in_mem_val);
    ~MemVal()
    {
        delete byte_line;
    }
    
    /* Get/set methods */
    hostUInt8 getByteVal( unsigned int byte_num)
    {
        return byte_line->getByteVal(byte_num);
    }
    
    void setByteVal( unsigned int byte_num, hostUInt8 byte_val)
    {
        byte_line->setByteVal(byte_num, byte_val);
    }
    
    unsigned int getSizeOfMemVal() 
    { 
        return this->byte_line->getSizeOfLine(); 
    }
};

/**
 * class MemoryModel implements memory of simulated architecture and infrastructure to operate with it
 */

class MemoryModel 
{
    
public:
    /* Constructors and destructor 
    MemoryModel( unsigned size_in_bytes);
    ~MemoryModel();
     */
    
    /* Read Byte form read_ptr address 
    Byte readByte( mathAddr read_ptr);
     */
    /* Read a logical set of bytes (MemVal) form read_ptr address, the number of bytes in the set is num_of_bytes 
    MemVal* read( mathAddr read_ptr, unsigned int num_of_bytes);
     */
     
    /* Write Byte to write_ptr address 
    void writeByte( mathAddr write_ptr, Byte byte_value);
     */
    /* Write a logical set of bytes (MemVal) to write_ptr address 
    void write( mathAddr write_ptr, MemVal mem_value);
     */
};

#endif /* MEMORY_H */