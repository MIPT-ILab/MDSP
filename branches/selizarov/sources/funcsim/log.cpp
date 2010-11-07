#include "log.h"

/* Show warning message*/
void log::warning(const char * message)
	{
		cout <<"Warning: "<<message<<"\n";
	}

/* Show error message and assert simulator*/
void log::critical(const char * message)
	{
		cout <<"Error: "<<message<<"\n";
		assert(0);
	}