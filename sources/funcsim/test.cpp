/**
 * test.cpp - Unit tests
 * @author Dmitry Ustyugov, Pavel Zaichenkov
 * Copyright 2009 MDSP team
 */

#include "memory.h"
#include "operation.h"
#include "register_file.h"
#include "cout_wrapper.h"

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
    if ( getTestingCoutBuffer() != string( "a:outputFormat 1\n"))
    {
    	cout<<"ERROR: wrong output format"<<endl;
    	assert(0);
    }

    //testing output format for b
    setTestingCoutHandler();
    cout<<"b:outputFormat "<<b.getOutputFormat()<<endl;
    setStandardCoutHandler();
    if ( getTestingCoutBuffer() != string( "b:outputFormat 0\n"))
    {
    	cout<<"ERROR: wrong output format"<<endl;
    	assert(0);
    }

    //testing output format for c
    setTestingCoutHandler();
    cout<<"c:outputFormat "<<c.getOutputFormat()<<endl;
    setStandardCoutHandler();
    if ( getTestingCoutBuffer() != string( "c:outputFormat 2\n"))
    {
    	cout<<"ERROR: wrong output format"<<endl;
    	assert(0);
    }

    //testing byte value for a
    setTestingCoutHandler();
    cout<<"a: "<<a<<endl;
    setStandardCoutHandler();
    if ( getTestingCoutBuffer() != string( "a: 7\n"))
    {
    	cout<<"ERROR: wrong byte value"<<endl;
    	assert(0);
    }

    //testing byte value for b
    setTestingCoutHandler();
    cout<<"b: "<<b<<endl;
    setStandardCoutHandler();
    if ( getTestingCoutBuffer() != string( "b: 00000111\n"))
    {
    	cout<<"ERROR: wrong byte value"<<endl;
    	assert(0);
    }

    //testing bitwise addition
    setTestingCoutHandler();
    cout<<"c=a&b: "<<c<<endl;
    setStandardCoutHandler();
    if ( getTestingCoutBuffer() != string( "c=a&b: 0x7\n"))
    {
    	cout<<"ERROR: bitwise addition"<<endl;
    	assert(0);
    }
    
    //testing shifting to the left
    setTestingCoutHandler();
    cout<<"c>>2: "<< ( c>>2) <<endl;
    setStandardCoutHandler();
    if ( getTestingCoutBuffer() != string( "c>>2: 0x1\n"))
    {
    	cout<<"ERROR: shifting to the left"<<endl;
    	assert(0);
    }

    //testing shifting to the right
    setTestingCoutHandler();
    cout<<"b<<2: "<< ( b<<2) <<endl;
    setStandardCoutHandler();
    if ( getTestingCoutBuffer() != string( "b<<2: 0x1c\n"))
    {
    	cout<<"ERROR: shifting to the right"<<endl;
    	assert(0);
    }

    //testing equal comparing
    setTestingCoutHandler();
    cout<<"c==a: "<<( c == a)<<endl;
    setStandardCoutHandler();
    if ( getTestingCoutBuffer() != string( "c==a: 1\n"))
    {
    	cout<<"ERROR: equal comparing"<<endl;
    	assert(0);
    }

    //testing not equal comparing
    setTestingCoutHandler();
    cout<<"c!=b: "<<( c != b)<<endl;
    setStandardCoutHandler();
    if ( getTestingCoutBuffer() != string( "c!=b: 0\n"))
    {
    	cout<<"ERROR: not equal comparing"<<endl;
    	assert(0);
    }

    cout<<"test byte class: ok"<<endl;
}
void testByteLine()
{
    Byte a( 7);
    Byte b( 205);
    Byte c( 110);
    hostUInt8 q;
    hostUInt16 w;
    hostUInt32 e;
    q=044;//oct
    w=0x34c6;
    e=45678;
    cout<<"test byteline class:"<<endl;
    cout<<"a: "<<'\t'<<a<<endl;
    cout<<"b: "<<'\t'<<b<<endl;
    cout<<"c: "<<'\t'<<c<<endl;
    ByteLine f( a + c + b);
    ByteLine d = f;
    ByteLine r( q, LOW_FIRST);
    ByteLine t( w, LOW_FIRST);
    
    ByteLine y( e, LOW_FIRST);
    ByteLine u( q, HIGH_FIRST);
    ByteLine i( w, HIGH_FIRST);
    ByteLine o( e, HIGH_FIRST);
    r.setBinOut();
    t.setBinOut();
    y.setBinOut();
    u.setBinOut();
    i.setBinOut();
    o.setBinOut();
    cout<<"q :"<<q<<endl;
    cout<<"w :"<<w<<endl;
    cout<<"e :"<<e<<endl;
    cout<<"r :"<<r<<endl;
    cout<<"t :"<<t<<endl;
    cout<<"y :"<<y<<endl;
    cout<<"u :"<<u<<endl;
    cout<<"i :"<<i<<endl;
    cout<<"o :"<<o<<endl;
    q = u.getHostUInt8();
    w = i.getHostUInt16();
    e = o.getHostUInt32();
    int m = 0;
    m += q;
    cout<<"q -ret:"<< oct <<m<<endl;
    cout<<"w -ret:"<<dec<<w<<endl;
    cout<<"e -ret:"<<dec<<e<<endl;


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
    MemVal mem5 = mem1+mem4;
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

void testOperationSetDump(
    OperType type, OperCode opcode0, OperCode opcode1, OperCode opcode2,
    hostUInt8 sd, hostUInt8 am,
    hostUInt16 imm10, hostUInt16 imm16,
    hostUInt8 rs1, hostUInt8 rs2, hostUInt8 rd,
    const char *expected)
{
    Operation *op = new Operation();

    setTestingCoutHandler();
    op->set( type, opcode0, opcode1, opcode2,
             sd, am, imm10, imm16, rs1, rs2, rd);
    op->dump();
    setStandardCoutHandler();
    if (getTestingCoutBuffer() != string(expected))
    {
        cout <<
            "testOperationSetDump failed, expected: " << expected <<
            ", got: " << getTestingCoutBuffer() << endl;
        assert(0);
    }

    delete op;
}

void testOperation()
{
    testOperationSetDump(   MOVE, BRR, NOP, NOP, 0, 0, 0,  0, 1, 0, 2, "brr 1, r2;\n");
    testOperationSetDump(   MOVE, BRM, NOP, NOP, 1, 0, 0,  0, 1, 0, 2, "brm 1, r1, r2;\n");
    testOperationSetDump(   MOVE,  LD, NOP, NOP, 0, 0, 0,  1, 0, 0, 2, "ld 0, r1, r2;\n");
    testOperationSetDump(    ALU, NOP, ADD, NOP, 0, 1, 6,  0, 0, 0, 2, "add 1, 6, r2;\n");
    testOperationSetDump(    ALU, NOP, SUB, NOP, 0, 0, 0,  0, 1, 3, 2, "sub 0, r1, r3, r2;\n");
    testOperationSetDump( P_FLOW, JMP, NOP, NOP, 1, 0, 0,  5, 0, 0, 0, "jmp 1, r5;\n");
    testOperationSetDump( P_FLOW, JGT, NOP, NOP, 1, 0, 0, 10, 0, 0, 0, "jmp 1,  r10;\n");
    testOperationSetDump( P_FLOW, JMP, NOP, NOP, 0, 0, 0,  0, 0, 0, 2, "jmp 0, r2;\n");
    testOperationSetDump( P_FLOW, JGT, NOP, NOP, 0, 0, 0,  0, 0, 0, 5, "jmp 0, r5;\n");
    testOperationSetDump( P_FLOW, JGT, NOP, NOP, 0, 0, 0,  0, 0, 0, 5, "jmp 0, r5;\n");
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

    cout << ( int)rfm->readReg( 0)->getByte( 0).getByteVal() << " " <<
            ( int)rfm->readReg( 1)->getByte( 0).getByteVal() << "\n";
    delete b1;
    delete b2;
    delete rv;
    delete rfm;
    
    //
    cout << "Testing write/read8,16,32" << endl;
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
    
    cout << ( int)rfm1->read8( 1) << " " <<
            ( int)rfm1->read8( 0) << "\n";
    cout << ( int)rfm2->read16( 1) << " " <<
            ( int)rfm2->read16( 0) << "\n";
    cout << ( int)rfm3->read32( 1) << " " <<
            ( int)rfm3->read32( 0) << "\n";
}

int main()
{
	//testByte();
	//testByteLine();
	//testMemVal();
	//testMemModel();
    testOperation();
    //testRegisterFileModel();

    return 0;
}

