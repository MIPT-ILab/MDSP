#include <cstdlib>
#include <cstdio>
#define mdspAssert(expr)\
{\
if(expr); else\
    {\
    cout << "\nmdspAssert:ERROR in line " <<__LINE__\
    << " in file " <<__FILE__<< " by expression "<< __STRING(expr) <<endl;\
    abort(); \
    }\
}
