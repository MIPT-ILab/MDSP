
#include <vector>

#include "memory.h"
#include "semantican.h"


class Assembler
{
public:
    Assembler( std::vector<SemanticAn::Unit *> units);
    std::map<unsigned int, hostUInt8> run();
    ByteLine *encodeOperation(
        SemanticAn::Unit *operation, unsigned int pc);

private:
    int getGprNum( std::string id);

private:
    std::vector<SemanticAn::Unit *> units;
};

