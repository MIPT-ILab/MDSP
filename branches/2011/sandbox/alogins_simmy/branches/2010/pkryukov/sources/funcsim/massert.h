#include <cstdlib>

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
#define mdspAssert(expr,error_num)\
{\
    if(expr);\
    else{\
    mdassert(#expr,__LINE__,__FILE__,error_num);\
    }\
}
void mdassert(const char *s,int line,const char *f,int err){
    if(err!=0){
        switch(err)
            {
                case ERROR_NO_TYPE: std::cerr <<"ERROR: NO_TYPE Operation type\n";
                break;
                case ERROR_UNKNOWN_OPERATION: std::cerr <<"ERROR: Unknown operation code\n";
                break;
                case ERROR_ZERO_LINE: std::cerr <<"ERROR: Size of the line can not be equal to 0 bytes!\n";
                break;
                case ERROR_ALLOC_MEMORY: std::cerr<<"ERROR: Can not allocate memory!\n";
                break;
                case ERROR_LESS_LINE: std::cerr <<"ERROR: Size of byte line is less than target byte number!\n";
                break;
                case ERROR_BAD_TYPE: std::cerr <<"ERROR: Invalid type\n";
                break;
                case ERROR_BAD_OPERATION: std::cerr <<"ERROR : Invalid operation type\n";
                break;
                case ERROR_MEM_VAL: std::cerr <<"ERROR: Size of MemVal must be 4 bytes\n";
                break;
                case ERROR_PRINT_BAD_TYPE: std::cerr <<"ERROR: Can't print to console, because operation has illegal type\n";
                break;
                case  ERROR_EMPTY_BYTE_LINE: std::cerr <<"ERROR: Byte line is empty!\n";
            break;
                case  ERROR_REGISTER_BAD_NUMBER: std::cerr <<"ERROR: Number of register is out of range!\n";
                break;
                case  ERROR_REG_VAL_BAD_LENGHT: std::cerr <<"ERROR: You can write to RegVal with the equal length only!\n";
                break;
                case  ERROR_FR_BAD_TYPE: std::cerr <<"ERROR: Invalid flag register type\n";
                break;
                case  ERROR_LESS_MEM_VAL: std::cerr <<"ERROR: Size of MemVal is less than target byte number!\n";
                break;
                case ERROR_BAD_OPERATION_CODE: std::cerr <<"ERROR: Operation code is invalid\n";
                break;
            }
    }
    std::cerr << "mdspAssert:ERROR in line " <<line ; 
        std::cerr << " in file " << f << " by expression "<< s<<"\n";
    system("PAUSE");        
    exit(1);
}
