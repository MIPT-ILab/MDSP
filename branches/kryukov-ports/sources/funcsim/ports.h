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
#include <vector>
#include <string>

#include "log.h"
#include "types.h"

template<class T> class PortMap;

/*
 * Port class
*/
template<class T> class Port: public log
{
    protected:
        // Key of port
        std::string _key;
    public:    
        // Static ports Map to connect ports between for themselves;
        static PortMap<T>* _portMap;
        
        // Constructor of port
        Port<T>( std::string);
};

/*
 * Init a map of ports (see bottom of file
*/
template<class T> PortMap<T>* Port<T>::_portMap = new PortMap<T>;

/*
 * Constructor
*/
template<class T> Port<T>::Port( std::string key)
{
    _key = key;
}

/*
 * WritePort
 */
template<class T> class WritePort: public Port<T>
{
    private:
        // Number of tokens that can be added in one cycle;
        hostUInt32 _bandwidth;
        
        // Number of reader that can read from this port
        hostUInt32 _fanout;
        
        // Cage consists of data and counter of reading data
        struct Cage
        {   
            T* data;
            hostUInt32 readCounter;
        };
        
        // Type of queue of data which were added in same cycle
        typedef std::queue<Cage> SameCycleData;
        
        // Type of vector of SameCycleData for every cycle
        typedef typename std::vector<SameCycleData*> DataVector;
        
        // DataVector includes all added data
        DataVector _dataVector;
        
        // Variables for counting token in the last cycle
        // _lastCycle is synonime for _dataVector.size()-1
        hostUInt32 _lastCycle;
        
        // _writeCounter is synonime for _dataVector[_lastCycle].size()
        hostUInt32 _writeCounter;
    public:
        // Constructor
        WritePort<T>( std::string, hostUInt32, hostUInt32);
        
        // Write Method
        void write( T*, hostUInt64);
        
        // Get Method (is called by ReadPort)
        T* getData( hostUInt64);
};

/*
 * Constructor
 *
 * First argument is key which is used to connect ports.
 * Second is the bandwidth of port (how much data items can port hold).
 * Third is maximum number of ReadPorts.
 *
 * Adds port to needed PortMap.
*/
template<class T> WritePort<T>::WritePort( std::string key, hostUInt32 bandwidth, hostUInt32 fanout):
    Port<T>::Port( key)
{
    _bandwidth = bandwidth;
    _fanout = fanout;
    
    _dataVector.resize(1);
    _dataVector[0] = new SameCycleData;
    
    _lastCycle = 0;
    _writeCounter = 0;

    this->_portMap->addWritePort( this->_key, this);    
}

/*
 * Write method.
 *
 * First argument is the link to data.
 * Second argument is the current cycle number.
*/
template<class T> void WritePort<T>::write( T* what, hostUInt64 cycle)
{
    if (_lastCycle != cycle)
    {
        // If cycle number was changed, 
        _lastCycle = cycle;
        _writeCounter = 0;
        
        // Creating new vector element for current cycle    
        _dataVector.resize(_lastCycle+1);
        _dataVector[cycle] = new SameCycleData;
    }
    if (_writeCounter < _bandwidth)
    {
    // If we can add something more on that cycle, adding
        Cage cage;
        cage.data = what;
        cage.readCounter = 0;
        _dataVector[cycle]->push(cage);
        
        _writeCounter++;
    }
    else
    {
    // If we overloaded port's bandwidth, assert
        critical("Port %s is overloaded\n", this->_key.c_str());
    }
}

/*
 * Get data method.
 * It's not a const method, it takes element from queue.
 *
 * Argument is cycle number of adding that we want to get
 *
 * If there was nothing added on this cycle, returns zero pointer.
*/
template<class T> T* WritePort<T>::getData( hostUInt64 cycle)
{
    // If there's nothing added on this cycle, return zero
    if (
        ( _dataVector.size() < cycle) || 
        ( _dataVector[cycle] == 0) || 
        ( _dataVector[cycle]->empty())
       )
    {
        return 0;
    }
    Cage buffer = _dataVector[cycle]->front();
    if (_dataVector[cycle]->front().readCounter == _fanout)
    {
    // If there was 'readCounter' readings, removing
        _dataVector[cycle]->pop();
        if (_dataVector[cycle]->empty())
        {
            delete _dataVector[cycle];
            _dataVector[cycle] = 0;
        }
    }
    else
    {
    // Otherwise, writes about new reading
        _dataVector[cycle]->front().readCounter++;
    }
    return _dataVector[cycle]->front().data;
}


/*
 * Read Port
*/
template<class T> class ReadPort: public Port<T>
{
    private:
        // Latency is the number of cycles after which we may take data from port.
        hostUInt64 _latency;
        
        // Pointer to source-WritePort
        WritePort<T>* _source;       
    public:
        // Constructor
        ReadPort<T>( std::string, hostUInt64);
        
        // setSource method. Used by PortMap
        void setSource( WritePort<T>*);
        
        // Read method
        hostSInt8 read( T**, hostUInt64) const;        
};

/*
 * Constructor
 *
 * First argument is the connection key.
 * Second argument is the latency of port.
 *
 * Adds port to needed PortMap.
*/ 
template<class T> ReadPort<T>::ReadPort( std::string key, hostUInt64 latency):
    Port<T>::Port( key)
{
    _latency = latency;
    _source = 0;
    
    this->_portMap->addReadPort( this->_key, this);
}

/*
 * Read method
 *
 * First arguments is address, second is the number of cycle
 *
 * Counts cycle of adding data and call to WritePort get method
*/
template<class T> hostSInt8 ReadPort<T>::read( T** address, hostUInt64 cycle) const
{   
    if ( !_source)
    {
        this->critical("Ports was not initialized");
    }
    T* result = _source->getData( cycle - _latency);
    if ( result)
    {
        *address = result; 
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
        // List of readers type and iterator type
        typedef std::list<ReadPort<T>* > ReadListType;
        typedef typename ReadListType::iterator ReadListTypeIt;
        
        // Entry of portMap — one writer and list of readers
        struct Entry
        {
            WritePort<T>* writer;
            ReadListType readers;
        };
        
        // Type of map of Entry
        typedef std::map<std::string, Entry> MapType;
        typedef typename MapType::iterator MapTypeIt;
        
        // Map itself
        MapType _map;
    public:
        // Adding methods
        void addWritePort( std::string, WritePort<T>*);
        void addReadPort( std::string, ReadPort<T>*);        
        
        // Init method
        void init();
}; 

/*
 * Adding WritePort to the map.
*/
template<class T> void PortMap<T>::addWritePort( std::string key, WritePort<T>* pointer)
{
    if ( _map.find( key) == _map.end())
    {
    // If there's no record in this map, create it.
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
    // If there's no record in this map, create it.
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
        for ( ReadListTypeIt jt = it->second.readers.begin(); jt != it->second.readers.end(); ++jt)
        {
            (*jt)->setSource(writer);
        }
    }
}
#endif // PORTS_H