/**
 * config.cpp - Implementation of Config class
 * @author Dmitry Lukiyanchuk
 * Copyright 2009 MDSP team
 */

#include "config.h"

#include "defines.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

using namespace std;


/* constructors */
Config::Config()
{
    strncpy( version, "0.1", version_size);
    strncpy( input_filename, "\0", file_name_size);
    strncpy( log_filename, "\0", file_name_size);
}
Config::Config( const int main_argc, char** main_argv):
argc(main_argc), argv(main_argv)
{
    strncpy( version, "0.1", version_size);
    strncpy( input_filename, "\0", file_name_size);
    strncpy( log_filename, "\0", file_name_size);
}
Config::~Config()
{
}
/* public methods */
/*
* Function handleArgs() analyses and handles inserted arguments.
* There are three cases of corect call:
*    funcsim * -h *
*    funcsim <testname>
*    funcsim <testname> -l <log>
* Function checks inputed <testname> for existance.
*    If <testname> doesn't exist,
*    function will report about error and stop programm.
* Function checks inputed <log> for acceptability of its symbols.
*    Now allowed symbols are {a-z, A-Z, 0-9, _, ., \, /}.
* If <log> already exist, function will ask user for replacing.
*/
int Config::handleArgs()
{
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
        * Try if input_filename exist,
        * if not - report about error and stop programm;
        * if yes - save input_filename_name.
        */
        if ( checkFileExisting(argv[1]) != 0)
        {
            cout << "Unable to open \"" << argv[1] << "\"" << endl;
            exit(-1);    // Stop programm
        }
        strncpy( input_filename, argv[1], file_name_size);
    } else
    {
        DIE( "Wrong input. Call \"%s -h\" for help\n", argv[0])
    }
    for ( int i = 2; i < argc; i++)
    {
        /* case: -l <log> */
        if ( strcmp( argv[i], "-l") == 0)
        {
            if ( strcmp( log_filename, "\0") != 0)
            {
                DIE( "Error! Doubling call of \"-l\" parameter.\n")
            } else if ( i == ( argc - 1))
            {
                DIE( "Wrong call of \"-l\" parameter. Call \"%s -h\" for help.\n", argv[0])
            }
            if ( checkSymbols( argv[i+1]) != 0)
            {
                DIE( "There is permitted symbol in log_filename name.\n")
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
                        strncpy( log_filename, argv[i+1], file_name_size);
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
                strncpy( log_filename, argv[i+1], file_name_size);
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
char* Config::getInputFilename()
{
    return input_filename;
}
/*
 * To check, if <log> was called you should check if
 * getLogFilename != "\0".
 */
char* Config::getLogFilename()
{
    return log_filename;
}
/* auxiliary private methods */
bool Config::checkFileExisting(const char *filename) const
{
    ifstream fin( filename);
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
bool Config::checkSymbols(const char *filename) const
{
    unsigned short int len = int( strlen(filename));
    for( int i = 0; i < len; i++)
    {
        if(( filename[i] >= 'a' && filename[i] <= 'z') 
            || ( filename[i] >= 'A' && filename[i] <= 'Z') 
            || ( filename[i] >= '0' && filename[i] <= '9')
            || filename[i] == '_' || filename[i] == '.'
            || filename[i] == '\\'|| filename[i] == '/')
        {
        }
        else
        {
            return 1;
        }
    }
    return 0;
}