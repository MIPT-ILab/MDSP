#include "operation.h"

int main()
{
    Operation *op1 = new Operation();
    op1->set( MOVE, BRR, 0, 12, 30);
    op1->dump();

    return 0;
}

