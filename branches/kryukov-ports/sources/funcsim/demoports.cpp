/**
 * demoports.cpp
 *
 * Very simple demos of ports. 
 *
 * First demo:
 * Connects WritePort with one ReadPort with defined latency (10)
 * We are adding data to port in 3 and 4 clock, and trying to get it in all clocks.
 * But we can read it only on 13 and 14 clock because latency of ReadPort.
 *
 * 
 * Second demo:
 * Connects WritePort and two ReadPorts with different latency.
 * We are adding data to port in 3 and 4 clock, trying to get in from Reader1 from 5 to 13 clock.
 * After, from 14 to 19 clock we're trying to read data from Reader2.
 *
 * Kryukov Pavel, 2011
*/

#include "ports.h"

static int SIZE = 100;

int main(int argc, char* argv[])
{
    PortMap<int> map;
    WritePort<int> writer(&map,"INIT", SIZE, SIZE);
    ReadPort<int> reader1(&map,"INIT", 10);
    ReadPort<int> reader2(&map,"INIT", 15);
    map.init();
    
    int operation1 = 100;
    int operation2 = 200;
    int *address;
   
    std::cout << std::endl << "First demo" << std::endl;
    
    writer.write(&operation1, 3);
    std::cout << "'" << operation1 << "' was added on 3-rd clock" << std::endl;
    
    writer.write(&operation2, 4); 
    std::cout << "'" << operation2 << "' was added on 4-rd clock" << std::endl;    
    
    for ( unsigned i = 5; i < 15; i++)
    {
        std::cout << i << "-th clock;" << std::endl;
        if (!reader1.read(&address, i))
        {
            std::cout  << "'" << *address << "' was readed from ReadPort1 on " << i << "-th clock" << std::endl;
        }
    }
    
    std::cout << std::endl << "Second demo" << std::endl;
    
    writer.write(&operation1, 3);
    std::cout << "'" << operation1 << "' was added on 3-rd clock" << std::endl;
    
    writer.write(&operation2, 4); 
    std::cout << "'" << operation2 << "' was added on 4-rd clock" << std::endl;  
    
    for ( unsigned i = 5; i < 14; i++)
    {
        std::cout << i << "-th clock;" << std::endl;
        if (!reader1.read(&address, i))
        {
            std::cout  << "'" << *address << "' was readed from ReadPort1 on " << i << "-th clock" << std::endl;
        }
    }
    
    for ( unsigned i = 14; i < 20; i++)
    {
        std::cout << i << "-th clock;" << std::endl;
        if (!reader2.read(&address, i))
        {
            std::cout  << "'" << *address << "' was readed from ReadPort2 on " << i << "-th clock" << std::endl;
        }
    }    
    
    return 0;

}
