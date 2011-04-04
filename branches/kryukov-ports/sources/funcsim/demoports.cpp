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
 * Third demo:
 * Overloading of WritePort by bandwidth
 *
 * Kryukov Pavel, 2011
*/

#include "ports.h"

using std::cout;
using std::endl;

int main(int argc, char* argv[])
{
    WritePort<int> writer("INIT", 1, 3);
    ReadPort<int> reader1("INIT", 10);
    ReadPort<int> reader2("INIT", 15);
    Port<int>::portMap->init();
    
    int operation1 = 100;
    int operation2 = 200;
    int *address;
   
    goto demo1;
   
demo1:
   
    cout << std::endl << "First demo" << endl;
    
    writer.write(&operation1, 3);
    cout << "'" << operation1 << "' was added on 3-rd clock" << endl;
    
    writer.write(&operation2, 4); 
    cout << "'" << operation2 << "' was added on 4-rd clock" << endl;    
    
    for ( unsigned i = 5; i < 15; i++)
    {
        cout << i << "-th clock;" << endl;
        if (!reader1.read(&address, i))
        {
            cout  << "'" << *address << "' was readed from ReadPort1 on " << i << "-th clock" << endl;
        }
    }
    Port<int>::portMap->lost( 16);
    return 0;

demo2:
    
    cout << std::endl << "Second demo" << endl;
    
    writer.write(&operation1, 3);
    cout << "'" << operation1 << "' was added on 3-rd clock" << endl;
    
    writer.write(&operation2, 4); 
    cout << "'" << operation2 << "' was added on 4-rd clock" << endl;  
    
    for ( unsigned i = 5; i < 14; i++)
    {
        cout << i << "-th clock;" << endl;
        if (!reader1.read(&address, i))
        {
            cout  << "'" << *address << "' was readed from ReadPort1 on " << i << "-th clock" << endl;
        }
    }
    
    for ( unsigned i = 14; i < 20; i++)
    {
        cout << i << "-th clock;" << endl;
        if (!reader2.read(&address, i))
        {
            cout  << "'" << *address << "' was readed from ReadPort2 on " << i << "-th clock" << endl;
        }
    }    
    
    Port<int>::portMap->lost( 20);
    return 0;
    
demo3:
   
    cout << std::endl << "Third demo" << endl;
    
    writer.write(&operation1, 4);
    cout << "'" << operation1 << "' was added on 3-rd clock" << endl;
    
    writer.write(&operation2, 4); 
    cout << "'" << operation2 << "' was added on 4-rd clock" << endl;     
    
    return 0;
}
