/**
 * main.cpp
 * @author Orlov Vasiliy
 * Copyright 2011 MDSP team
 */

#include <iostream>
#include "Simmy.h"

int main()
{
    hostUInt32 c;
    hostUInt8 a[55] = {132, 12, 1, 5, 0,   130, 12, 1, 3, 0,   132, 4, 2, 4, 0,   128, 0, 1, 2, 0,   132, 0, 0, 1, 0,
                       195,  0, 1, 0, 0,   194,  2, 1, 0, 0,   193, 0, 2, 0, 0,   192, 0, 0, 0, 0,    68, 0, 2, 0, 0,
                         1,  0, 0, 1, 0      };
    Simmy b(a, 1);
    cout << b.execute(11);
    cin >> c;
    
    return 0;
}
