/**
 * demoports.cpp
 *
 * Very simple test of ports. Connects WritePort with one ReadPort with defined latency (10)
 * We are adding data to port in 0 clock, and trying to get it in all clocks.
 * But we can read it only on 10 clock because latency of ReadPort is 10.
 * On the eleventh clock program failed, because there's no data in port.
 *
 * Kryukov Pavel
*/

#include "ports.h"

static int SIZE = 100;

int main(int argc, char* argv[])
{
    WritePort<int> writer("INIT", SIZE);
    ReadPort<int> reader("INIT", 10);
    
    int buffer = 5;
    int *address;
    
    writer.write(&buffer, 0);
    
    for ( unsigned i = 1; i < SIZE; i++)
    {
        std::cout << i << "-th clock;" << std::endl;
        if (!reader.read(&address, i))
        {
            std::cout << *address << " was readed on " << i << "-th clock" << std::endl;
        }
    }
    
    return 0;

}
