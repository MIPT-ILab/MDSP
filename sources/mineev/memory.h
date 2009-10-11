/**
 * memory.h - Specification of memory model
 * Define classes and methods to operate with memory of simulated architecture
 * Copyright 2009 MDSP team
 */
 
#ifndef MEMORY_H
#define MEMORY_H
 
#include <iostream>
#include "types.h"

using namespace std;

/**
 * class Byte implements 
 */

class Byte
{
    hostUInt8 byte_val;
    
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

	/* Member overloaded operators */
    bool operator== ( const Byte byte)
    {
        return this->getByteVal() == byte.getByteVal();
    }

    bool operator!= ( const Byte byte)
    {
        return this->getByteVal() != byte.getByteVal();
    }

    friend ostream& operator<< ( ostream& os, const Byte& byte);
};

inline ostream& operator<< ( ostream& os, const Byte& byte)
{   
    for( short i = 7; i >= 0; i--) 
    { 
        os << ( ( 1 << i) & byte.getByteVal() ? '1' : '0'); 
    }
    return os;
}

/* Non-member overloaded operators */
Byte operator>> ( const Byte byte, int count)
{	
    Byte temp;
    temp.setByteVal( byte.getByteVal() >> count);
    return temp;
}

Byte operator<< ( const Byte byte, int count)
{	
    Byte temp;
    temp.setByteVal( byte.getByteVal() << count);
    return temp;
}

Byte operator& ( const Byte left, const Byte right)
{	
    Byte temp;
    temp.setByteVal( left.getByteVal() & right.getByteVal());
    return temp;
}


/**
 * class ByteLine implements a logical set of bytes 
 */

class ByteLine: public Byte
{
    vector<Byte> byte_line;
	unsigned int size_of_line;
    
public:
    /* Constructors */
	ByteLine( unsigned int num_of_bytes_in_line);
    
    /* Destructor */
    ~ByteLine()
    { 
        byte_line.~vector<Byte>();
    }
    
    /* Get/set methods */
    hostUInt8 getByteVal( unsigned int byte_num) const;
    
    void setByteVal( unsigned int byte_num, hostUInt8 byte_val);

	void addByte( Byte byte);

	vector<Byte>::iterator getPointFirst() 
	{
		return this->byte_line.begin();
	}
	vector<Byte>::iterator getPointEnd() 
	{
		return this->byte_line.end();
	}

    unsigned int getSizeOfLine() const
    { 
        return this->size_of_line; 
    }

	friend ostream& operator<< ( ostream& os, ByteLine line);
		
};

inline ostream& operator<< ( ostream& os,  ByteLine line)
{   
    vector<Byte>::iterator pos; 
    for( pos = line.getPointFirst(); pos < line.getPointEnd(); ++pos)
    {
        os << (*pos).getByteVal() << " | ";  
    }
    return os;
}
ByteLine operator+ ( const Byte a, const Byte b)
{	
    ByteLine temp( a);
    temp.addByte( b);
    return temp;	
}
ByteLine operator+ ( const ByteLine a, const Byte b)
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
