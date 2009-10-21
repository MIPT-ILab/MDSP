/**
* main.cpp - test of memory
* Copyright 2009 MDSP team
*/

#include "memory.h"
void testByte()
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
}
void testByteLine()
{
	Byte a( 7);
    Byte b( 205);
    Byte c( 110);
	cout<<"test byteline class:"<<endl;
	cout<<"a: "<<'\t'<<a<<endl;
    cout<<"b: "<<'\t'<<b<<endl;
    cout<<"c: "<<'\t'<<c<<endl;
	
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
}
void testMemVal()
{
    Byte a( 7);
    Byte b( 205);
    Byte c( 110);
    ByteLine f( a + c + b);
    ByteLine d( a+( c&b));
    ByteLine dd = d + d;
    cout<<"a: "<<'\t'<<a<<endl;
    cout<<"b: "<<'\t'<<b<<endl;
    cout<<"c: "<<'\t'<<c<<endl;
    cout<<"f( a + c + b): "<<'\t'<<f<<endl;
    cout<<"d( a+(c&b));: "<<'\t'<<d<<endl;
    cout<<"dd = d+d;: "<<'\t'<<dd<<endl;
	
    MemVal mem1(f,5);
    MemVal mem2(mem1);
    MemVal mem3;
    MemVal mem4(5);
    MemVal mem5 = mem1+mem3;
    cout<<"test MemVal class:"<<endl;
    cout<<" MemVal mem1(f,5): "<<'\t'<<mem1<<endl;
    cout<<" MemVal mem2(mem1): "<<'\t'<<mem2<<endl;
    cout<<" MemVal mem3: "<<'\t'<<mem3<<endl;
    cout<<" MemVal mem4(5): "<<'\t'<<mem4<<endl;
    cout<<" MemVal mem5 = mem1+mem3: "<<'\t'<<mem5<<endl;
    mem5 = dd;
    cout<<" mem5 = dd: "<<'\t'<<mem5<<endl;

	
    cout<<" mem1.getByteLine(): "<<'\t'<<mem1.getByteLine()<<endl;
    cout<<" mem1.getByteLine(0,3): "<<'\t'<<mem1.getByteLine(0,3)<<endl;
    mem1.writeByteLine(d,3);
    cout<<" mem1.writeByteLine(d,3): "<<'\t'<<mem1<<endl;
    mem1.writeByteLine(dd);
    cout<<" mem1.writeByteLine(dd): "<<'\t'<<mem1<<endl;
    mem1.resizeMemVal(6);
    cout<<" mem1.resizeMemVal(6): "<<'\t'<<mem1<<endl;

    cout<<" mem1.getSizeOfMemVal(): "<<'\t'<<mem1.getSizeOfMemVal()<<endl;
    cout<<" mem1.getSizeOfSegment(): "<<'\t'<<mem1.getSizeOfSegment()<<endl;


}
void testMemModel();


int main()
{
    

    //testByte();
	//testByteLine();
	testMemVal();
	
	return 0;
}
