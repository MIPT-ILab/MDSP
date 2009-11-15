
#include <iostream>
#include <assert.h>

#include "semantican.h"


SemanticAn::SemanticAn( std::vector<Token *> tokens)
{
    this->tokens = tokens;
}

std::vector<SemanticUnit *> SemanticAn::run()
{
    std::vector<SemanticUnit *> res;

    for ( tok = tokens.begin(); tok != tokens.end(); )
    {
        if ( tok[0]->type() == TOKEN_EOS)
        {
            tok ++;
        }
        else if ( tok[0]->type() == TOKEN_ID &&
                  tok[1]->type() == TOKEN_COLON) // label
        {
            res.push_back( SemanticUnit::createLabel( tok[0]->str()));
            tok += 2;
        }
        else if ( tok[0]->type() == TOKEN_ID && isOpcode( tok[0]->str()))
        {
            std::string opcode = tok[0]->str();
            tok ++;

            std::vector<Operand *> operands = parseOperandList();
            res.push_back( SemanticUnit::createOperation( opcode, operands));
        }
        else
        {
            std::cerr << "token type = " << tok[0]->type() << std::endl;
            throw;
        }
    }

    return res;
}

bool SemanticAn::isOpcode( std::string s)
{
    return s == "brm" || s == "brr" || s == "ld" ||
           s == "nop" || s == "add" || s == "sub" ||
           s == "jmp" || s == "jgt";
}

std::vector<Operand *> SemanticAn::parseOperandList()
{
    std::vector<Operand *> res;
    
    while ( tok[0]->type() != TOKEN_EOS)
    {
        res.push_back( parseOperand());

        if ( tok[0]->type() == TOKEN_COMMA)
        {
            tok ++;
        }
        else if ( tok[0]->type() != TOKEN_EOS)
        {
            std::cerr << "token type = " << tok[0]->type() << std::endl;
            throw;
        }
    }

    return res;
}

Operand *SemanticAn::parseOperand()
{
    Operand *res = NULL;

    if ( tok[0]->type() == TOKEN_ID)
    {
        res = Operand::createId( tok[0]->str());
        tok ++;
    }
    else if ( tok[0]->type() == TOKEN_LBRACKET &&
              tok[1]->type() == TOKEN_ID &&
              tok[2]->type() == TOKEN_RBRACKET)
    {
        res = Operand::createIdInd( tok[1]->str()); // indirect via id
        tok += 3;
    }
    else if ( tok[0]->type() == TOKEN_CONST_INT)
    {
        res = Operand::createConstInt( tok[0]->integer());
        tok ++;
    }
    else
    {
        std::cerr << "token type = " << tok[0]->type() << std::endl;
        throw;
    }

    return res;
}

Operand *Operand::createId( std::string id_string)
{
    Operand *res = new Operand;
    if ( id_string[0] == '%')
    {
        res->type = OPERAND_GPR;
        res->sVal = id_string;
    }
    else
    {
        res->type = OPERAND_CUSTOM_ID;
        res->sVal = id_string;
    }

    return res;
}

Operand *Operand::createIdInd(
    std::string id_string)
{
    Operand *res = createId( id_string);
    res->indirect = true;

    return res;
}

Operand *Operand::createConstInt( int iVal)
{
    Operand *res = new Operand;
    res->type = OPERAND_CONST_INT;
    res->iVal = iVal;

    return res;
}

Operand::Operand()
{
    indirect = false;
}

bool Operand::isIndirectGpr() const
{
    return indirect && type == OPERAND_GPR;
}

bool Operand::isDirectGpr() const
{
    return !indirect && type == OPERAND_GPR;
}

bool Operand::isConstInt() const
{
    return type == OPERAND_CONST_INT;
}

SemanticUnit *SemanticUnit::createOperation(
    std::string opcode, std::vector<Operand *> operands)
{
    SemanticUnit *res = new SemanticUnit;
    res->unitType = UNIT_OPERATION;
    res->sVal = opcode;
    res->operands = operands;

    return res;
}

SemanticUnit *SemanticUnit::createLabel( std::string id)
{
    SemanticUnit *res = new SemanticUnit;
    res->unitType = UNIT_LABEL;
    res->sVal = id;

    return res;
}

UNIT_TYPE SemanticUnit::type()
{
    return unitType;
}

std::string SemanticUnit::str() const
{
    assert(unitType == UNIT_LABEL || unitType == UNIT_OPERATION);

    return sVal;
}

bool SemanticUnit::operator== ( const std::string &str)
{
    assert(unitType == UNIT_LABEL || unitType == UNIT_OPERATION);

    return sVal == str;
}

int SemanticUnit::nOperands()
{
    assert(unitType == UNIT_OPERATION);

    return (int)operands.size();
}

const Operand *SemanticUnit::operator[] ( int index)
{
    assert(unitType == UNIT_OPERATION);
    assert(index >= 0 && index < nOperands());

    return operands[index];
}

void SemanticUnit::dump()
{
    switch ( unitType)
    {
    case UNIT_LABEL:
        std::cout << "(label) " << sVal << ":";
        break;

    case UNIT_OPERATION:
        std::cout << "(op   ) " << sVal << " ";
        for ( int i = 0; i < (int)operands.size(); i ++)
        {
            if ( i > 0)
            {
                std::cout << ", ";
            }

            operands[i]->dump();
        }
        break;

    default: throw;
    }
}

std::string Operand::str() const
{
    return sVal;
}

int Operand::integer() const
{
    return iVal;
}

void Operand::dump()
{
    if ( indirect)
    {
        std::cout << "m(";
    }

    switch ( type)
    {
    case OPERAND_GPR:       std::cout << sVal; break;
    case OPERAND_CONST_INT: std::cout << "$" << iVal; break;
    case OPERAND_CUSTOM_ID: std::cout << sVal; break;
    default: throw;
    }

    if ( indirect)
    {
        std::cout << ")";
    }
}

