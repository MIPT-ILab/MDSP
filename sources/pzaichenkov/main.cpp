/**
* main.cpp - Entry point of functional simulator (funcsim)
* Copyright 2009 MDSP team
*/

#include "operation.h"

int main()
{
    Operation *op1 = new Operation();
    /* Correct Operations */
    cout << "Correct operations: " << endl;
    op1->set(MOVE, BRR, NOP, NOP, 0, 0, 0, 0, 1, 0, 2);
    op1->dump();
    op1->set(MOVE, BRM, NOP, NOP, 1, 0, 0, 0, 1, 0, 2);
    op1->dump();
    op1->set(MOVE, LD, NOP, NOP, 0, 0, 0, 1, 0, 0, 2);
    op1->dump();
    op1->set(ALU, NOP, ADD, NOP, 0, 1, 0, 0, 1, 3, 2);
    op1->dump();
    op1->set(ALU, NOP, SUB, NOP, 0, 0, 0, 0, 1, 3, 2);
    op1->dump();
    op1->set(P_FLOW, JMP, NOP, NOP, 1, 0, 0, 5, 0, 0, 0);
    op1->dump();
    op1->set(P_FLOW, JGT, NOP, NOP, 1, 0, 0, 10, 0, 0, 0);
    op1->dump();
    op1->set(P_FLOW, JMP, NOP, NOP, 0, 0, 0, 0, 0, 0, 2);
    op1->dump();
    op1->set(P_FLOW, JGT, NOP, NOP, 0, 0, 0, 0, 0, 0, 2);
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
    return 0;
}