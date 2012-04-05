/**
 * Cache study exercise
 * @author Orlov Vasiliy
 * Copyright 2011 MDSP team
 */

#include <math.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

class Cache
{
    unsigned int size;
    unsigned int ways;
    unsigned int block_size;
    unsigned int set_number;
    unsigned int miss_number;
    unsigned int request_number;

    /* cache pointers (rows are sets, coloms are ways) */
    unsigned int **cache; // for 0-32 bit tag
    unsigned char **cache_bits; // for valid bit(0th) and Round-Robin bit(1st)
   
public:
	Cache( unsigned int ssize, unsigned int wways,
                unsigned int bblock_size, 
                unsigned int aaddr_size_in_bit);

    void processRead( unsigned int addr);
    double getMissRate() const;
};

Cache::Cache( unsigned int ssize, unsigned int wways,
                   unsigned int bblock_size, 
                   unsigned int aaddr_size_in_bit)
{
    unsigned int i, j;

	/* Calculation cache parametrs */
    size = ssize;
    ways = wways;
    block_size = bblock_size;
    set_number = ssize / bblock_size / wways;
    miss_number = 0;
    request_number = 0;

	/* Creating our cache */
    cache = new unsigned int*[set_number];
    for ( i = 0;  i < set_number; i++)
        cache[i] = new unsigned int[ways];
    cache_bits = new unsigned char*[set_number];
    for ( i = 0;  i < set_number; i++)
        cache_bits[i] = new unsigned char[ways];

	/* Initialisation control bits */
    for ( i = 0; i < set_number; i++)
        for ( j = 0; j < ways; j++)
            if ( j == 0) cache_bits[i][j] = 2;
               else cache_bits[i][j] = 0;


}

void Cache::processRead( unsigned int addr)
{
    unsigned int set, tag, i, hit = 0;
	
    ++request_number;

	/* Decode adress */
	addr = addr / block_size; // deleting byte offset from adress
    set = addr % set_number; // getting set
    tag = addr / set_number; // getting tag

	/* Search data in cache */
    for ( i = 0; i < ways; ++i)
	    if ( ( tag == cache[set][i]) && ( ( cache_bits[set][i] % 2) == 1))
        {
		    hit = 1; // indicator cache hit
			break;
        }

    /* Processing miss */
    if ( hit ==0)
    {
        ++miss_number;
	    for ( i = 0; i < ways; ++i)
			if ( ( ( cache_bits[set][i] / 2) % 2) == 1)
	        {
                cache[set][i] = tag;
                cache_bits[set][i] = 1;
				if ( i == ( ways - 1)) cache_bits[set][0] += 2;
				     else  cache_bits[set][i+1] += 2;
                break;
	        }

    }

}

double Cache::getMissRate() const
{
    return ( double) miss_number / ( double) request_number;
}

/* Getting 32-bit instruction from file*/
unsigned int getNextAdress( FILE* fd)
{
    char buffer[10], c;
    unsigned int addr = 0;
    int k = -1, i;

    /* Allocation hexadecimal number*/
    fread(&c, 1, 1, fd);
    fread(&c, 1, 1, fd); 
   	fread(&c, 1, 1, fd); 
    while ( ( c != ' ') && ( !feof( fd)))
    {
        ++k; 
        if ( isdigit( c)) buffer[k] = c - '0';
            else buffer[k] = c - 'a' + 10; 
		fread(&c, 1, 1, fd); 
    }

    /* Conversion hexadecimal number to decimal */
    for ( i = k; i >= 0; --i)
        addr += buffer[i] * ( int)pow( 16.0, k-i); 

    return addr;
}

int main(int argc, char *argv[])
{
    FILE *input_file, *output_file;
    unsigned int addr;
    char *buffer, csv_buffer[13];
    double d;
    int i, j, k, s, m;
    int number = 66; // number of caches examined

    /* Initialization cache objects*/
    Cache o[66] = 
    {
        Cache( 1024, 1, 4, 32), Cache( 2048, 1, 4, 32), Cache( 4096, 1, 4, 32), Cache( 8192, 1, 4, 32), Cache( 16384, 1, 4, 32), 
        Cache( 32768, 1, 4, 32), Cache( 65536, 1, 4, 32), Cache( 131072, 1, 4, 32), Cache( 262144, 1, 4, 32), 
        Cache( 524288, 1, 4, 32), Cache( 1048576, 1, 4, 32), 

        Cache( 1024, 2, 4, 32), Cache( 2048, 2, 4, 32), Cache( 4096, 2, 4, 32), Cache( 8192, 2, 4, 32), Cache( 16384, 2, 4, 32), 
        Cache( 32768, 2, 4, 32), Cache( 65536, 2, 4, 32), Cache( 131072, 2, 4, 32), Cache( 262144, 2, 4, 32), 
        Cache( 524288, 2, 4, 32), Cache( 1048576, 2, 4, 32), 

        Cache( 1024, 4, 4, 32), Cache( 2048, 4, 4, 32), Cache( 4096, 4, 4, 32), Cache( 8192, 4, 4, 32), Cache( 16384, 4, 4, 32), 
        Cache( 32768, 4, 4, 32), Cache( 65536, 4, 4, 32), Cache( 131072, 4, 4, 32), Cache( 262144, 4, 4, 32), 
        Cache( 524288, 4, 4, 32), Cache( 1048576, 4, 4, 32), 

        Cache( 1024, 8, 4, 32), Cache( 2048, 8, 4, 32), Cache( 4096, 8, 4, 32), Cache( 8192, 8, 4, 32), Cache( 16384, 8, 4, 32), 
        Cache( 32768, 8, 4, 32), Cache( 65536, 8, 4, 32), Cache( 131072, 8, 4, 32), Cache( 262144, 8, 4, 32), 
        Cache( 524288, 8, 4, 32), Cache( 1048576, 8, 4, 32), 

        Cache( 1024, 16, 4, 32), Cache( 2048, 16, 4, 32), Cache( 4096, 16, 4, 32), Cache( 8192, 16, 4, 32), Cache( 16384, 16, 4, 32), 
        Cache( 32768, 16, 4, 32), Cache( 65536, 16, 4, 32), Cache( 131072, 16, 4, 32), Cache( 262144, 16, 4, 32), 
        Cache( 524288, 16, 4, 32), Cache( 1048576, 16, 4, 32), 

        Cache( 1024, 256, 4, 32), Cache( 2048, 512, 4, 32), Cache( 4096, 1024, 4, 32), Cache( 8192, 2048, 4, 32), Cache( 16384, 4096, 4, 32), 
        Cache( 32768, 8192, 4, 32), Cache( 65536, 16384, 4, 32), Cache( 131072, 32768, 4, 32), Cache( 262144, 65536, 4, 32), 
        Cache( 524288, 131072, 4, 32), Cache( 1048576, 262144, 4, 32)

	};

    printf("Cache Simulator has started. Please wait...\n");

    /* Simulate cache work*/ 
    input_file = fopen( argv[1], "r" ); 
    while( !feof( input_file))
    {
        addr = getNextAdress( input_file); 
        for ( i = 0; i < number; ++i)
           o[i].processRead( addr);
    }
    fclose( input_file);

    /* Getting CSV output file*/
    output_file = fopen( argv[2], "w");
    for ( i = 0; i < number; ++i)
	{
        d = o[i].getMissRate();
        buffer = _fcvt( d, 6, &j, &s);

		/* Getting csv_buffer from buffer and j*/
        if ( d != 1)
        {
            strcpy(csv_buffer, "0");
            if ( j < 0) 
            {
                strcpy( ( csv_buffer + 1), ".");
                for ( m = 0; m > j; --m) strcpy( ( csv_buffer + 2 - m), "0");
                strcpy( ( csv_buffer + 2 - m), buffer);
            }
            else
            {
                strcpy( ( csv_buffer + 1), buffer);
                strcpy( ( csv_buffer + j + 1), ".");
                strcpy( ( csv_buffer + j + 2), ( buffer + j));
            }
        }
        else
        {
            strcpy(csv_buffer, buffer);
            strcpy( ( csv_buffer + j), ".");
            strcpy( ( csv_buffer + j + 1), ( buffer + j));
        }

        if ( ( ( ( i +1) % 11) == 0) && ( i != 0))
        {
            strcat( csv_buffer, "\n");
		}
		else 
        {
            strcat( csv_buffer, ", ");
            k = k + 3;
		}
		k = strlen( csv_buffer);


        fwrite( csv_buffer, k, 1, output_file); //write one number to CSV
	}
    fclose( output_file);

    printf("Cache Simulator successfully finished.\n");

    return 0;
}
