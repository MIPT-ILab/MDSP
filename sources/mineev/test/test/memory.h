/**
 * memory.h - Specification of memory model
 * Define classes and methods to operate with memory of simulated architecture
 * Copyright 2009 MDSP team
 */

#ifndef MEMORY_H
#define MEMORY_H
 
#include <iostream>
#include <vector>
#include <map>
#include "types.h"
#include <cassert>


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
	//int* decToBin();

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
	//unsigned int operator[]( unsigned int);
	
};

inline ostream& operator<< ( ostream& os, const Byte& byte)
{   
    for ( short i = 7; i >= 0; i--) 
    { 
        os << ( ( 1 << i) & byte.getByteVal() ? '1' : '0'); 
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


/*inline unsigned int Byte::operator[]( unsigned int count)
{
    if ( count > sizeof( hostUInt8))
    {
        cout << "ERROR: Size of byte is less than target bit number!\n";
        assert( 0);
    }
	return ( ( 1 << count) & this->getByteVal() ? 1 : 0); 
}
inline int* Byte::decToBin()
{
	int *p = new int( 8);
	for ( short i = 7; i >= 0; i--) 
    { 
        p[i] = ( ( 1 << i) & this->getByteVal() ? 1 : 0); 
    }
    return p;
}
*/

/**
 * class ByteLine implements a logical set of bytes 
 */

class ByteLine
{
    vector<Byte> *byte_line;
	    
public:
    /* Constructors */
	ByteLine();
	ByteLine( unsigned int count);
    ByteLine( const ByteLine& line);
    ByteLine( const Byte& byte);
	    
    /* Destructor */
    virtual ~ByteLine()
    { 
        delete byte_line;
    }
    
    /* Get/set methods */
    hostUInt8 getByteVal( unsigned int byte_num) const;
    Byte getByte( unsigned int byte_num) const;
    
    void setByteVal( unsigned int byte_num, hostUInt8 byte_val);
    void setByte( unsigned int byte_num, const Byte& byte);

    void addByte( const Byte& byte);
    void resizeByteLine( unsigned int count);

    unsigned int getSizeOfLine() const
    { 
        return ( *byte_line).size();
    }
    ByteLine& operator = ( const ByteLine&);
    Byte operator[] ( int) const;
    friend ostream& operator<< ( ostream&, const  ByteLine&);
    friend ByteLine operator+ ( const Byte&, const Byte&);
    friend ByteLine operator+ (  const ByteLine&,  const Byte&);
    friend ByteLine operator+ (  const ByteLine&,  const ByteLine&);
     	
};

inline Byte ByteLine::operator []( int count) const
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

inline ByteLine& ByteLine::operator = ( const ByteLine& line)
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

inline ostream& operator<< ( ostream& os, const ByteLine& line)
{   
    for ( int i = 0; i < line.getSizeOfLine(); i++)
    {
        os << line[ i] << " | ";  
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
inline ByteLine operator+ (  const ByteLine& a,  const ByteLine& b)
{
    ByteLine temp( a); 
	
    for ( int i = 0 ; i < b.getSizeOfLine(); i++)
    {
        temp.addByte( b.getByte( i));;
    }
    return temp;
}

/**
 * class MemVal implements a object to interaction with memory 
 */

class MemVal: public ByteLine
{
    unsigned int size_of_segmentation;
	    
public:
	
    /* Constructors and destructor */

    MemVal( const MemVal &mem_val):ByteLine( mem_val.getByteLine()),
                    size_of_segmentation( mem_val.getSizeOfSegment()){} ;

    MemVal():ByteLine(), size_of_segmentation( 0){};
    MemVal( unsigned int size):ByteLine( size), size_of_segmentation( size){};

    MemVal( const ByteLine&, unsigned int);
		   
    /* Get/set methods */
	
    void recountLenght();
    void setSizeOfSegment( unsigned int size)
    {
        size_of_segmentation = size;
    }

		
  	ByteLine getByteLine( unsigned int, unsigned int) const;
    ByteLine getByteLine() const;
	
    void writeByteLine( const ByteLine&, unsigned int);
    void writeByteLine( const ByteLine&);
    void resizeMemVal( unsigned int);


    unsigned int getSizeOfSegment() const
    {
        return size_of_segmentation;
    }
    unsigned int getSizeOfMemVal() const
    {
        return getSizeOfLine();
    }
    friend MemVal operator+ ( const MemVal&, const MemVal&);
    MemVal& operator= ( const MemVal&);
    MemVal& operator= ( const ByteLine&);
    
};
inline MemVal operator+ ( const MemVal& a, const MemVal& b)
{
    MemVal temp ( a);
    temp.resizeByteLine( a.getSizeOfMemVal() + b.getSizeOfMemVal());
    temp.writeByteLine( b.getByteLine(), a.getSizeOfMemVal());
    return temp;
}
inline MemVal& MemVal::operator= ( const MemVal& mem_val)
{
	ByteLine temp( mem_val.getByteLine());
	resizeMemVal( mem_val.getSizeOfMemVal());
	setSizeOfSegment( mem_val.getSizeOfSegment());
	this->writeByteLine( temp);
	return *this;
}
inline MemVal& MemVal::operator= ( const ByteLine& line)
{
	ByteLine temp( line);
	resizeMemVal( line.getSizeOfLine());
	this->writeByteLine( temp);
	return *this;
}

/**
 * class MemoryModel implements memory of simulated architecture and infrastructure to operate with it
 */
/*
class MemoryModel 
{
	//map< MemVal, mathAddr, std::greater<mathAddr> > *mem_model;
	map< MemVal, mathAddr > *mem_model;
	unsigned int size_of_segmentation;
    
public:
	
    // Constructors and destructor 
    MemoryModel( unsigned int size_of_segmentation );
    ~MemoryModel()
	{
		delete mem_model;
	}
     
    
   
    MemVal read( mathAddr read_ptr, unsigned int num_of_bytes);
		
    map< MemVal, mathAddr>::iterator find( mathAddr ptr);
	map< MemVal, mathAddr>::iterator findOrInit( mathAddr ptr);
    void mergeMemVal(map< MemVal, mathAddr>::iterator, MemVal);
	unsigned int countDistance( map< MemVal, mathAddr>::iterator);
     
    // Write Byte to write_ptr address 
    void write( mathAddr write_ptr, ByteLine line);
	void write( mathAddr write_ptr, MemVal mem_value);
	friend bool operator ==( map< MemVal, mathAddr>::iterator, mathAddr);
        
};
inline bool operator ==( map< MemVal, mathAddr>::iterator p , mathAddr adrr)
{

	if( (adrr> p->second) && (((p->first).getSizeOfMemVal()+ p->second  )>  adrr) )
	{
		return true;
	}
	return false;
}
*/
#endif /* MEMORY_H */
