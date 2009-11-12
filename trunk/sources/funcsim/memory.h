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

    /* The constant member function. Returns the Byte value in dec form */
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

    /* Overloaded. The constant member function.The member function returns an object of
    class reference. Returns the Byte at position pos in the ByteLine.
    If that position is invalid, recalls exception */
    Byte operator[] ( unsigned int) const;

    /* Overloaded. Outputs the ByteLine in bin form to screen */
    friend ostream& operator<< ( ostream&, const  ByteLine&);

    /* Overloaded. Returns the ByteLine to be a result of addition two
    object of class reference */
    friend ByteLine operator+ (  const ByteLine&,  const ByteLine&);

};

inline Byte ByteLine::operator []( unsigned int count) const
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
        for ( unsigned int i = 0 ;i < line.getSizeOfLine() ; i++)
        {
        ( *byte_line).at( i).setByteVal( line.getByteVal( i));
        }
    }
    return *this;
}

inline ostream& operator<< ( ostream& os, const ByteLine& line)
{
    for ( unsigned int i = 0; i < line.getSizeOfLine(); i++)
    {
        os << line[ i] << " | ";
    }
    return os;
}

inline ByteLine operator+ (  const ByteLine& a,  const ByteLine& b)
{
    ByteLine temp( a);

    for ( unsigned int i = 0 ; i < b.getSizeOfLine(); i++)
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
                         size_of_segmentation( 1){};

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

    /* The constant member function. Returns ByteLine with specified
	lenght and first element with index.If that position is invalid,
	recalls exception */
  	ByteLine getByteLine( unsigned int, unsigned int) const;

    /* The constant member function. Returns entire ByteLine */
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

    /* The constant member function. Returns size of segmentation */
    unsigned int getSizeOfSegment() const
    {
        return size_of_segmentation;
    }

    /* The constant member function. Returns size of MemVal */
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
	if ( this != &mem_val)
    {
	    ByteLine temp( mem_val.getByteLine());
	    resizeMemVal( mem_val.getSizeOfMemVal());
	    setSizeOfSegment( mem_val.getSizeOfSegment());
	    this->writeByteLine( temp);
	}
	return *this;
}

/**
 * class MemoryModel implements memory of simulated architecture and infrastructure to operate with it
 */

typedef map< mathAddr, MemVal, std::less< mathAddr> > memMap;
class MemoryModel
{

    memMap *mem_model;
    unsigned int size_of_segmentation;

    /* Closed copy constructors */
    MemoryModel( const MemoryModel&);


public:

    /* Constructors and destructor */

    /* Creates empty object of MemoryModel class
	with specified size of segmentation */
    MemoryModel( unsigned int size);

    virtual ~MemoryModel()
	{
		delete mem_model;
	}


    /* Returns ByteLine with specified lenght from specified
    address. If that position is invalid, recalls exception */
	ByteLine read( mathAddr, unsigned int);

	/* Rerurns pointer to object of MemVal class if will be
	found in MemoryModel.If not returns poiter to end of MemoryModel.
	Used in read member function */
    memMap::iterator find( mathAddr);

    /* Rerurns pointer to object of MemVal class if will be
	found in MemoryModel.If not create MemVal with specified
    address. Used in write member function */
	memMap::iterator findOrInit( mathAddr);

    /*The constant member function.Returns pointer to first
	object of MemVal class in MemoryModel */
	memMap::iterator getFirstIter() const
	{
		memMap::iterator pos;
		return pos = ( *mem_model).begin();
	}
	/*The constant member function. Returns pointer to last
	object of MemVal class in MemoryModel */
	memMap::iterator getLastIter() const
	{
		memMap::iterator pos;
		return pos = ( *mem_model).end();
	}


    /* Merges two object of MemVal class in MemoryModel*/
    void mergeMemVal( memMap::iterator, MemVal*);

	/* Counts amount of empty address between two object of MemVal class*/
	unsigned int countDistance( const memMap::iterator);


    /* Stores the object of class ByteLine at specified address */
    void write( mathAddr write_ptr, const ByteLine&);

    /* Stores the object of class MemVal at specified address */
	void write( mathAddr write_ptr, MemVal mem_value);

     /* Overloaded. Checks of belonging specified address to object of class MemVal*/
	friend bool operator== ( memMap::iterator, mathAddr);

	/* Overloaded. Outputs the contents of MemoryModel to screen */
	friend ostream& operator<< ( ostream&,  MemoryModel&);

    /* Overloaded. Returns pointer to the next object of class MemVal*/
	friend memMap::iterator operator+ ( const memMap::iterator, int);

};

inline bool operator ==( memMap::iterator p, mathAddr adrr)
{

	if ( ( adrr >= p->first ) && ( ( ( p->second).getSizeOfMemVal()+ p->first - 1) >=  adrr))
	{
		return true;
	}
	return false;
}
inline ostream& operator<< ( ostream& os,  MemoryModel& model)
{
	memMap::iterator pos;
	for ( pos = model.getFirstIter(); pos != model.getLastIter(); ++pos)
	{
		os<<"address: "<< pos->first<<'\t'<< pos->second<<endl;
	}
	return os;

}
inline memMap::iterator operator+ ( const memMap::iterator pos,  int count)
{
	memMap::iterator temp = pos;
	return ++temp;
}



#endif /* MEMORY_H */
