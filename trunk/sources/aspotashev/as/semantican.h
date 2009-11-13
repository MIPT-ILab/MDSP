
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
 * This class is used to generate a sequence of semantic unit from a
 * sequence of tokens
 */
class SemanticAn
{
public:
    struct Operand
    {
        OPERAND_TYPE type;
        bool indirect;
        std::string sVal;
        int iVal;

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

        void dump();
    };

    struct Unit
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
        static Unit *createOperation(
            std::string opcode, std::vector<Operand *> operands);

        /**
         * Creates a label as a semantic unit
         *
         * @param id The identifier of the label.
         */
        static Unit *createLabel( std::string id);

        void dump();
    };

public:
    /**
     * Convenience constructor
     *
     * @param tokens The sequence of tokens to work with.
     */
    SemanticAn( std::vector<TokenAn::Token *> tokens);

    /**
     * Generates the sequence of semantic units
     */
    std::vector<Unit *> run();

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

private:
    /**
     * The list of tokens on the input
     */
    std::vector<TokenAn::Token *> tokens;

    /**
     * Iterator pointing to the current token
     */
    std::vector<TokenAn::Token *>::iterator tok;
};

#endif

