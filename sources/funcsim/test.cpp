/**
 * test.cpp - Unit tests
 * @author Dmitry Ustyugov, Pavel Zaichenkov, Alexander Potashev, Yura Savchenko
 * Copyright 2009 MDSP team
 */

#include <string>

#include "memory.h"
#include "operation.h"
#include "register_file.h"
#include "cout_wrapper.h"

using namespace std;

void testByte()
{
    Byte a( 7);
    Byte b( 7);
    Byte c = a&b;
    b.setBinOut();
    a.setDecOut();
    c.setHexOut();

    //testing output format for a
    setTestingCoutHandler();
    cout<<"a:outputFormat "<<a.getOutputFormat()<<endl;
    setStandardCoutHandler();
    if ( getTestingCoutBuffer().compare( "a:outputFormat 1\n"))
    {
        cout<<"ERROR: wrong output format"<<endl;
        assert(0);
    }

    //testing output format for b
    setTestingCoutHandler();
    cout<<"b:outputFormat "<<b.getOutputFormat()<<endl;
    setStandardCoutHandler();
    if ( getTestingCoutBuffer().compare( "b:outputFormat 0\n"))
    {
        cout<<"ERROR: wrong output format"<<endl;
        assert(0);
    }

    //testing output format for c
    setTestingCoutHandler();
    cout<<"c:outputFormat "<<c.getOutputFormat()<<endl;
    setStandardCoutHandler();
    if ( getTestingCoutBuffer().compare( "c:outputFormat 2\n"))
    {
        cout<<"ERROR: wrong output format"<<endl;
        assert(0);
    }

    //testing byte value for a
    setTestingCoutHandler();
    cout<<"a: "<<a<<endl;
    setStandardCoutHandler();
    if ( getTestingCoutBuffer().compare( "a: 7\n"))
    {
        cout<<"ERROR: wrong byte value"<<endl;
        assert(0);
    }

    //testing byte value for b
    setTestingCoutHandler();
    cout<<"b: "<<b<<endl;
    setStandardCoutHandler();
    if ( getTestingCoutBuffer().compare( "b: 00000111\n"))
    {
        cout<<"ERROR: wrong byte value"<<endl;
        assert(0);
    }

    //testing bitwise addition
    setTestingCoutHandler();
    cout<<"c=a&b: "<<c<<endl;
    setStandardCoutHandler();
    if ( getTestingCoutBuffer().compare( "c=a&b: 0x7\n"))
    {
        cout<<"ERROR: bitwise addition"<<endl;
        assert(0);
    }
    
    //testing shifting to the left
    setTestingCoutHandler();
    cout<<"c>>2: "<< ( c>>2) <<endl;
    setStandardCoutHandler();
    if ( getTestingCoutBuffer().compare( "c>>2: 0x1\n"))
    {
        cout<<"ERROR: shifting to the left"<<endl;
        assert(0);
    }

    //testing shifting to the right
    setTestingCoutHandler();
    cout<<"b<<2: "<< ( b<<2) <<endl;
    setStandardCoutHandler();
    if ( getTestingCoutBuffer().compare( "b<<2: 0x1c\n"))
    {
        cout<<"ERROR: shifting to the right"<<endl;
        assert(0);
    }

    //testing equal comparing
    setTestingCoutHandler();
    cout<<"c==a: "<<( c == a)<<endl;
    setStandardCoutHandler();
    if ( getTestingCoutBuffer().compare( "c==a: 1\n"))
    {
        cout<<"ERROR: equal comparing"<<endl;
        assert(0);
    }

    //testing not equal comparing
    setTestingCoutHandler();
    cout<<"c!=b: "<<( c != b)<<endl;
    setStandardCoutHandler();
    if ( getTestingCoutBuffer().compare( "c!=b: 0\n"))
    {
        cout<<"ERROR: not equal comparing"<<endl;
        assert(0);
    }

    cout<<"test byte class: ok"<<endl;
}

void testByteLine()
{
    unsigned int testConstructor = 3;
    Byte test1( 7);
    Byte test2( 110);
    Byte test3( 205);
    hostUInt8 testUInt8 = 044;
    hostUInt16 testUInt16 = 0x34c6;
    hostUInt32 testUInt32 = 45678;
    unsigned int test8 = 10;
    unsigned int test16 = 123;
    unsigned int test32 = 45678;


    ByteLine testConstructor1(testConstructor);
    ByteLine testConstructorCopy(testConstructor1);
    ByteLine testConstructorByte(test1 + test2 + test3);
    ByteLine testConstructorUInt8L( testUInt8, LOW_FIRST);
    ByteLine testConstructorUInt16L( testUInt16, LOW_FIRST);
    ByteLine testConstructorUInt32L( testUInt32, LOW_FIRST);
    ByteLine testConstructorUInt8H( testUInt8, HIGH_FIRST);
    ByteLine testConstructorUInt16H( testUInt16, HIGH_FIRST);
    ByteLine testConstructorUInt32H( testUInt32, HIGH_FIRST);

    ByteLine testConstructorUInt8L1(test8 , HUINT8, LOW_FIRST);
    ByteLine testConstructorUInt16L1(test16 , HUINT16, LOW_FIRST);
    ByteLine testConstructorUInt32L1(test32 , HUINT32, LOW_FIRST);
    ByteLine testConstructorUInt8H1(test8 , HUINT8, HIGH_FIRST);
    ByteLine testConstructorUInt16H1(test16 , HUINT16, HIGH_FIRST);
    ByteLine testConstructorUInt32H1(test32 , HUINT32, HIGH_FIRST);

    ByteLine testSetByte( testConstructorByte);
    ByteLine testAddByte( testConstructorByte);
    ByteLine testResizeByteLine( testConstructorByte);
    ByteLine testOutputFormatBIN( testConstructorByte);
    ByteLine testOutputFormatHEX( testConstructorByte);
    ByteLine testOutputFormatDEC( testConstructorByte);
    ByteLine testEquality( testConstructor1);
    ByteLine testSum;
    ByteLine testShiftLeft;
    ByteLine testShifrRight;
    
    testConstructorUInt8L.setBinOut();
    testConstructorUInt16L.setBinOut();
    testConstructorUInt32L.setBinOut();
    testConstructorUInt8H.setBinOut();
    testConstructorUInt16H.setBinOut();
    testConstructorUInt32H.setBinOut();
    testUInt8 = testConstructorUInt8H.getHostUInt8();
    testUInt16 = testConstructorUInt16H.getHostUInt16();
    testUInt32 = testConstructorUInt32H.getHostUInt32();
    unsigned int testByteVal = testConstructorByte.getByteVal(2);
    test1 = testConstructorByte.getByte(2);
    testConstructor = 2;
    testSetByte.setByte(testConstructor, test1);
    testAddByte.addByte(test1);
    testResizeByteLine.resizeByteLine(testConstructor);
    testConstructor = testConstructor1.getSizeOfLine();
    testOutputFormatBIN.setBinOut();
    testOutputFormatHEX.setHexOut();
    testOutputFormatDEC.setDecOut();
    testEquality = testConstructorByte;
    testSum = (testEquality + testConstructorByte);
        
    //testing byteline constructor with unsigned int parmeter
    setTestingCoutHandler();
    cout<<"testConstructor1: "<< testConstructor1 <<endl;
    setStandardCoutHandler();
    if ( getTestingCoutBuffer().compare( "testConstructor1: 0 | 0 | 0 | \n"))
    {
        cout<<"ERROR: byteline constructor with unsigned int parmeter"<<endl;
        assert(0);
    }
    
    //testing byteline constructor copy
    setTestingCoutHandler();
    cout<<"testConstructorCopy: "<< testConstructorCopy <<endl;
    setStandardCoutHandler();
    if ( getTestingCoutBuffer().compare( "testConstructorCopy: 0 | 0 | 0 | \n"))
    {
        cout<<"ERROR: byteline constructor copy"<<endl;
        assert(0);
    }

    //testing byteline constructor byte
    setTestingCoutHandler();
    cout<<"testConstructorByte: "<< testConstructorByte <<endl;
    setStandardCoutHandler();
    if ( getTestingCoutBuffer().compare( "testConstructorByte: 0x7 | 0x6e | 0xcd | \n"))
    {
        cout<<"ERROR: constructor byte"<<endl;
        assert(0);
    }

    //testing byteline constructor byte
    setTestingCoutHandler();
    cout<<"testConstructorByte: "<< testConstructorByte <<endl;
    setStandardCoutHandler();
    if ( getTestingCoutBuffer().compare( "testConstructorByte: 0x7 | 0x6e | 0xcd | \n"))
    {
        cout<<"ERROR: constructor byte"<<endl;
        assert(0);
    }

    //testing byteline constructor byte
    setTestingCoutHandler();
    cout<<"testConstructorByte: "<< testConstructorByte <<endl;
    setStandardCoutHandler();
    if ( getTestingCoutBuffer().compare( "testConstructorByte: 0x7 | 0x6e | 0xcd | \n"))
    {
        cout<<"ERROR: constructor byte"<<endl;
        assert(0);
    }

    //testing byteline constructor hostUInt8 low first
    setTestingCoutHandler();
    cout<<"testConstructorUInt8L: "<< testConstructorUInt8L <<endl;
    setStandardCoutHandler();
    if ( getTestingCoutBuffer().compare( "testConstructorUInt8L: 00100100 | \n"))
    {
        cout<<"ERROR: constructor hostUInt8 low first"<<endl;
        assert(0);
    }

    //testing byteline constructor hostUInt16 low first
    setTestingCoutHandler();
    cout<<"testConstructorUInt16L: "<< testConstructorUInt16L <<endl;
    setStandardCoutHandler();
    if ( getTestingCoutBuffer().compare( "testConstructorUInt16L: 00110100 | 11000110 | \n"))
    {
        cout<<"ERROR: constructor hostUInt16 low first"<<endl;
        assert(0);
    }

    //testing byteline constructor hostUInt32 low first
    setTestingCoutHandler();
    cout<<"testConstructorUInt32L: "<< testConstructorUInt32L <<endl;
    setStandardCoutHandler();
    if ( getTestingCoutBuffer().compare( "testConstructorUInt32L: 00000000 | 00000000 | 10110010 | 01101110 | \n"))
    {
        cout<<"ERROR: constructor hostUInt32 low first"<<endl;
        assert(0);
    }

    //testing byteline constructor hostUInt8 high first
    setTestingCoutHandler();
    cout<<"testConstructorUInt8H: "<< testConstructorUInt8H <<endl;
    setStandardCoutHandler();
    if ( getTestingCoutBuffer().compare( "testConstructorUInt8H: 00100100 | \n"))
    {
        cout<<"ERROR: constructor hostUInt8 high first"<<endl;
        assert(0);
    }

    //testing byteline constructor hostUInt16 high first
    setTestingCoutHandler();
    cout<<"testConstructorUInt16H: "<< testConstructorUInt16H <<endl;
    setStandardCoutHandler();
    if ( getTestingCoutBuffer().compare( "testConstructorUInt16H: 11000110 | 00110100 | \n"))
    {
        cout<<"ERROR: constructor hostUInt16 high first"<<endl;
        assert(0);
    }

    //testing byteline constructor hostUInt32 high first
    setTestingCoutHandler();
    cout<<"testConstructorUInt32H: "<< testConstructorUInt32H <<endl;
    setStandardCoutHandler();
    if ( getTestingCoutBuffer().compare( "testConstructorUInt32H: 01101110 | 10110010 | 00000000 | 00000000 | \n"))
    {
        cout<<"ERROR: constructor hostUInt32 high first"<<endl;
        assert(0);
    }

    //testing getHostUInt8
    setTestingCoutHandler();
    cout<<"testUInt8: "<< testUInt8 <<endl;
    setStandardCoutHandler();
    if ( getTestingCoutBuffer().compare( "testUInt8: $\n"))
    {
        cout<<"ERROR: getHostUInt8"<<endl;
        assert(0);
    }

    //testing getHostUInt16
    setTestingCoutHandler();
    cout<<"testUInt16: "<< testUInt16 <<endl;
    setStandardCoutHandler();
    if ( getTestingCoutBuffer().compare( "testUInt16: 13510\n"))
    {
        cout<<"ERROR: getHostUInt16"<<endl;
        assert(0);
    }

    //testing getHostUInt32
    setTestingCoutHandler();
    cout<<"testUInt32: "<< testUInt32 <<endl;
    setStandardCoutHandler();
    if ( getTestingCoutBuffer().compare( "testUInt32: 45678\n"))
    {
        cout<<"ERROR: getHostUInt32"<<endl;
        assert(0);
    }

    //testing getByteVal
    setTestingCoutHandler();
    cout<<"testByteVal: "<< testByteVal <<endl;
    setStandardCoutHandler();
    if ( getTestingCoutBuffer().compare( "testByteVal: 205\n"))
    {
        cout<<"ERROR: getByteVal"<<endl;
        assert(0);
    }

    //testing getByte
    setTestingCoutHandler();
    cout<<"test1: "<< test1 <<endl;
    setStandardCoutHandler();
    if ( getTestingCoutBuffer().compare( "test1: 0xcd\n"))
    {
        cout<<"ERROR: getByte"<<endl;
        assert(0);
    }

    //testing setByte
    setTestingCoutHandler();
    cout<<"testSetByte: "<< testSetByte <<endl;
    setStandardCoutHandler();
    if ( getTestingCoutBuffer().compare( "testSetByte: 0x7 | 0x6e | 0xcd | \n"))
    {
        cout<<"ERROR: setByte"<<endl;
        assert(0);
    }

    //testing addByte
    setTestingCoutHandler();
    cout<<"testAddByte: "<< testAddByte <<endl;
    setStandardCoutHandler();
    if ( getTestingCoutBuffer().compare( "testAddByte: 0x7 | 0x6e | 0xcd | 0xcd | \n"))
    {
        cout<<"ERROR: addByte"<<endl;
        assert(0);
    }

    //testing ResizeByteLine
    setTestingCoutHandler();
    cout<<"testResizeByteLine: "<< testResizeByteLine <<endl;
    setStandardCoutHandler();
    if ( getTestingCoutBuffer().compare( "testResizeByteLine: 0x7 | 0x6e | \n"))
    {
        cout<<"ERROR: ResizeByteLine"<<endl;
        assert(0);
    }

    //testing getSizeOfLine
    setTestingCoutHandler();
    cout<<"testConstructor: "<< testConstructor <<endl;
    setStandardCoutHandler();
    if ( getTestingCoutBuffer().compare( "testConstructor: 3\n"))
    {
        cout<<"ERROR: getSizeOfLine"<<endl;
        assert(0);
    }

    //testing OutputFormatBIN
    setTestingCoutHandler();
    cout<<"testOutputFormatBIN: "<< testOutputFormatBIN.getOutputFormat() <<endl;
    setStandardCoutHandler();
    if ( getTestingCoutBuffer().compare( "testOutputFormatBIN: 0\n"))
    {
        cout<<"ERROR: OutputFormatBIN"<<endl;
        assert(0);
    }

    //testing OutputFormatDEC
    setTestingCoutHandler();
    cout<<"testOutputFormatDEC: "<< testOutputFormatDEC.getOutputFormat() <<endl;
    setStandardCoutHandler();
    if ( getTestingCoutBuffer().compare( "testOutputFormatDEC: 1\n"))
    {
        cout<<"ERROR: OutputFormatDEC"<<endl;
        assert(0);
    }

    //testing OutputFormatHEX
    setTestingCoutHandler();
    cout<<"testOutputFormatHEX: "<< testOutputFormatHEX.getOutputFormat() <<endl;
    setStandardCoutHandler();
    if ( getTestingCoutBuffer().compare( "testOutputFormatHEX: 2\n"))
    {
        cout<<"ERROR: OutputFormatHEX"<<endl;
        assert(0);
    }

    testOutputFormatBIN.clrBinOut();
    testOutputFormatDEC.clrDecOut();
    testOutputFormatHEX.clrHexOut();

    //testing OutputFormatBIN clrBinOut
    setTestingCoutHandler();
    cout<<"testOutputFormatBINclrBinOut: "<< testOutputFormatBIN.getOutputFormat() <<endl;
    setStandardCoutHandler();
    if ( getTestingCoutBuffer().compare( "testOutputFormatBINclrBinOut: 2\n"))
    {
        cout<<"ERROR: OutputFormatBIN"<<endl;
        assert(0);
    }

    //testing OutputFormatDEC clrDecOut
    setTestingCoutHandler();
    cout<<"testOutputFormatDECclrDecOut: "<< testOutputFormatDEC.getOutputFormat() <<endl;
    setStandardCoutHandler();
    if ( getTestingCoutBuffer().compare( "testOutputFormatDECclrDecOut: 2\n"))
    {
        cout<<"ERROR: OutputFormatDEC"<<endl;
        assert(0);
    }

    //testing OutputFormatHEX clrHexOut
    setTestingCoutHandler();
    cout<<"testOutputFormatHEXclrHexOut: "<< testOutputFormatHEX.getOutputFormat() <<endl;
    setStandardCoutHandler();
    if ( getTestingCoutBuffer().compare( "testOutputFormatHEXclrHexOut: 2\n"))
    {
        cout<<"ERROR: OutputFormatHEX"<<endl;
        assert(0);
    }

    //testing Equality
    setTestingCoutHandler();
    cout<<"testEquality: "<< testEquality <<endl;
    setStandardCoutHandler();
    if ( getTestingCoutBuffer().compare( "testEquality: 0x7 | 0x6e | 0xcd | \n"))
    {
        cout<<"ERROR: Equality"<<endl;
        assert(0);
    }

    //testing Output
    setTestingCoutHandler();
    cout<<"testOutput: "<< testEquality[2] <<endl;
    setStandardCoutHandler();
    if ( getTestingCoutBuffer().compare( "testOutput: 0xcd\n"))
    {
        cout<<"ERROR: Output"<<endl;
        assert(0);
    }

    //testing testShiftLeft
    setTestingCoutHandler();
    cout<<"testShiftLeft: "<< (testConstructorByte<<8) <<endl;
    setStandardCoutHandler();
    if ( getTestingCoutBuffer().compare( "testShiftLeft: 0 | 0x7 | 0x6e | \n"))
    {
        cout<<"ERROR: testShiftLeft"<<endl;
        assert(0);
    }

    //testing testShiftRight
    setTestingCoutHandler();
    cout<<"testShiftRight: "<< (testConstructorByte>>8) <<endl;
    setStandardCoutHandler();
    if ( getTestingCoutBuffer().compare( "testShiftRight: 0x6e | 0xcd | 0 | \n"))
    {
        cout<<"ERROR: testShiftRight"<<endl;
        assert(0);
    }

    //testing Sum
    setTestingCoutHandler();
    cout<<"testSum: "<< testSum <<endl;
    setStandardCoutHandler();
    if ( getTestingCoutBuffer().compare( "testSum: 0x7 | 0x6e | 0xcd | 0x7 | 0x6e | 0xcd | \n"))
    {
        cout<<"ERROR: Sum"<<endl;
        assert(0);
    }

    //testing byteline constructor hostUInt8 low first 1
    setTestingCoutHandler();
    cout<<"testConstructorUInt8L1: "<< testConstructorUInt8L1 <<endl;
    setStandardCoutHandler();
    if ( getTestingCoutBuffer().compare( "testConstructorUInt8L1: 0xa | \n"))
    {
        cout<<"ERROR: constructor hostUInt8 low first"<<endl;
        assert(0);
    }

    //testing byteline constructor hostUInt16 low first 1
    setTestingCoutHandler();
    cout<<"testConstructorUInt16L1: "<< testConstructorUInt16L1 <<endl;
    setStandardCoutHandler();
    if ( getTestingCoutBuffer().compare( "testConstructorUInt16L1: 0 | 0x7b | \n"))
    {
        cout<<"ERROR: constructor hostUInt16 low first"<<endl;
        assert(0);
    }

    //testing byteline constructor hostUInt32 low first 1
    setTestingCoutHandler();
    cout<<"testConstructorUInt32L1: "<< testConstructorUInt32L1 <<endl;
    setStandardCoutHandler();
    if ( getTestingCoutBuffer().compare( "testConstructorUInt32L1: 0 | 0 | 0xb2 | 0x6e | \n"))
    {
        cout<<"ERROR: constructor hostUInt32 low first"<<endl;
        assert(0);
    }

    //testing byteline constructor hostUInt8 high first 1
    setTestingCoutHandler();
    cout<<"testConstructorUInt8H1: "<< testConstructorUInt8H1 <<endl;
    setStandardCoutHandler();
    if ( getTestingCoutBuffer().compare( "testConstructorUInt8H1: 0xa | \n"))
    {
        cout<<"ERROR: constructor hostUInt8 high first"<<endl;
        assert(0);
    }

    //testing byteline constructor hostUInt16 high first 1
    setTestingCoutHandler();
    cout<<"testConstructorUInt16H1: "<< testConstructorUInt16H1 <<endl;
    setStandardCoutHandler();
    if ( getTestingCoutBuffer().compare( "testConstructorUInt16H1: 0x7b | 0 | \n"))
    {
        cout<<"ERROR: constructor hostUInt16 high first"<<endl;
        assert(0);
    }

    //testing byteline constructor hostUInt32 high first 1
    setTestingCoutHandler();
    cout<<"testConstructorUInt32H1: "<< testConstructorUInt32H1 <<endl;
    setStandardCoutHandler();
    if ( getTestingCoutBuffer().compare( "testConstructorUInt32H1: 0x6e | 0xb2 | 0 | 0 | \n"))
    {
        cout<<"ERROR: constructor hostUInt32 high first"<<endl;
        assert(0);
    }

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
    MemVal mem1(f);
    MemVal mem2(mem1);
    RegVal rv( 1);
    MemVal mem3( rv, 1);
    MemVal mem4(5);
    MemVal mem5 = mem1+mem4;

    //testing MemVal output
    setTestingCoutHandler();
    cout<<" MemVal mem1(f): "<<'\t'<<mem1<<endl;
    setStandardCoutHandler();
    if ( getTestingCoutBuffer().compare( " MemVal mem1(f):  0x7 | 0x6e | 0xcd | \n"))
    {
        cout<<"ERROR: wrong output"<<endl;
        assert(0);
    }

    setTestingCoutHandler();
    cout<<" MemVal mem2(mem1): "<<'\t'<<mem2<<endl;
    setStandardCoutHandler();
    if ( getTestingCoutBuffer().compare( " MemVal mem2(mem1):   0x7 | 0x6e | 0xcd | \n"))
    {
        cout<<"ERROR: wrong output"<<endl;
        assert(0);
    }

    setTestingCoutHandler();
    cout<<" MemVal mem3: "<<'\t'<<mem3<<endl;
    setStandardCoutHandler();
    if ( getTestingCoutBuffer().compare( " MemVal mem3:     \n"))
    {
        cout<<"ERROR: wrong output"<<endl;
        assert(0);
    }
    
    setTestingCoutHandler();
    cout<<" MemVal mem4(5): "<<'\t'<<mem4<<endl;
    setStandardCoutHandler();
    if ( getTestingCoutBuffer().compare( " MemVal mem4(5):  0 | 0 | 0 | 0 | 0 | \n"))
    {
        cout<<"ERROR: wrong output"<<endl;
        assert(0);
    }

    setTestingCoutHandler();
    cout<<" MemVal mem5 = mem1+mem3: "<<'\t'<<mem5<<endl;
    setStandardCoutHandler();
    if ( getTestingCoutBuffer().compare( " MemVal mem5 = mem1+mem3:     0x7 | 0x6e | 0xcd | 0 | 0 | 0 | 0 | 0 | \n"))
    {
        cout<<"ERROR: wrong output"<<endl;
        assert(0);
    }

    //testing MemVal operator '='
    mem3 = dd;
    setTestingCoutHandler();
    cout<<" mem3 = dd: "<<'\t'<<mem3<<endl;
    setStandardCoutHandler();
    if ( getTestingCoutBuffer().compare( 
        " mem3 = dd:    0xff | 0xff | \n"))
    {
        cout<<"ERROR: operator '='"<<endl;
        assert(0);
    }

    //testing methods
    mem3.setSizeOfSegment(5);
    setTestingCoutHandler();
    cout<<" mem3.setSizeOfSegment(5): "<<'\t'<<mem3<<endl;
    setStandardCoutHandler();
    if ( getTestingCoutBuffer().compare(
        " mem3.setSizeOfSegment(5):     0xff | 0xff | 0 | 0 | 0 | \n"))
    {
        cout<<"ERROR: setSizeOfSegment( unsigned int size)"<<endl;
        assert(0);
    }

    setTestingCoutHandler();
    cout<<" mem1.getByteLine(): "<<'\t'<<mem1.getByteLine()<<endl;
    setStandardCoutHandler();
    if ( getTestingCoutBuffer().compare( 
        " mem1.getByteLine():   0x7 | 0x6e | 0xcd | \n"))
    {
        cout<<"ERROR: getByteLine()"<<endl;
        assert(0);
    }

    setTestingCoutHandler();
    cout<<" mem3.getByteLine(0,3): "<<'\t'<<mem3.getByteLine(0,3)<<endl;
    setStandardCoutHandler();
    if ( getTestingCoutBuffer().compare( 
        " mem3.getByteLine(0,3):    0xff | 0xff | 0 | \n"))
    {
        cout<<"ERROR: getByteLine()"<<endl;
        assert(0);
    }

    mem3.writeByteLine(d,3);
    setTestingCoutHandler();
    cout<<" mem1.writeByteLine(d,3): "<<'\t'<<mem3<<endl;
    setStandardCoutHandler();
    if ( getTestingCoutBuffer().compare( 
        " mem1.writeByteLine(d,3):  0xff | 0xff | 0 | 0x7 | 0x4c | \n"))
    {
        cout<<"ERROR: writeByteLine( "
            "const ByteLine& line, unsigned int index)"<<endl;
        assert(0);
    }

    mem3.writeByteLine(d);
    setTestingCoutHandler();
    cout<<" mem1.writeByteLine(d): "<<'\t'<<mem3<<endl;
    setStandardCoutHandler();
    if ( getTestingCoutBuffer().compare( 
        " mem1.writeByteLine(d):    0x7 | 0x4c | 0 | 0x7 | 0x4c | \n"))
    {
        cout<<"ERROR: writeByteLine( const ByteLine & line)"<<endl;
        assert(0);
    }

    mem3.resizeMemVal(6);
    setTestingCoutHandler();
    cout<<" mem3.resizeMemVal(6): "<<'\t'<<mem3
        <<" mem3.getSizeOfMemVal(): "<<'\t'<<mem3.getSizeOfMemVal()
        <<" mem3.getSizeOfSegment(): "<<'\t'<<mem3.getSizeOfSegment()<<endl;
    setStandardCoutHandler();
    if ( getTestingCoutBuffer().compare( 
        " mem3.resizeMemVal(6):     "
        "0x7 | 0x4c | 0 | 0x7 | 0x4c | 0 | 0 | 0 | 0 | 0 | "
        " mem3.getSizeOfMemVal():   10 mem3.getSizeOfSegment():     5\n"))
    {
        cout<<"ERROR: resizeMemVal( unsigned int size),"
            " getSizeOfMemVal(), getSizeOfSegment()"<<endl;
        assert(0);
    }
}

void testMemModel()
{
    Byte a( 7);
    Byte b( 205);
    Byte c( 110);
    ByteLine f( a + c + b);
    mathAddr aa =10;
    mathAddr bb = 6;
    MemoryModel model(1);
    model.write(bb,f);
    cout<<" model.write(bb,f): \n"<<model<<endl;
    model.write(aa,a);
    cout<<" model.write(aa,a): \n"<<model<<endl;
    model.write(9,b);
    cout<<" model.write(9,b): \n"<<model<<endl;
    cout<<" model.read(7,3): \n"<<model.read(7,3)<<endl;
    cout<<" model: \n"<<model<<endl;;
    model.write(8,f);
    cout<<" model.write(8,f): \n"<<model<<endl;
    //
    cout << "hostUInt test: \n\n" << endl;
    hostUInt8 ha = 7;
    hostUInt16 hb = 205;
    hostUInt32 hc = 110;

    MemoryModel model1( 3), model2( 3), model3( 3);
    model1.write8( aa, ha);
    cout<<" model.write(aa,ha): \n"<<model1<<endl;
    model2.write16( 9,hb);
    cout<<" model.write(9,hb): \n"<<model1<<endl;
    model3.write32( 9,hc);
    cout<<" model.write(9,hc): \n"<<model1<<endl;

    ha = model1.read8(aa);
    hb = model2.read16(9);
    hc = model3.read32(9);
    unsigned int dd = ( unsigned int) ha;
    cout<<"model1.read8(aa);"<<dd<<endl;
    cout<<"model2.read16(9);"<<hb<<endl;
    cout<<"model3.read32(9);"<<hc<<endl;

    MemVal mv = model2.read( 9, 2);
    cout << mv.getByteLine().getHostUInt16() << endl;
}

void testOperationSetDumpEncode(
    OperType type, OperCode opcode0, OperCode opcode1, OperCode opcode2,
    hostUInt8 sd, hostUInt8 am,
    hostUInt8 imm8, hostUInt16 imm10, hostUInt16 imm16,
    hostUInt8 rs1, hostUInt8 rs2, hostUInt8 rd,
    const char *expected, hostUInt32 expected_word)
{
    Operation *op = new Operation();

    setTestingCoutHandler();
    op->set( type, opcode0, opcode1, opcode2,
             sd, am, imm8, imm10, imm16, rs1, rs2, rd);
    op->dump();
    setStandardCoutHandler();
    if (getTestingCoutBuffer().compare(expected))
    {
        cout << "testOperation/Dump failed, expected: " << expected << ", got: " << getTestingCoutBuffer() << endl;
        assert(0);
    }

    hostUInt32 encoded = op->encode()->getHostUInt32();
    if (encoded != expected_word)
    {
        cout << "testOperation/Encode failed," << endl <<
            "encoded: " << hex << encoded << endl <<
            "expected: " << expected_word << dec << endl;
        assert(0);
    }

    delete op;
}

void testOperation()
{
    testOperationSetDumpEncode(   MOVE, BRR, NOP, NOP, 0, 0, 0, 0,  0, 1, 0, 2, "brr 1, r2;\n",
        0x2200000c); // 000 011 --- -- ----------- 00001 00010
    testOperationSetDumpEncode(   MOVE, BRM, NOP, NOP, 1, 0, 0, 0,  0, 1, 0, 2, "brm 1, r1, r2;\n",
        0x22002004); // 000 001 --- 01
    testOperationSetDumpEncode(   MOVE,  LD, NOP, NOP, 0, 0, 0, 0,  1, 0, 0, 2, "ld 0, r1, r2;\n",
        0x22000018); // 000 110 --- 00
    testOperationSetDumpEncode(    ALU, NOP, ADD, NOP, 0, 1, 0, 6,  0, 0, 0, 2, "add 1, 6, r2;\n",
        0xc2802020);
    testOperationSetDumpEncode(    ALU, NOP, SUB, NOP, 0, 0, 0, 0,  0, 1, 3, 2, "sub 0, r1, r3, r2;\n",
        0x62044020);
    testOperationSetDumpEncode( P_FLOW, JMP, NOP, NOP, 1, 0, 0, 0,  5, 0, 0, 0, "jmp 1, r5;\n",
        0x050080a0);
    testOperationSetDumpEncode( P_FLOW, JGT, NOP, NOP, 1, 0, 0, 0, 10, 0, 0, 0, "jgt 1, r10;\n",
        0x0a0080a2);
    testOperationSetDumpEncode( P_FLOW, JMP, NOP, NOP, 0, 0, 0, 0,  0, 0, 0, 2, "jmp 0, r2;\n",
        0x020000a0);
    testOperationSetDumpEncode( P_FLOW, JGT, NOP, NOP, 0, 0, 0, 0,  0, 0, 0, 5, "jgt 0, r5;\n",
        0x050000a2);
    testOperationSetDumpEncode( SYS, HLT, NOP, NOP, 0, 0, 0, 0,  0, 0, 0, 0, "hlt;\n",
        0x000000C0);
    testOperationSetDumpEncode( SYS, INT, NOP, NOP, 0, 0, 16, 0,  0, 0, 0, 0, "int 0x10;\n",
        0x100000C2);

}

void testRegisterFileModel()
{
    RegisterFileModel* rfm = new RegisterFileModel( 2, 1);
    RegVal* rv = new RegVal( 1);
    RegVal rv1( 1);
    Byte* b1 = new Byte( 5);
    Byte* b2 = new Byte( 2);
    rv->setByte( 0, *b1);
    rv1.setByte( 0, *b2);
    rfm->writeReg( 1, *rv);
    rfm->writeReg( 0, rv1);

    //Testing read reg
    setTestingCoutHandler();
    cout << ( int)rfm->readReg( 0)->getByte( 0).getByteVal() << " " <<
            ( int)rfm->readReg( 1)->getByte( 0).getByteVal() << "\n";
    setStandardCoutHandler();
    if ( getTestingCoutBuffer().compare( 
        "2 5\n"))
    {
        cout<<"ERROR: readReg()"<<endl;
        assert(0);
    }

    delete b1;
    delete b2;
    delete rv;
    delete rfm;
    
    //Testing write/read8,16,32
    RegisterFileModel* rfm1 = new RegisterFileModel( 2, 1);
    RegisterFileModel* rfm2 = new RegisterFileModel( 2, 2);
    RegisterFileModel* rfm3 = new RegisterFileModel( 2, 4);
    hostUInt8 ha = 8, haa = 88;
    hostUInt16 hb = 1666, hbb = 6111;
    hostUInt32 hc = 32222, hcc = 23333;
    rfm1->write8( 1, ha);
    rfm1->write8( 0, haa);
    rfm2->write16( 1, hb);
    rfm2->write16( 0, hbb);
    rfm3->write32( 1, hc);
    rfm3->write32( 0, hcc);

    //testing read8
    setTestingCoutHandler();
    cout << ( int)rfm1->read8( 1) << " " <<
            ( int)rfm1->read8( 0) << "\n";
    setStandardCoutHandler();
    if ( getTestingCoutBuffer().compare( 
        "8 88\n"))
    {
        cout<<"ERROR: read8()"<<endl;
        assert(0);
    }

    //testing read16
    setTestingCoutHandler();
    cout << ( int)rfm2->read16( 1) << " " <<
            ( int)rfm2->read16( 0) << "\n";
    setStandardCoutHandler();
    if ( getTestingCoutBuffer().compare( 
        "1666 6111\n"))
    {
        cout<<"ERROR: read16()"<<endl;
        assert(0);
    }

    //testing read32
    setTestingCoutHandler();
    cout << ( int)rfm3->read32( 1) << " " <<
            ( int)rfm3->read32( 0) << "\n";
    setStandardCoutHandler();
    if ( getTestingCoutBuffer().compare( 
        "32222 23333\n"))
    {
        cout<<"ERROR: read32()"<<endl;
        assert(0);
    }

}


int main()
{
    testByte();
    testByteLine();
    //testMemVal();
    //testMemModel();
    testOperation();
    testRegisterFileModel();
    return 0;
}

