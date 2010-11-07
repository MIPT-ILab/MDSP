/**
 * log.h - Header of log class 
 * includes 2 methods to show warrnings and errors
 * @author Stas Elizarov
 * Copyright 2010 MDSP team
 */

#ifndef	LOG_H
#define LOG_H

#include <iostream>
#include <cassert>

using namespace std;

class log
{
public:
	/* Method to show warning message*/
	void warning(const char * message);

	/* Method to show error and assert simulator*/
	void critical(const char * message);
};


#endif /* LOG_H */
