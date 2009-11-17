
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


/**
 * Objects of this class define operands of assembler commands
 */
class Operand
{
public:
    /**
     * Default constructor
     *
     * Sets @p indirect to false
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
    bool isIndirectGpr() const;

    /**
     * Returns whether the operand is a register
     * ("%r0".."%r31")
     */
    bool isDirectGpr() const;

    /**
     * Returns whether the operand is a constant integer
     */
    bool isConstInt() const;

    /**
     * Returns the identifier for operands of types
     * OPERAND_GPR and OPERAND_CUSTOM_ID
     *
     * Getter for @p sVal
     */
    std::string str() const;

    /**
     * Returns the integer value for operand of type OPERAND_CONST_INT
     *
     * Getter for @p iVal
     */
    int integer() const;

    /**
     * Dumps the operand into a string
     */
    std::string dump() const;

private:
    /**
     * The type of the operand, one of the following:
     *      OPERAND_GPR       -- register ("%r0") or "m(reg)" ("(%r0)")
     *      OPERAND_CONST_INT -- integer constant
     *      OPERAND_CUSTOM_ID -- user-defined identifier (e.g. a label)
     */
    OPERAND_TYPE type;

    /**
     * Contains whether the operand is an operand in memory with its
     * address stored in a GPR (general-purpose register)
     */
    bool indirect;

    /**
     * The identifier of a register or an user-defined identifier
     * (when @p type is OPERAND_GPR or OPERAND_CUSTOM_ID)
     */
    std::string sVal;

    /**
     * The value of integer constant (when @p type is OPERAND_CONST_INT)
     */
    int iVal;
};


/**
 * A semantic unit is a part of source code that defines a complete
 * instruction for the assembler (like a sentence in natural languages)
 * Examples:
 *      - labels
 *      - assembler commands
 */
class SemanticUnit
{
public:
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

    /**
     * Returns the type of the semantic unit
     *
     * Getter for @p unitType
     */
    UNIT_TYPE type() const;

    /**
     * Returns the string value of the semantic unit, e.g.
     *      1. label identifier when type == UNIT_LABEL,
     *      2. processor instruction name when type == UNIT_OPERATION
     *
     * Getter for @p sVal
     */
    std::string str() const;

    /**
     * Compares the string value of the semantic unit with another string
     *
     * @see str
     */
    bool operator== ( const std::string &str) const;

    /**
     * Returns the number of assembler command operands when the
     * semantic unit is an assembler command (type == UNIT_OPERATION)
     */
    int nOperands() const;

    /**
     * Read-access to a specific assembler command operand
     *
     * @param index The index in the list of operands.
     */
    const Operand *operator[] ( int index) const;

    /**
     * Dumps the semantic unit into a string
     */
    std::string dump() const;

private:
    /**
     * The type of the semantic unit, one of the following:
     *      UNIT_LABEL     -- a label
     *      UNIT_OPERATION -- an assembler command
     */
    UNIT_TYPE unitType;

    /**
     * The identifier of label (when @p unitType is UNIT_LABEL) or
     * the name of assembler command (when @p unitType is UNIT_OPERATION)
     */
    std::string sVal;

    /**
     * The operands list of the assembler command
     * (when @p unitType is UNIT_OPERATION)
     */
    std::vector<Operand *> operands;
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
     * dtor
     */
    ~SemanticAn();

    /**
     * Generates the sequence of semantic units
     */
    std::vector<SemanticUnit *> run();

private:
    /**
     * Returns whether a string is the name of an assembler command
     * (e.g. "brr", "jmp", ...)
     */
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

