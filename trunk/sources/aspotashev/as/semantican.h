
#ifndef __SEMANTICAN_H__
#define __SEMANTICAN_H__


#include <vector>

#include "tokenan.h"

enum UNIT_TYPE
{
    UNIT_LABEL = 1,
    UNIT_OPERATION
};

enum OPERAND_TYPE
{
    OPERAND_GPR = 1,
    OPERAND_CONST_INT,
    OPERAND_CUSTOM_ID,
};

class SemanticAn
{
public:
    struct Operand
    {
        OPERAND_TYPE type;
        bool indirect;
        std::string sVal;
        int iVal;

        Operand();
        static Operand *createId( std::string id_string);
        static Operand *createIdInd( std::string id_string);
        static Operand *createConstInt( int iVal);
        void dump();

        bool isIndirectGpr();
        bool isDirectGpr();
        bool isConstInt();
    };

    struct Unit
    {
        UNIT_TYPE type;

        std::string sVal;
        std::vector<Operand *> operands;

        static Unit *createOperation(
            std::string opcode, std::vector<Operand *> operands);
        static Unit *createLabel( std::string id);
        void dump();
    };

public:
    SemanticAn( std::vector<TokenAn::Token *> tokens);
    std::vector<Unit *> run();

private:
    bool isOpcode( std::string s); // arch
    std::vector<Operand *> parseOperandList();
    Operand *parseOperand();

private:
    std::vector<TokenAn::Token *> tokens;
    std::vector<TokenAn::Token *>::iterator tok;
};

#endif

