/**
* main.cpp - Entry point of functional simulator (funcsim)
* Copyright 2009 MDSP team
*/

#include "operation.h"

int main()
{
    Byte a( 31);
    Byte b( 63);
    Byte c( 0);
    cout<<"test byteline class:"<<endl; 
    cout<<"a: "<<'\t'<<a<<endl;
    cout<<"b: "<<'\t'<<b<<endl;
    cout<<"c: "<<'\t'<<c<<endl;

    ByteLine f( a + b + c);
    ByteLine byteline = f;
    cout<<(byteline[0].getByteVal()+byteline[1].getByteVal()*256+byteline[2].getByteVal()*65536)<<endl;
    cout<<"byteline: "<<'\t'<<byteline<<endl;
    byteline = byteline << 10;
    cout<<(byteline[0].getByteVal()+byteline[1].getByteVal()*256+byteline[2].getByteVal()*65536)<<endl;
    cout<<"byteline: "<<'\t'<<byteline<<endl;
    return 0;
}

