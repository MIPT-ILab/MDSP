/**
 * handle_args.h - Analysing and handling of inputed arguments 
 * @author Dmitry Lukiyanchuk
 * Copyright 2009 MDSP team
 */

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

using std::cout;
using std::cin;
using std::endl;
using std::ifstream;

const int file_name_size = 80;

bool check_file_existing( const char* file_name);
bool check_symbols( const char* file_name);

/*
* Function analises and handles inserted arguments.
* There are three cases of corect call:
*   funcsim -h
*   funcsim <testname>
*   funcsim <testname> -l <log>
* Function saves <testname> into variable "test_file"
*               <log> into variable "log_file"
* Function checks inputed <testname> for existance.
*   If <testname> doesn't exist,
*   function will report about error and stop programm.
* Function checks inputed <log> for acceptability of its symbols.
*   Now allowed symbols are {a-z, A-Z, 0-9, _, ., \, /}.
* If <log> already exist, function will ask user for replacing.
* Any programmist can check if <log> was called.
*   He should only check if variable log_name != "\0".
*/
int handleArgs( int argc, char** argv, char* test_file, char* log_file)
{
    const char* version_number = "0.1";

    try
    {
        /* case: funcsim -h */
        if( argc == 2 && argv[1][0] == '-' && argv[1][1] == 'h' && argv[1][2] == '\0')
        {
            // Print help information and stop programm
            cout << "Functional simulator of multimedia digital signal processor." << endl;
            cout << "Version: " << version_number << endl;
            cout << "Usage:" << endl;
            cout << endl;
            cout << "\t" << argv[0] << " -h - show this help" << endl;
            cout << "\t" << argv[0] << " <testname> [options]" << endl;
            cout << endl;
            cout << "Available options:" << endl;
            cout << "\t" << "-l <log> - print logs into file <log>" << endl;
            exit(0);    // Stop programm
        }
        /* case: funcsim <testname> */
        else if( argc == 2)
        {
            /*
            * Try if test_file exist,
            * if not - report about error and stop programm;
            * if yes - save test_file_name.
            */
            if( check_file_existing(argv[1]) != 0)
            {
                cout << "Unable to open \"" << argv[1] << "\"" << endl;
                exit(-1);    // Stop programm
            }
            strncpy( test_file, argv[1], file_name_size);
            return 0; // continue main
        }
        /* case: funcsim <testname> -l <log> */
        else if( argc == 4 && argv[2][0] == '-' && argv[2][1] == 'l' && argv[2][2] == '\0')
        {
            /*
            * Try if test_file exist,
            * if not - report about error and stop programm;
            * if yes - save test_file_name.
            */
            if( check_file_existing( argv[1]) != 0)
            {
                cout << "Unable to open \"" << argv[1] << "\"" << endl;
                exit(-1);    // Stop programm
            }
            strncpy( test_file, argv[1], file_name_size);
            if( check_symbols( argv[3]) != 0)
            {
                cout << "There is permitted symbol in log_file name." << endl;
                exit(-1);   // Stop programm
            }
            
            if( check_file_existing(argv[3]) == 0)
            {
                cout << "File \"" << argv[3] << "\" already exist." 
                     << "Do you wont replace it?" << " (y/n)" << endl;
                char answer[10] = "\0";
                bool flag = 1;
                while( flag != 0)
                {
                    cout << ">";
                    cin >> answer;
                    if( answer[0] == 'y' && answer[1] == '\0')
                    {
                        strncpy( log_file, argv[3], file_name_size);
                        flag = 0;
                    }
                    else if( answer[0] == 'n' && answer[1] == '\0')
                    {
                        exit(0);    // Stop programm
                    }
                    else
                    {
                        cout << "Incorrect input. Please answer again: (y/n)" << endl;
                    }
                }
            }
            else
            {
                strncpy( log_file, argv[3], file_name_size);
            }
            return 0; // continue main
        }
        else
        {
            cout << "Wrong input. Call \"" << argv[0] << " -h\" for help" << endl;
            exit(-1);    // Stop programm
        }
    }
    catch(...)
    {
        cout << "Something going wrong in handle_args!" << endl;
        exit(-1);    // Stop programm
    }
    cout << "Something going wrong! (handle_args.h)" << endl;
    exit(-1);
}

bool check_file_existing( const char* file_name)
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
bool check_symbols( const char* file_name)
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

