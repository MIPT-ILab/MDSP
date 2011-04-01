/**
 * flags.h - Header of Flags class which defines
 * fields and methods to operate with flag register
 * Copyright 2009 MDSP team
 */

#ifndef FLAGS_H
#define FLAGS_H

#include <cassert>

#include "register_file.h"

#define FLAG_N_POSITION 128
#define FLAG_Z_POSITION 64
#define FLAG_C_POSITION 32
#define FLAG_O_POSITION 16

/**
 * Class of flag register description
 */
class Flags: public RegVal
{

public:
    Flags();

    /* Get methods */
    bool getFlag( FlagType flag);

    /* Set methods */
    void setFlag( FlagType flag, bool value);

};


#endif /* FLAGS_H */

