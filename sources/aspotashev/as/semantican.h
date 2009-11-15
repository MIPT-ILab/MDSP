
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


class Operand
{
public:
    /**
     * Default constructor
     *
     * Sets @indirect to false
     */
    Operand();

    /**
     * Creates an operand defined by a single identifier
     *
     * @param id_string The identifier in the operand.
     */
    static Operand *createId( std::string id_string);

    /**
     * Creates an indirect operand with the address in memory defined
     * by an identifier. Example: "(%r0)"
     *
     * @param id_string The identifier in the operand.
     */
    static Operand *createIdInd( std::string id_string);

    /**
     * Creates a constant integer operand
     *
     * @param iVal The value of the constant.
     */
    static Operand *createConstInt( int iVal);

    /**
     * Returns whether the operand is a memory address in a register
     * ("(%r0)".."(%r31)")
     */
    bool isIndirectGpr();

    /**
     * Returns whether the operand is a register
     * ("%r0".."%r31")
     */
    bool isDirectGpr();

    /**
     * Returns whether the operand is a constant integer
     */
    bool isConstInt();

    /**
     * Returns the identifier for operands of types
     * OPERAND_GPR and OPERAND_CUSTOM_ID
     *
     * Getter for sVal
     */
    std::string str();

    /**
     * Returns the integer value for operand of type OPERAND_CONST_INT
     *
     * Getter for iVal
     */
    int integer();

    void dump();

private:
    OPERAND_TYPE type;
    bool indirect;
    std::string sVal;
    int iVal;
};


struct SemanticUnit
{
    UNIT_TYPE type;

    std::string sVal;
    std::vector<Operand *> operands;

    /**
     * Creates a processor instruction as a semantic unit
     *
     * @param opcode The instruction name.
     * @param operands The list of operands of the instruction.
     */
    static SemanticUnit *createOperation(
        std::string opcode, std::vector<Operand *> operands);

    /**
     * Creates a label as a semantic unit
     *
     * @param id The identifier of the label.
     */
    static SemanticUnit *createLabel( std::string id);

    void dump();
};


/**
 * This class is used to generate a sequence of semantic unit from a
 * sequence of tokens
 */
class SemanticAn
{
public:
    /**
     * Convenience constructor
     *
     * @param tokens The sequence of tokens to work with.
     */
    SemanticAn( std::vector<Token *> tokens);

    /**
     * Generates the sequence of semantic units
     */
    std::vector<SemanticUnit *> run();

private:
    bool isOpcode( std::string s); // architecture-dependent

    /**
     * @internal
     * Parses a sequence of tokens starting from @tok as an operands list
     * split by commas and ending with an end-of-string, e.g.:
     *      %r0, %r1, (%r2)\n
     */
    std::vector<Operand *> parseOperandList();

    /**
     * @internal
     * Parses a single assembler command operand
     */
    Operand *parseOperand();


    /**
     * The list of tokens on the input
     */
    std::vector<Token *> tokens;

    /**
     * Iterator pointing to the current token
     */
    std::vector<Token *>::iterator tok;
};

#endif

