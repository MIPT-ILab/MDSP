/**
 * register_file.cpp - Implementation of register file model
 * Implementation of methods to operates with register file model
 * Copyright 2009 MDSP team
 */

#include "register_file.h"

/* Read a logical set of bytes (RegVal) form physical register with number reg_num */
RegVal* RegisterFileModel::readReg( physRegNum reg_num)
{
    return register_file+reg_num;
}

 /* Write a logical set of bytes (RegVal) to physical register with number reg_num */ 
void RegisterFileModel::writeReg( physRegNum reg_num, RegVal reg_value)
{
    (register_file+reg_num)->setByteVal( low_byte, reg_value.byte_line->byte_line[ low_byte]);
    (register_file+reg_num)->setByteVal( high_byte, reg_value.byte_line->byte_line[ high_byte]);
}
