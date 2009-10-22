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
    
    f.setByte( 1, 1);
    cout<<"f.setByte(1,1): "<<f<<endl;
    cout<<"f.getByte(2): "<<( int)( f.getByteVal( 2))<<endl;
    cout<<"f.getByte(2): "<<( f.getByte( 2))<<endl;
    f.setByte( 1, a);
    cout<<"f.setByte(1,a): "<<f<<endl;
	cout<<"f.getSizeOfLine() : "<<'\t'<<f.getSizeOfLine()<<endl;
	f.resizeByteLine( 5);
	cout<<"f.resizeByteLine( 5) : "<<'\t'<<f<<endl;
	cout<<"f.getSizeOfLine() : "<<'\t'<<f.getSizeOfLine()<<endl;
}
void testMemVal()
{
    Byte a( 7);
    Byte b( 205);
    Byte c( 110);
	Byte e( 255);
    ByteLine f( a + c + b);
    ByteLine d( a+( c&b));
    ByteLine dd = e + e;
    cout<<"a: "<<'\t'<<a<<endl;
    cout<<"b: "<<'\t'<<b<<endl;
    cout<<"c: "<<'\t'<<c<<endl;
    cout<<"e: "<<'\t'<<e<<endl;
    cout<<"f( a + c + b): "<<'\t'<<f<<endl;
    cout<<"d( a+(c&b)): "<<'\t'<<d<<endl;
    cout<<"dd = e + e: "<<'\t'<<dd<<endl;
	
    MemVal mem1(f);
    MemVal mem2(mem1);
    MemVal mem3;
    MemVal mem4(5);
    MemVal mem5 = mem1+mem3;
    cout<<"test MemVal class:"<<endl;
    cout<<" MemVal mem1(f): "<<'\t'<<mem1<<endl;
    cout<<" MemVal mem2(mem1): "<<'\t'<<mem2<<endl;
    cout<<" MemVal mem3: "<<'\t'<<mem3<<endl;
    cout<<" MemVal mem4(5): "<<'\t'<<mem4<<endl;
    cout<<" MemVal mem5 = mem1+mem3: "<<'\t'<<mem5<<endl;
    mem3 = dd;
    cout<<" mem3 = dd: "<<'\t'<<mem3<<endl;
	mem3.setSizeOfSegment(5);
    cout<<" mem3.setSizeOfSegment(5): "<<'\t'<<mem3<<endl;	
    cout<<" mem1.getByteLine(): "<<'\t'<<mem1.getByteLine()<<endl;
    cout<<" mem3.getByteLine(0,3): "<<'\t'<<mem3.getByteLine(0,3)<<endl;
    mem3.writeByteLine(d,3);
    cout<<" mem1.writeByteLine(d,3): "<<'\t'<<mem3<<endl;
    mem3.writeByteLine(d);
    cout<<" mem1.writeByteLine(d): "<<'\t'<<mem3<<endl;
    mem3.resizeMemVal(6);
    cout<<" mem3.resizeMemVal(6): "<<'\t'<<mem3<<endl;

    cout<<" mem3.getSizeOfMemVal(): "<<'\t'<<mem3.getSizeOfMemVal()<<endl;
    cout<<" mem3.getSizeOfSegment(): "<<'\t'<<mem3.getSizeOfSegment()<<endl;


}
void testMemModel();


int main()
{
    

    //testByte();
	//testByteLine();
	testMemVal();
	
	return 0;
}
