/**
 * ports.h - template for simulation of ports.
 * @author Pavel Kryukov
 * Copyright 2011 MDSP team
 */
 
#ifndef PORTS_H
#define PORTS_H

#include <map>
#include <queue>

#include "log.h"
#include "types.h"

/*
 * WritePort
 */
template<class T> class WritePort: public log
{
    private:
        std::queue<T*> _data;
        std::queue<hostUInt64> _cycle;
        string _key;
        int _bandwidth;
    public:
        WritePort<T>( string, int);
        void write( T*, hostUInt64);
        
        T* getData();
        hostUInt64 getCycle() const;
};

/*
 * Map of ports (should be upgraded to class
*/
std::map<string, WritePort<int>* > portMap;

/*
 * Constructor
 *
 * First argument is key which is used to connect ports.
 * Second is the bandwidth of port (how much data items can port hold)
*/
template<class T> WritePort<T>::WritePort(string key, int bandwidth)
{
    _key = key;
    _bandwidth = bandwidth;
    portMap.insert(std::pair<string, WritePort<T>*>(_key, this));
}

/*
 * Write method.
 *
 * First argument is the link to data.
 * Second argument is the cycle number.
*/
template<class T> void WritePort<T>::write( T* what, hostUInt64 cycle)
{
    if (_data.size() < _bandwidth)
    {
        _data.push(what);
        _cycle.push(cycle); 
    }    
    else
    {
    // If port is overloaded, assert.
        critical("Port is overloaded\n");//, _key);
    }
}


/*
 * Get data method.
 * It's not a const method, it takes element from queue.
*/
template<class T> T* WritePort<T>::getData()
{
    if (_data.empty())
    {
    // If there's nothing in port, assert.
        critical("No data in port\n");//, _key);
    }
    else
    {
    // Getting front element
        T* buffer = _data.front();
        _data.pop();
        _cycle.pop();
        return buffer;
    }
}

/*
 * Get cycle method
*/
template<class T> hostUInt64 WritePort<T>::getCycle() const
{
    return _cycle.front();
}

/*
 * Read Port
 *
 * It's just a receiver, so it much more simplier
*/

template<class T> class ReadPort: public log
{
    private:
        string _key;
        hostUInt64 _latency;
    public:
        ReadPort<T>( string, hostUInt64);
        int read( T**, hostUInt64);
};

/*
 * Constructor
 *
 * First argument is the connection key.
 * Second argument is the latency of port.
*/ 
template<class T> ReadPort<T>::ReadPort( string key, hostUInt64 latency)
{
    _key = key;
    _latency = latency;
}

/*
 * Read method
 *
 * First arguments is address, second is the number of cycle
 *
 * Finds writePort with data from PortMap. If not, asserts.
 * Then compares current cycle with needed cycle (cycle of adding plus latency).
 * If current cycle is less than needed, returns 1;
 * If current cycle is equal or greater than needed, tries to return data address to first argument. (see WritePort::getData)
*/
template<class T> int ReadPort<T>::read( T** address, hostUInt64 cycle)
{   
    if (  portMap.find(_key) != portMap.end())
    {
        if ( (portMap[_key]->getCycle() + _latency) <= cycle)
        {
            *address = portMap[_key]->getData();
            return 0;
        }
        else
        {
            return -1;
        }
    }
    else
    {
        critical("Read port is not connected\n");
    }
}

#endif // PORTS_H