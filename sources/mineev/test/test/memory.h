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
	
    /* Copy constructors */
    Byte( const Byte& byte):byte_val( byte.getByteVal()){}

    /* Get/set methods */

    /* Returns the Byte value in dec form */
    hostUInt8 getByteVal() const
    { 
        return this->byte_val;
    }
    
    /* Sets the Byte value in dec form */
    void setByteVal( hostUInt8 val) 
    { 
         this->byte_val = val;
    }
	
    /* Overloaded. The member operator function
    returns true only if the Byte is the same */
    bool operator== ( const Byte& byte)
    {
        return this->getByteVal() == byte.getByteVal();
    }

    /* Overloaded. The member operator function returns
    true only if the Byte differs from the one */
    bool operator!= ( const Byte& byte)
    {
        return this->getByteVal() != byte.getByteVal();
    }

    /* Overloaded. Outputs the value of the 
    current Byte object in bin form to screen */
    friend ostream& operator<< ( ostream&, const Byte&);

    /* Overloaded. Returns Byte, shifting to the left upon count */
    friend Byte operator>> ( const Byte&, int);

    /* Overloaded. Returns Byte, shifting to the right upon count */
    friend Byte operator<< ( const Byte&, int);

    /* Overloaded. Returns Byte to be a result of bitwise addition */
    friend Byte operator& ( const Byte&, const Byte&);
	
	
};

inline ostream& operator<< ( ostream& os, const Byte& byte)
{   
    for ( short i = 7; i >= 0; i--) 
    { 
        os << ( ( 1 << i) & byte.getByteVal() ? '1' : '0'); 
    }
    return os;
}
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
	    
public:
    /* Constructors */

    /* Creates empty object of Byteline class */
    ByteLine();

    /* Creates object of Byteline class 
    with count Byte, initializing with null bytes */
    ByteLine( unsigned int);

    /* Copy constructors */
    ByteLine( const ByteLine&);

    /* Conversion constructors Byte in ByteLine */
    ByteLine( const Byte&);
	    
    /* Destructor */
    virtual ~ByteLine()
    { 
        delete byte_line;
    }
    
    /* Get/set methods */

    /* The constant member function. Returns the value of 
    the Byte at position pos in the ByteLine.If that
    position is invalid, recalls exception */
    hostUInt8 getByteVal( unsigned int) const;

    /* The constant member function. Returns the 
    object of class Byte at position pos in the ByteLine.
    If that position is invalid, recalls exception */
    Byte getByte( unsigned int) const;
    
    /* Stores the object of class Byte at position pos in 
    the ByteLine.If that position is invalid, 
    recalls exception */
    void setByte( unsigned int, const Byte&);
	
    /* Adds object of Byte class to end of ByteLine */
    void addByte( const Byte&);

    /* Resize of ByteLine on count. New member 
    of ByteLine is null bytes */
    void resizeByteLine( unsigned int);

    /* The constant member function. Return size of Byteline */
    unsigned int getSizeOfLine() const
    { 
        return ( *byte_line).size();
    }

    /* Overloaded. Assign the current object of ByteLine class to another */
    ByteLine& operator = ( const ByteLine&);

    /* Overloaded. The member function returns an object of 
    class reference. Returns the Byte at position pos in the ByteLine.
    If that position is invalid, recalls exception */
    Byte operator[] ( int) const;

    /* Overloaded. Outputs the ByteLine in bin form to screen */
    friend ostream& operator<< ( ostream&, const  ByteLine&);
	
    /* Overloaded. Returns the ByteLine to be a result of addition two 
    object of class reference */
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

    /* Copy constructors */
    MemVal( const MemVal &mem_val):ByteLine( mem_val.getByteLine()),
                    size_of_segmentation( mem_val.getSizeOfSegment()){};

    /* Creates empty object of MemVal class */
    MemVal():ByteLine(), size_of_segmentation( 1){};

    /* Creates object of MemVl class ,
    ByteLine, initializing with null bytes */
    MemVal( unsigned int size):ByteLine( size), size_of_segmentation( 1){};

    /* Conversion constructors ByteLine in MemVal */
    MemVal( const ByteLine& line):ByteLine( line),
                    size_of_segmentation( 1){} ;;
		   
    /* Get/set methods */
	
    /*If size_of_segmentation different from 1, 
    adds null bytes to ByteLine 
    multiple of size_of_segmentation */
    void recountLenght();

    /* Set size_of_segmentation */
    void setSizeOfSegment( unsigned int size)
    {
        size_of_segmentation = size;
        recountLenght();
    }

    /* Returns ByteLine with specified lenght and first
    element with index.If that position is invalid, recalls exception */		
  	ByteLine getByteLine( unsigned int, unsigned int) const;

    /* Returns entire ByteLine */
    ByteLine getByteLine() const;

    /* Stores the object of class ByteLine at position pos in 
    the MemVal.If that position is invalid, 
    recalls exception */
    void writeByteLine( const ByteLine&, unsigned int);
    void writeByteLine( const ByteLine&);

    /* Resizes of MemVal on count. New member 
    of ByteLine is null bytes */	
    void resizeMemVal( unsigned int size)
    {
        resizeByteLine( size);
        recountLenght();
    }

    /* Returns size of segmentation */
    unsigned int getSizeOfSegment() const
    {
        return size_of_segmentation;
    }

    /* Returns size of MemVal */
    unsigned int getSizeOfMemVal() const
    {
        return getSizeOfLine();
    }

    /* Overloaded. Returns the MemVal to be a result of addition two 
    object of class reference */
    friend MemVal operator+ ( const MemVal&, const MemVal&);

   /* Overloaded. Assign the current object of MemVal class to another */
    MemVal& operator= ( const MemVal&);
    
};
inline MemVal operator+ ( const MemVal& a, const MemVal& b)
{
    MemVal temp ( a);
    temp.resizeMemVal( a.getSizeOfMemVal() + b.getSizeOfMemVal());
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
