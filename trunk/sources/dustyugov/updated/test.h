/**
 * test.h - Header of set of testing function
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
    Byte b( 205);
    Byte c = a&b;
    a.setBinOut();
    b.setDecOut();
    c.setHexOut();
    cout<<"test byte class:"<<endl;
    cout<<"a:outputVal "<<a.getOutputVal()<<endl;
    cout<<"a: "<<'\t'<<a<<endl;
    cout<<"b:outputVal "<<b.getOutputVal()<<endl;
    cout<<"b: "<<'\t'<<b<<endl;
    cout<<"c:outputVal "<<c.getOutputVal()<<endl;
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
    op1->set(ALU, ADD, NOP, NOP, 0, 1, 0, 0, 1, 3, 2);
    op1->dump();
    op1->decode(op1->encode());
    cout << "Decode / encode output: ";
    op1->dump();
    op1->set(ALU, SUB, NOP, NOP, 0, 0, 0, 0, 1, 3, 2);
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
    cout << endl << "Incorrect operations: " << endl;
    op1->set(MOVE, BRR, NOP, NOP, 1, 1, 1, 1, 1, 1, 5);
    op1->dump();
    op1->set(MOVE, BRM, NOP, NOP, 1, 1, 1, 1, 1, 1, 2);
    op1->dump();
    op1->set(P_FLOW, JMP, NOP, NOP, 1, 0, 0, 0, 0, 0, 5);
    op1->dump();
    op1->set(P_FLOW, JMP, NOP, NOP, 0, 0, 0, 0, 1, 1, 2);
    op1->dump();
    cout << endl << "Big bada boom X_X ..." << endl;
    op1->set(MOVE, NOP, NOP, NOP, 0, 0, 0, 0, 1, 1, 2);
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
}

void test()
{
	testByte();
	testByteLine();
	testMemVal();
	testMemModel();
    testOperation();
    testRegisterFileModel();
}

#endif /* TEST_H */
