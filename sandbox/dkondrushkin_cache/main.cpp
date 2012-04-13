#include <iostream>
#include <fstream>
#include <conio.h>
#include <string.h>
#include "cache.h"
using namespace std;


int main( int argc, char* argv[])
{
    ifstream read_file;
    ofstream write_file;

    // checking correct programme call
    if ( argc != 3)
    {        
        cout << "\n Error: not enough arguments(" << argc - 1 <<") in programme call.";
            return 0;
    } else
    {
        read_file.open( argv[1]);
        write_file.open( argv[2]);
        if ( ! ( read_file.is_open() && write_file.is_open()))
        {
            cout << "\n Error: incorrect arguments (file names) in programme call.";
                return 0;
        }
    }
