#include <cstdlib>
#include <cstdio>
enum ERRORS {
ERROR_NO_TYPE =100,
ERROR_UNKNOWN_OPERATION,
ERROR_ZERO_LINE,
ERROR_ALLOC_MEMORY,
ERROR_LESS_LINE,
ERROR_BAD_TYPE,
ERROR_BAD_OPERATION,
ERROR_MEM_VAL,
ERROR_PRINT_BAD_TYPE,
ERROR_EMPTY_BYTE_LINE,
ERROR_REGISTER_BAD_NUMBER,
ERROR_REG_VAL_BAD_LENGHT,
ERROR_FR_BAD_TYPE,
ERROR_LESS_MEM_VAL,
ERROR_BAD_OPERATION_CODE
};
#define mdspAssert(expr)\
{int i=(int)expr;\
switch(expr)\
    {\
    case ERROR_NO_TYPE: cout <<"ERROR: NO_TYPE Operation type\n";\
    i=0;\
    break;\
    case ERROR_UNKNOWN_OPERATION: cout <<"ERROR: Unknown operation code\n";\
    i=0;\
    break;\
    case ERROR_ZERO_LINE: cout <<"ERROR: Size of the line can not be equal to 0 bytes!\n";\
    i=0;\
    break;\
    case ERROR_ALLOC_MEMORY:cout<<"ERROR: Can not allocate memory!\n";\
    i=0;\
    break;\
    case ERROR_LESS_LINE: cout <<"ERROR: Size of byte line is less than target byte number!\n";\
    i=0;\
    break;\
    case ERROR_BAD_TYPE: cout <<"ERROR: Invalid type\n";\
    i=0;\
    break;\
    case ERROR_BAD_OPERATION: cout <<"ERROR : Invalid operation type\n";\
    i=0;\
    break;\
    case ERROR_MEM_VAL: cout <<"ERROR: Size of MemVal must be 4 bytes\n";\
    i=0;\
    break;\
    case ERROR_PRINT_BAD_TYPE: cout <<"ERROR: Can't print to console, because operation has illegal type\n";\
    i=0;\
    break;\
    case  ERROR_EMPTY_BYTE_LINE: cout <<"ERROR: Byte line is empty!\n";\
    i=0;\
    break;\
    case  ERROR_REGISTER_BAD_NUMBER: cout <<"ERROR: Number of register is out of range!\n";\
    i=0;\
    break;\
    case  ERROR_REG_VAL_BAD_LENGHT: cout <<"ERROR: You can write to RegVal with the equal length only!\n";\
    i=0;\
    break;\
    case  ERROR_FR_BAD_TYPE: cout <<"ERROR: Invalid flag register type\n";\
    i=0;\
    break;\
    case  ERROR_LESS_MEM_VAL: cout <<"ERROR: Size of MemVal is less than target byte number!\n";\
    i=0;\
    break;\
    case  ERROR_BAD_OPERATION_CODE: cout <<"ERROR: Operation code is invalid\n";\
    i=0;\
    break;\
    }\
if(i);\
else\
    {\
    cout << "mdspAssert:ERROR in line " <<__LINE__\
    << " in file " <<__FILE__<< " by expression "<< __STRING(expr) <<endl;\
    abort(); \
    }\
}
