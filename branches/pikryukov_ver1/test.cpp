#include <iostream>
#include <string>

#include "source/simmy.h"

class Test
{
private:
    const unsigned char * const _program;
    const size_t _program_s;
    const int _result;
public:
    Test( const unsigned char * program, size_t program_s, int result);
    bool run( bool printResult);
};

Test::Test( const unsigned char * program, size_t program_s, int result) : 
    _program( program),
    _program_s( program_s),
    _result( result) {}
    
bool Test::run( bool printResult)
{
    Simmy::Simmy* simulator = new Simmy::Simmy( _program);
    int result = simulator->execute( _program_s);
    delete simulator;
    if( result != this->_result)
    {
        if ( printResult)
        {
            std::cout << "Result is " << result <<
                ", expected " << _result << std::endl;
        }
        return false;
    }
    std::cout << "Test passed" << std::endl;
    return true;
}

int main() {
    const unsigned char listing[] =
        {
         0x84, 0x0C, 0x00, 0x0A, 0x00, // 1: mov r1 1x000A
         0x84, 0x0C, 0x00, 0x0A, 0x00, // 2: mov r0 1x000A
         0x44, 0x00, 0x02, 0x00, 0x00, // 3: not r2
         0x84, 0x08, 0x00, 0x02, 0x00, // 4: mov r0 r2
         0x01, 0x08, 0x01, 0x02, 0x00, // 5: and r1 r2
         0x84, 0x08, 0x00, 0x01, 0x00, // 6: mov r0 r1
         0x02, 0x08, 0x01, 0x02, 0x00, // 7: or  r1 r2
         0x84, 0x08, 0x00, 0x01, 0x00, // 8: mov r0 r1
         0x03, 0x08, 0x01, 0x01, 0x00, // 9: xor r1 r1
         0x84, 0x08, 0x00, 0x01, 0x00, // 10: mov r0 r1
         0x82, 0x0C, 0x01, 0x10, 0x00, // 11: add r1 1x0010
         0x84, 0x08, 0x00, 0x01, 0x00, // 12: mov r0 r1
         0x82, 0x08, 0x01, 0x01, 0x00, // 13: add r1 r1
         0x84, 0x08, 0x00, 0x01, 0x00, // 14: mov r0 r1
         0x83, 0x0C, 0x03, 0x00, 0xff, // 15: sub r3 1x00FF
         0x84, 0x08, 0x00, 0x03, 0x00, // 16: mov r0 r3
         0x84, 0x0C, 0x0F, 0x0A, 0x00, // 17: mov r15 1x000A
         0x81, 0x0C, 0x0F, 0x10, 0x00, // 18: mul r15 1x0010
         0x84, 0x08, 0x00, 0x0F, 0x00, // 19: mov r0 r15
         0x80, 0x08, 0x0F, 0x01, 0x00, // 20: div r15 r1
         0x84, 0x08, 0x00, 0x0F, 0x00, // 21: mov r0 r15
         0xC1, 0x00, 0x0A, 0x00, 0x00, // 22: inc r10         
         0x84, 0x08, 0x00, 0x0A, 0x00, // 23: mov r0 r10
         0xC0, 0x00, 0x0B, 0x00, 0x00, // 24: dec r11         
         0x84, 0x08, 0x00, 0x0B, 0x00, // 25: mov r0 r11
         0xC2, 0x0C, 0x0A, 0x00, 0x00, // 26: ssgn 1, r10         
         0x84, 0x08, 0x00, 0x0A, 0x00, // 27: mov r0 r10
         0xC3, 0x00, 0x0B, 0x00, 0x00, // 28: isgn r11         
         0x84, 0x08, 0x00, 0x0B, 0x00, // 29: mov r0 r11
         0xC2, 0x00, 0x0A, 0x00, 0x00, // 30: ssgn 0, r10         
         0x84, 0x08, 0x00, 0x0A, 0x00, // 31: mov r0 r10
        };
        
    struct Program
    {
        size_t amount;
        int result;
        std::string name;
    } programs[] =
        {
            {2 , 0x000A, "mov"},
            {4 , 0xFFFF, "not"},
            {6 , 0,      "and"},
            {8 , 0xFFFF, "or "},
            {10, 0,      "xor"},
            {12, 0x10,   "add const"},
            {14, 0x20,   "add reg"},
            {16, -0xFF00,"sub"},
            {19, 0x00A0, "mul"},
            {21, 5,    "div"},
            {23, 1,    "inc"},
            {25, -1,   "dec"},
            {27, 1,    "ssgn 1"},
            {29, 1,    "isgn"},
            {31, -1,    "ssgn 0"}
        };
            
    const unsigned size = 15;

    for (unsigned i = 0; i < size; ++i)
    {
        std::cout << "Testing \"" << programs[i].name << "\"" << std::endl;
        Test test(listing, programs[i].amount, programs[i].result);
        if (!test.run(true))
        {
            return 1;
        }
        std::cout << std::endl;
    }
    
    std::cout << "ALL TESTS PASSED" << std::endl;
    return 0;
}
        

    