/**
 * mdsp-asm/assembler.h -- Definition of Assembler class,
 *                         the assembler output generator
 * Copyright 2009 MDSP team
 */

#include <vector>

#include "memory.h"
#include "semantican.h"


/**
 * This class is used to assemble an executable image a sequence of
 * semantic units
 */
class Assembler
{
public:
    /**
     * Convenience constructor
     *
     * @param units The sequence of semantic units to work with.
     */
    Assembler( std::vector<SemanticUnit *> units);

    /**
     * dtor
     */
    ~Assembler();

    /**
     * Generates an executable image defined by a list of
     * pairs (byte address; byte value)
     */
    std::map<unsigned int, hostUInt8> run();

    /**
     * Encodes a processor instruction located at word address @p pc
     * in program memory
     *
     * @param operation Pointer to the assembler command.
     * @param pc The word address of the instruction in program memory.
     */
    ByteLine *encodeOperation(
        SemanticUnit *operation, unsigned int pc);

private:
    /**
     * @internal
     * Return the number of a register define by an identifier, e.g.
     * "%r23" => 23
     */
    int getGprNum( std::string id);

private:
    /**
     * The sequence of semantic units given on the input
     */
    std::vector<SemanticUnit *> units;
};

