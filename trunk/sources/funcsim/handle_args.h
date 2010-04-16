/**
 * handle_args.h - Analysing and handling of inputed arguments 
 * @author Dmitry Lukiyanchuk
 * Copyright 2009 MDSP team
 */
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

#include "defines.h"

using namespace std;

bool checkFileExisting( const char* file_name);
bool checkSymbols( const char* file_name);

/*
* Function analyses and handles inserted arguments.
* There are three cases of corect call:
*    funcsim * -h *
*    funcsim <testname>
*    funcsim <testname> -l <log>
* Function saves <testname> into variable "test_file"
*                <log> into variable "log_file"
* Function checks inputed <testname> for existance.
*    If <testname> doesn't exist,
*    function will report about error and stop programm.
* Function checks inputed <log> for acceptability of its symbols.
*    Now allowed symbols are {a-z, A-Z, 0-9, _, ., \, /}.
* If <log> already exist, function will ask user for replacing.
* Any programmist can check if <log> was called.
*    He should only check if variable log_name != "\0".
*/
int handleArgs( int argc, char** argv, char* test_file, char* log_file)
{
	const char* version = "0.1";

	/* case: -h*/
	for ( int i = 0; i < argc; i++)
	{
		if ( strcmp(argv[i], "-h") == 0)
		{
			// Print help information and stop programm
			cout << "Functional simulator of multimedia digital signal processor." << endl;
			cout << "Version: " << version << endl;
			cout << "Usage:" << endl;
			cout << endl;
			cout << "\t" << argv[0] << " -h - show this help" << endl;
			cout << "\t" << argv[0] << " <testname> [options]" << endl;
			cout << endl;
			cout << "Available options:" << endl;
			cout << "\t" << "-h" << "      " << " - show this help" << endl;
			cout << "\t" << "-l <log> - print logs into file <log>" << endl;
			exit(0);    // Stop programm
		}
	}
	/* case: funcsim <testname> */
	if ( argc > 1)
	{
		/*
		* Try if test_file exist,
		* if not - report about error and stop programm;
		* if yes - save test_file_name.
		*/
		if ( checkFileExisting(argv[1]) != 0)
		{
			cout << "Unable to open \"" << argv[1] << "\"" << endl;
			exit(-1);    // Stop programm
		}
		strncpy( test_file, argv[1], FILE_NAME_SIZE);
	} else
	{
		DIE( "Wrong input. Call \"%s -h\" for help\n", argv[0])
	}
	for ( int i = 2; i < argc; i++)
	{
		/* case: -l <log> */
		if ( strcmp( argv[i], "-l") == 0)
		{
			if ( strcmp( log_file, "\0") != 0)
			{
				DIE( "Error! Doubling call of \"-l\" parameter.\n")
			} else if ( i == ( argc - 1))
			{
				DIE( "Wrong call of \"-l\" parameter. Call \"%s -h\" for help.\n", argv[0])
			}
			if ( checkSymbols( argv[i+1]) != 0)
			{
				DIE( "There is permitted symbol in log_file name.\n")
			}
			if ( checkFileExisting(argv[i+1]) == 0)
			{
				cout << "File \"" << argv[i+1] << "\" already exist." 
				 << "Do you wont replace it?" << " (y/n)" << endl;
				char answer[10] = "\0";
				bool flag = 1;
				while ( flag != 0)
				{
					cout << ">";
					cin >> answer;
					if ( strcmp( answer, "y") == 0)
					{
						strncpy( log_file, argv[i+1], FILE_NAME_SIZE);
						flag = 0;
					} else if( strcmp( answer, "n") == 0)
					{
						exit(0);    // Stop programm
					} else
					{
						cout << "Incorrect input. Please answer again: (y/n)" << endl;
					}
				}
			} else
			{
				strncpy( log_file, argv[i+1], FILE_NAME_SIZE);
			}
			++i;    // <log> has been already used
		} 
		/* place for new parameters adding */
		else
		{
			DIE( "Wrong input. Call \"%s -h\" for help\n", argv[0])
		}
	}
	return 0;    // continue main
}

bool checkFileExisting( const char* file_name)
{
	ifstream fin( file_name);
	if( !fin)
	{
		return 1;
	}
	fin.close();
	return 0;
}

/*
* Check acceptability of file name symbols
* {a-z, A-Z, 0-9, _, ., \, /}.
*/
bool checkSymbols( const char* file_name)
{
	unsigned short int len = int( strlen(file_name));
	for( int i = 0; i < len; i++)
	{
		if(( file_name[i] >= 'a' && file_name[i] <= 'z') 
			|| ( file_name[i] >= 'A' && file_name[i] <= 'Z') 
			|| ( file_name[i] >= '0' && file_name[i] <= '9')
			|| file_name[i] == '_' || file_name[i] == '.'
			|| file_name[i] == '\\'|| file_name[i] == '/')
		{
		}
		else
		{
			return 1;
		}
	}
	return 0;
}

