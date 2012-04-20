#include "cashe.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>


//#include <iostream>

using namespace std;

const int MAX_SIZE_HEX_ADDRESS = 15;

int main( int argc, char**argv)
{
	int fd1, fd2;
	if ( ( fd1 = open( argv[1],O_RDONLY)) == -1)
	{
		cout << argv[ 0] << ": Can't open file " << "'" << argv[ 1] << "'"<< endl;
		exit ( -1);
	}
	
	if ( ( fd2 = open( argv[ 2],O_RDWR)) == -1)
	{
		cout << argv[ 0] << ": Can't open file " << "'" << argv[ 2] << "'"<< endl;
		exit (-1);
	}
	Cashe *myCashe = new Cashe( 1024, 2, 4, 32);//cout << "Hello" << endl;
	string Address;//[ MAX_SIZE_HEX_ADDRESS] = {};
	char *cur = new char;
	int i = 0;
start:
	while ( read ( fd1, (void*)cur, 1) != 0)
	{cout << "Hello" << endl;
		//cout << *cur << endl;
		if ( *cur ==  ' ' || *cur == '\0' || *cur == '\n')
		{
			i = 0;
			unsigned int dec_address = 0;
			char Buffer[ MAX_SIZE_HEX_ADDRESS] = {};
			Address.copy( Buffer, MAX_SIZE_HEX_ADDRESS - 2, 2);
			//cout << Buffer << endl;
			sscanf( Buffer,"%x",&dec_address);
			//cout << dec_address << endl;
			Address.clear();
			//cout << endl << endl;
			myCashe->processRead( dec_address);
			goto start;
		}
		Address = Address + cur;
		i++;
	}
	cout << "miss rate = " << myCashe->getMissRate() << endl;
	close( fd1);
	close( fd2);
	return 0;
}
