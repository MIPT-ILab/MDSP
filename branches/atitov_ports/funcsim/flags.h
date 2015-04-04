/**
 * flags.h - Header of Flags class which defines
 * fields and methods to operate with flag register
 * Copyright 2009 MDSP team
 */

#ifndef FLAGS_H
#define FLAGS_H

#include <cassert>

#include "register_file.h"

#define FLAG_N_POSITION 0x80
#define FLAG_Z_POSITION 0x40
#define FLAG_C_POSITION 0x20
#define FLAG_O_POSITION 0x10

#define FLAG_N_POS_INVERSED (char)(~FLAG_N_POSITION)
#define FLAG_Z_POS_INVERSED (char)(~FLAG_Z_POSITION)
#define FLAG_C_POS_INVERSED (char)(~FLAG_C_POSITION)
#define FLAG_O_POS_INVERSED (char)(~FLAG_O_POSITION)

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
    
    void init(){ this->setByte( 0, 0x0000);}

};


#endif /* FLAGS_H */

