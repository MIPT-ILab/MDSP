/**
* main.cpp - test of memory
* Copyright 2009 MDSP team
*/

#include "memory.h"

int main()
{
    Byte a( 7);
    Byte b( 205);
    Byte c = a&b;
    cout<<"test byte class:"<<endl;

    cout<<"a: "<<'\t'<<a<<endl;
    cout<<"b: "<<'\t'<<b<<endl;
    cout<<"c=a&b: "<<'\t'<<c<<endl;
    cout<<"c>>2: "<<'\t'<<( c>>2)<<endl;
    cout<<"b<<2: "<<'\t'<<( b<<2)<<endl;
    cout<<"c==a: "<<'\t'<<( c == a)<<endl;
    cout<<"c!=b: "<<'\t'<<( c != b)<<endl;

    cout<<"test byteline class:"<<endl;
	
    ByteLine f( a + c + b);
    ByteLine d = f;
    cout<<"f( a + c + b): "<<'\t'<<f<<endl;
    cout<<"d = f: "<<'\t'<<d<<endl;
    f.addByte( a&b);
    cout<<"f.addByte( a&b) : "<<'\t'<<f<<endl;
    cout<<"f.getSizeOfLine() : "<<'\t'<<f.getSizeOfLine()<<endl;
    f.setByteVal( 1, 1);
    cout<<"f.setByteVal(1,1): "<<f<<endl;
    cout<<"f.getByteVal(2): "<<( int)( f.getByteVal( 2))<<endl;
    cout<<"f.getByte(2): "<<( f.getByte( 2))<<endl;
    f.setByte( 1, a);
    cout<<"f.setByte(1,a): "<<f<<endl;


	return 0;
}
