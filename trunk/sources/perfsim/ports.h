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
template<class T> class ReadPort;
template<class T> class WritePort;

/*
 * Port class
*/
template<class T> class Port: public log
{
    protected:
        // Key of port
        std::string _key;
        
        // Init flag
        bool _init;
    public:    
        // Static ports Map to connect ports between for themselves;
        static PortMap<T>* portMap;
        
        // Call of initialization of portMap
        static inline void init()
        {
            portMap->init();
        };
        
        // Call of finding lost tokens in ports
        static inline void lost( hostUInt32 cycle)
        {
            portMap->lost( cycle);
        };
        
        // Sets init flag as true.
        void setInit();
        
        // Constructor of port
        Port<T>( std::string);
};

/*
 * Init a map of ports (see bottom of file)
*/
template<class T> PortMap<T>* Port<T>::portMap = new PortMap<T>;

/*
 * Constructor
*/
template<class T> Port<T>::Port( std::string key)
{
    _key = key;
    _init = false;
}

/*
 * Setting init flag as true.
*/
template<class T> void Port<T>::setInit()
{
    _init = true;
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

        // List of readers
        typedef std::list<ReadPort<T>* > ReadListType;
        typedef typename ReadListType::iterator ReadListIt;
        ReadListType* _destinations;
        
        // Variables for counting token in the last cycle
        hostUInt32 _lastCycle;
        hostUInt32 _writeCounter;
        
    public:
        // Constructor
        WritePort<T>( std::string, hostUInt32, hostUInt32);
        
        // Write Method
        void write( T, hostUInt64);
        
        // Addes destination ReadPort to list
        void setDestination( ReadListType*);
        
        // Returns fanout for test of connection
        hostUInt32 getFanout() const;
};

/*
 * Constructor
 *
 * First argument is key which is used to connect ports.
 * Second is the bandwidth of port (how much data items can port get during one cycle).
 * Third is maximum number of ReadPorts.
 *
 * Adds port to needed PortMap.
*/
template<class T> WritePort<T>::WritePort( std::string key, hostUInt32 bandwidth, hostUInt32 fanout):
    Port<T>::Port( key)
{
    _bandwidth = bandwidth;
    _fanout = fanout;
    
    _lastCycle = 0;
    _writeCounter = 0;

    this->portMap->addWritePort( this->_key, this);    
}

/*
 * Write method.
 *
 * First argument is data itself.
 * Second argument is the current cycle number.
 * 
 * Forwards data to all connected ReadPorts 
 *
 * If port wasn't initialized, asserts.
 * If port is overloaded by bandwidth (more than _bandwidth token during one cycle, asserts).
*/
template<class T> void WritePort<T>::write( T what, hostUInt64 cycle)
{
    if ( !this->_init) 
    {
    // If no init, asserts
        critical( "%s WritePort was not initializated", this->_key.c_str());
        return;
    }
    if ( _lastCycle != cycle)
    {
        // If cycle number was changed, zero counter.
        _lastCycle = cycle;
        _writeCounter = 0;
    }
    if ( _writeCounter < _bandwidth)
    {
    // If we can add something more on that cycle, forwarding it to all ReadPorts.
        _writeCounter++;
        for ( ReadListIt it = _destinations->begin(); it != _destinations->end(); ++it)
        {
            (*it)->pushData(what, cycle);
        }
    }
    else
    {
    // If we overloaded port's bandwidth, assert
        critical( "Port '%s' is overloaded by bandwidth\n", this->_key.c_str());
    }
}

/*
 * Shows to WritePort list of his ReadPorts (from PortMap)
*/
template<class T> void WritePort<T>::setDestination(ReadListType* pointer)
{
    _destinations = pointer;
}

/*
 * Returns fanout
*/
template<class T> hostUInt32 WritePort<T>::getFanout() const
{
    return _fanout;
}

/*
 * Read Port
*/
template<class T> class ReadPort: public Port<T>
{
    private:
        // Latency is the number of cycles after which we may take data from port.
        hostUInt64 _latency;
        
        // Queue of data that should be released
        struct DataCage
        {
            T data;
            hostUInt64 cycle;
        };
        typedef std::queue<DataCage> DataQueue;
        DataQueue _dataQueue;
 
    public:
        // Constructor
        ReadPort<T>( std::string, hostUInt64);
        
        // Read method
        hostSInt8 read( T*, hostUInt64);

        // Pushes data from WritePort
        void pushData( T, hostUInt64);
        
        // Tests if there is any ungot data
        bool selfTest( hostUInt64, hostUInt64*) const;
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
    
    this->portMap->addReadPort( this->_key, this);
}

/*
 * Read method
 *
 * First arguments is address, second is the number of cycle
 *
 * If there's nothing in port to give, returns -1
 * If succesful, returns 0
 * If uninitalized, asserts
*/
template<class T> hostSInt8 ReadPort<T>::read( T* address, hostUInt64 cycle)
{   
    if ( !this->_init) 
    {
        critical( "%s ReadPort was not initializated", this->_key.c_str());
        return -2;
    }
    if ( _dataQueue.empty()) return -1;
    if ( _dataQueue.front().cycle == cycle)
    {
        *address = _dataQueue.front().data;
        _dataQueue.pop();
        return 0;
    }
    else
    {
        return -1;
    }
}

/*
 * Receive data from WritePort.
*/
template<class T> void ReadPort<T>::pushData( T what, hostUInt64 cycle)
{
    DataCage buffer;
    buffer.data = what;
    buffer.cycle = cycle + _latency;
    _dataQueue.push( buffer);
}

/*
 * Tests if there is any data that can not be used ever.
 *
 * Returns cycle number when data was added to WritePort.
*/
template<class T> bool ReadPort<T>::selfTest(hostUInt64 cycle, hostUInt64* wantedCycle) const
{
    if ( _dataQueue.empty()) return true;
    if ( _dataQueue.front().cycle < cycle)
    {
        *wantedCycle = _dataQueue.front().cycle - _latency;
        return false;
    }
    return true;
}

/*
 * Map of ports
*/
template<class T> class PortMap: public log
{
    private:       
        typedef std::list<ReadPort<T>* > ReadListType;
        typedef typename ReadListType::iterator ReadListTypeIt;
        
        // Entry of portMap � one writer and list of readers
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
        
        // Finding lost elements
        void lost( hostUInt64);
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
    else
    {
        if ( !_map[key].writer)
        {
        // Warning of double using of same key for WritePort
            warning( "Reusing of '%s' key for WritePort. Last WritePort will be used.", key.c_str());
        }
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
 * Iterates all map and sets destination list to all writePorts
 * If there're any unconnected ports or fanout overload, asserts.
 * If ther's fanout underload, warnings.
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
        hostUInt32 readersCounter = it->second.readers.size();
        if ( !readersCounter)
        {
           critical( "No ReadPorts for '%s' key", it->first.c_str());
           return;
        }
        if ( readersCounter > writer->getFanout())
        {
            critical( "%s WritePort is overloaded by fanout", it->first.c_str());
            return;
        }
        if ( readersCounter < writer->getFanout())
        {
            warning( "%s WritePort is underloaded by fanout", it->first.c_str());
        }
        it->second.writer->setDestination( &(it->second.readers));

        // Initializing ports with setting their init flags.
        for ( ReadListTypeIt jt = it->second.readers.begin(); jt != it->second.readers.end(); ++jt)
        {
            (*jt)->setInit();
        }
        writer->setInit();        
    }
}

/*
 * Function for founding lost elements at port
 *
 * Argument is the number of current cycle.
 * If some token couldn't be get in future, warnings
*/
template<class T> void PortMap<T>::lost( hostUInt64 cycle)
{
    for ( MapTypeIt it = _map.begin(); it != _map.end(); ++it)
    {
        for ( ReadListTypeIt jt = it->second.readers.begin(); jt != it->second.readers.end(); ++jt)
        {
            hostUInt64 addCycle;
            if ( !(*jt)->selfTest( cycle, &addCycle))
            {
                warning( "In %s port data was added at %d clock and will not be readed\n", it->first.c_str(), addCycle);
            }
        }
    }
}    
    
#endif // PORTS_H