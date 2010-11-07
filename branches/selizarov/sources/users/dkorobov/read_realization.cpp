/**
* Realization of the "read()" method
* Designed by Dmitry Korobov
*/

#include "read_realization.h"

MemVal* MyMemory::read()
{
	MemVal* mv = new MemVal(3);
	mv->setByteVal( 1, 1);
	mv->setByteVal( 2, 2);
	mv->setByteVal( 3, 3);
	return mv;
}