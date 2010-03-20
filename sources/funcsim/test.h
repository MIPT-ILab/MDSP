/**
 * test.h - Header of set of testing function
 * @author Dmitry Ustyugov
 * Copyright 2009 MDSP team
 */

#ifndef TEST_H
#define TEST_H
#include "memory.h"
#include "operation.h"
#include "register_file.h"

void testByte()
{
    Byte a( 7);
    Byte b( 7);
    Byte c = a&b;
    b.setBinOut();
    a.setDecOut();
    c.setHexOut();
    cout<<"test byte class:"<<endl;
    cout<<"a:outputFormat "<<a.getOutputFormat()<<endl;
    cout<<"a: "<<'\t'<<a<<endl;
    cout<<"b:outputFormat "<<b.getOutputFormat()<<endl;
    cout<<"b: "<<'\t'<<b<<endl;
    cout<<"c:outputFormat "<<c.getOutputFormat()<<endl;
    cout<<"c=a&b: "<<'\t'<<c<<endl;
    cout<<"c>>2: "<<'\t'<< ( c>>2) <<endl;
    cout<<"b<<2: "<<'\t'<<( b<<2)<<endl;
    cout<<"c==a: "<<'\t'<<( c == a)<<endl;
    cout<<"c!=b: "<<'\t'<<( c != b)<<endl;
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

void testOperation()
{
    Operation *op1 = new Operation();
    /* Correct Operations */
    cout << "Correct operations: " << endl;
    op1->set(MOVE, BRR, NOP, NOP, 0, 0, 0, 0, 1, 0, 2);
    op1->dump();
    op1->decode(op1->encode());
    cout << "Decode / encode output: ";
    op1->dump();
    op1->set(MOVE, BRM, NOP, NOP, 1, 0, 0, 0, 1, 0, 2);
    op1->dump();
    op1->decode(op1->encode());
    cout << "Decode / encode output: ";
    op1->dump();
    op1->set(MOVE, LD, NOP, NOP, 0, 0, 0, 1, 0, 0, 2);
    op1->dump();
    op1->decode(op1->encode());
    cout << "Decode / encode output: ";
    op1->dump();
    op1->set(ALU, NOP, ADD, NOP, 0, 1, 6, 0, 0, 0, 2);
    op1->dump();
    op1->decode(op1->encode());
    cout << "Decode / encode output: ";
    op1->dump();
    op1->set(ALU, NOP, SUB, NOP, 0, 0, 0, 0, 1, 3, 2);
    op1->dump();
    op1->decode(op1->encode());
    cout << "Decode / encode output: ";
    op1->dump();
    op1->set(P_FLOW, JMP, NOP, NOP, 1, 0, 0, 5, 0, 0, 0);
    op1->dump();
    op1->decode(op1->encode());
    cout << "Decode / encode output: ";
    op1->dump();
    op1->set(P_FLOW, JGT, NOP, NOP, 1, 0, 0, 10, 0, 0, 0);
    op1->dump();
    op1->decode(op1->encode());
    cout << "Decode / encode output: ";
    op1->dump();
    op1->set(P_FLOW, JMP, NOP, NOP, 0, 0, 0, 0, 0, 0, 2);
    op1->dump();
    op1->decode(op1->encode());
    cout << "Decode / encode output: ";
    op1->dump();
    op1->set(P_FLOW, JGT, NOP, NOP, 0, 0, 0, 0, 0, 0, 5);
    op1->dump();
    op1->decode(op1->encode());
    cout << "Decode / encode output: ";
    op1->dump();
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

void test()
{
	//testByte();
	//testByteLine();
	//testMemVal();
	testMemModel();
    //testOperation();
    testRegisterFileModel();
}

#endif /* TEST_H */
