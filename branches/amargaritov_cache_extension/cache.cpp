/*
 * cache.cpp
 *
 *  Created on: Apr 16, 2012
 *      Author: art
 */

/** This file is for definition of Abstract classes's methods. */

#include "cache.h"

///============================================================================================
///=====================### Abstract classes's methods ###=======================================
///============================================================================================
Block::Block() { tag_ = 0; valid_ = 0;};
SetAbstract::SetAbstract( uint ways) { blocks_.resize( ways, Block());};
