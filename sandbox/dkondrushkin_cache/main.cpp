#include <iostream>
#include <fstream>
#include <conio.h>
#include "cache.h"
using namespace std;


int main( int argc, char* argv[])
{
    hostUInt32 ways_massive[6] = { 1 , 2, 4, 8, 16, 0};
    hostUInt32 cache_sizes_massive[11] = { 1 , 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024};    
    
    ifstream read_file;
    ofstream write_file;
    hostUInt32 val1, val2;
    hostUInt32 i, j, k;

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
  
    for ( i = 0; i < 6; i++)
    {
        for ( j = 0; j < 11; j++ )
        {
            {
                // creating cache
                if ( ways_massive[i] == 0) // simulating full associativity
                {
                    k = 1024 * cache_sizes_massive[j] / 4; // k = ways = cache elements
                } else
                {
                    k = ways_massive[i]; // k = ways != cache elements ( not full associativity)
                }
                Cache cache( 1024 * cache_sizes_massive[j], k , 4, 32);

                // cycle of reading input data and calling cache request
                read_file >> hex >> val1;
                val2 = val1;
                while ( !read_file.eof())
                {
                    read_file >> hex >> val1;
                    cache.processRead( val2);
                    val2 = val1;
                }
                cache.processRead( val2);
                write_file << hex << cache.getMissRate() << ", ";
            }            
            read_file.close();
            read_file.open( argv[1]);
        }
        write_file << '\n';
    }    

    // explicit closing of files
    read_file.close();
    write_file.close();

    _getch();
        return 0;
}