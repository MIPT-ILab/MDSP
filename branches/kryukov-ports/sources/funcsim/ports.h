/**
 * ports.h - template for simulation of ports.
 * @author Pavel Kryukov
 * Copyright 2011 MDSP team
 */
 
#ifndef PORTS_H
#define PORTS_H

#include <map>
#include <queue>
#include <list>
#include <string>

#include "log.h"
#include "types.h"

template<class T> class PortMap;

/*
 * WritePort
 */
template<class T> class WritePort: public log
{
    private:
        std::queue<T*> _data;
        std::queue<hostUInt64> _cycle;
        std::string _key;
        unsigned _bandwidth;
        unsigned _phoneOn;
        PortMap<T>* _portMap;
    public:
        WritePort<T>( PortMap<T>*,std::string, unsigned, unsigned);
        void write( T*, hostUInt64);
        T* getData();
        hostUInt64 getCycle() const;
        unsigned getPhoneOn() const;
};

/*
 * Constructor
 *
 * First argument is pointer to map of ports.
 * Second argument is key which is used to connect ports.
 * Third is the bandwidth of port (how much data items can port hold).
 * Fourth is maximum number of ReadPorts.
 *
 * Adds port to needed PortMap.
*/
template<class T> WritePort<T>::WritePort( PortMap<T>* portMap, std::string key, unsigned bandwidth, unsigned phoneOn)
{
    _key = key;
    _portMap = portMap;
    _bandwidth = bandwidth;
    _phoneOn = phoneOn;

    _portMap->addWritePort( _key, this);    
}

/*
 * Write method.
 *
 * First argument is the link to data.
 * Second argument is the cycle number.
*/
template<class T> void WritePort<T>::write( T* what, hostUInt64 cycle)
{
    if ( _data.size() < _bandwidth)
    {
        _data.push(what);
        _cycle.push(cycle); 
    }    
    else
    {
    // If port is overloaded, assert.
        critical( "Port '%s' is overloaded\n", _key.c_str());
    }
}

/*
 * Get data method.
 * It's not a const method, it takes element from queue.
*/
template<class T> T* WritePort<T>::getData()
{
    if ( _data.empty())
    {
    // If there's nothing in port, assert.
        critical( "No data in '%s'", _key.c_str());
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
 * Get phoneon method
*/
template<class T> unsigned WritePort<T>::getPhoneOn() const
{
    return _phoneOn;
}

/*
 * Read Port
*/
template<class T> class ReadPort: public log
{
    private:
        std::string _key;
        hostUInt64 _latency;
        WritePort<T>* _source;
        PortMap<T>* _portMap;        
    public:
        ReadPort<T>( PortMap<T>*, std::string, hostUInt64);
        void setSource( WritePort<T>*);
        int read( T**, hostUInt64) const;        
};

/*
 * Constructor
 *
 * First argument is the address of portMap.
 * Second argument is the connection key.
 * Third argument is the latency of port.
 *
 * Adds port to needed PortMap.
*/ 
template<class T> ReadPort<T>::ReadPort( PortMap<T>* portMap,std::string key, hostUInt64 latency)
{
    _key = key;
    _portMap = portMap;
    _latency = latency;
    
    portMap->addReadPort( _key, this);
}

/*
 * Read method
 *
 * First arguments is address, second is the number of cycle
 *
 * Compares current cycle with needed cycle (cycle of adding plus latency).
 * If current cycle is less than needed, returns 1;
 * If current cycle is equal or greater than needed, tries to return data address to first argument. (see WritePort::getData)
*/
template<class T> int ReadPort<T>::read( T** address, hostUInt64 cycle) const
{   
    if ( ( _source->getCycle() + _latency) <= cycle)
    {
        *address = _source->getData();
        return 0;
    }
    else
    {
        return -1;
    }
}

/*
 * Sets source WritePort.
*/
template<class T> void ReadPort<T>::setSource( WritePort<T>* source)
{
    _source = source;
}

/*
 * Map of ports
*/
template<class T> class PortMap: public log
{
    private:
        typedef std::list<ReadPort<T>* > ReadListType;
        typedef typename ReadListType::iterator ReadListTypeIt;
        struct Entry
        {
            WritePort<T>* writer;
            ReadListType readers;
        };
        typedef std::map<std::string, Entry> MapType;
        typedef typename MapType::iterator MapTypeIt;
        MapType _map;
    public:
        void addWritePort( std::string, WritePort<T>*);
        void addReadPort( std::string, ReadPort<T>*);        
        
        void init();
}; 

/*
 * Adding WritePort to the map.
*/
template<class T> void PortMap<T>::addWritePort( std::string key, WritePort<T>* pointer)
{
    if ( _map.find( key) == _map.end())
    {
        Entry entry;
        entry.writer = 0;
        entry.readers.resize(0);
        _map.insert( std::pair<std::string, Entry>( key, entry));
    }
    _map[key].writer = pointer;
}

/*
 * Adding ReadPort to the map.
*/
template<class T> void PortMap<T>::addReadPort( std::string key, ReadPort<T>* pointer)
{
    if ( _map.find(key) == _map.end())
    {
        Entry entry;
        entry.writer = 0;
        entry.readers.resize(0);        
        _map.insert( std::pair<std::string, Entry>( key, entry));    
    }
    _map[key].readers.push_front( pointer);
}

/*
 * Initialize map of ports.
 *
 * Iterates all map and sets _source field on readPorts.
 * If there're any unconnected ports, asserts.
 * If there're any overloaded WritePort, also asserts.
*/ 
template<class T> void PortMap<T>::init()
{
    for ( MapTypeIt it = _map.begin(); it != _map.end(); ++it)
    {
        if ( !it->second.writer)
        {
           critical( "No WritePort for '%s' key", it->first.c_str());
        }
        
        WritePort<T>* writer = it->second.writer;
        size_t size = it->second.readers.size();
        
        if ( !size)
        {
           critical( "No ReadPorts for '%s' key", it->first.c_str());
        }
        if ( size > writer->getPhoneOn())
        {
           critical( "Too much ReadPorts for '%s' key", it->first.c_str());
        }
        for ( ReadListTypeIt jt = it->second.readers.begin(); jt != it->second.readers.end(); ++jt)
        {
            (*jt)->setSource(writer);
        }
    }
}
#endif // PORTS_H