#include "cashe.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <fstream> 


//#include <iostream>
const int MAX_SIZE_HEX_ADDRESS = 15;
const int FULL = 0;
const int SIZE = 11;
const int WAYS = 6;
const int MAX_LENGTH_DEC_NUMBER = 20;
using namespace std;

void openFiles ( int* fd1, char** argv);
void closeFiles ( int fd1);



int main( int argc, char** argv)
{
	int fd1 = 0;
	int fd2 = 0;
	char MissRatio[ MAX_LENGTH_DEC_NUMBER] = {};
	double missRate = 0;
	
	unsigned int CacheWays[ WAYS] = { 1, 2, 4, 8, 16, FULL};
    unsigned int CacheSize[ SIZE] = { 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576};
	
	string Address;
	char *cur = new char;
	
	int i = 0;
	int j = 0;
	int k = 0;
	
	ofstream output_file( argv[ 2]);
    	
	for ( j = 0; j < WAYS; j++)
	{
		for ( k = 0; k < SIZE; k++)
		{
			Cashe *myCashe = new Cashe( CacheSize[ k], CacheWays[ j], 4, 32);//cout << "Hello" << endl;		
			openFiles( &fd1, argv);
start:		while ( read ( fd1, (void*)cur, 1) != 0)
			{
				if ( *cur ==  ' ' || *cur == '\0' || *cur == '\n')
				{
					i = 0;
					unsigned int dec_address = 0;
					char Buffer[ MAX_SIZE_HEX_ADDRESS] = {};
					Address.copy( Buffer, MAX_SIZE_HEX_ADDRESS - 2, 2);
					sscanf( Buffer, "%x", &dec_address);
					Address.clear();
					myCashe->processRead( dec_address);
					goto start;
				}
				Address = Address + cur;
				i++;
			}
			cout << "hello" << endl;
			missRate = myCashe->getMissRate();
			//output_file << missRate << ", ";
			cout << ( myCashe->getMissRate()) << ", ";
			//fflush( output_file);
			delete myCashe;
			closeFiles( fd1);
		}
		output_file << endl;
		cout << endl;
	}
	output_file.close();
	//cout << "miss rate = " << myCashe->getMissRate() << endl;
	//close( fd1);
	//close( fd2);
	return 0;
}

void openFiles ( int* fd1, char** argv)
{
	char* argv1 = argv[1];
	//cout << argv1 << endl;
//	char* argv2 = argv[2];
	//cout << argv2 << endl;
	char* argv0 = argv[0];
//	*fd2 = open( argv2, O_RDWR);
/*	
	if ( ( *fd2 = open( argv2, O_RDWR)) == -1)
	{
		cout << argv0 << ": Can't open file " << "'" << argv2 << "'"<< endl;
		exit (-1);
	}
*/	
	if ( ( *fd1 = open( argv1, O_RDONLY)) == -1)
	{
		cout << argv0 << ": Can't open file " << "'" << argv1 << "'"<< endl;
		exit ( -1);
	}
}

void closeFiles( int fd1)
{
	close( fd1);
}



