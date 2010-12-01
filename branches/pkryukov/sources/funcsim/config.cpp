/**
 * config.cpp - Implementation of Config class
 * @author Pavel Kryukov
 * Copyright 2010 MDSP team
 */

#include "log.h"
#include "config.h"
#include "defines.h"

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

#include <boost/program_options.hpp>

using namespace std;

/* constructors */
Config::Config()
{
    this->binaryFilename = new string;
    this->elfFilename = new string;
    this->outputFilename = new string;
}
Config::~Config()
{
    delete this->binaryFilename;
	delete this->elfFilename;
    delete this->outputFilename;
}

/* basic method */
int Config::handleArgs( int argc, char** argv)
{
    namespace po = boost::program_options;

    po::options_description description( "allowed options");

    description.add_options()
        ( "binary,b", po::value<string>(), "choose binary")
        ( "elf,e", po::value<string>(), "choose ELF")
        ( "numsteps,n", po::value<int>(), "choose numsteps")
	    ( "disasm,d", "disassembly")
	    ( "print-reg-state,r","dump registers")
	    ( "print-mem-state,m","dump memory")
	    ( "output-file,o",po::value<string>(),"output file")
	    ( "trace,t","tracing");

    po::variables_map options;

     try 
     {
         po::store(po::parse_command_line(argc, argv, description), options);
     } 
     catch (const std::exception& e) 
     {
         this->critical( "Command line error:", e.what());
         return 0;
     }
    

    /* parsing input file name */
    if ( options.count( "binary") == 1 ) 
    {
        *binaryFilename = options["binary"].as<string>();
        this->inputType = true;
    }
    else
    {
        if ( options.count( "binary") > 1)
		{
	        this->critical( "Key -b is used twice");
		}
		if ( options.count( "elf") == 1)
        {
            *elfFilename = options["elf"].as<string>();
            this->inputType = false;
        }
        else
        {
            if ( options.count( "elf") > 1)
	        {
		         this->critical( "Key -e is used twice");
	        }
		    else
            {
                this->critical( "No input file");
            }
        }
    }

    /* parsing output-file */
    switch ( options.count( "output-file"))
    {
        case 1: 
            *outputFilename = options[ "output-file"].as<string>();
            this->outputToFile = true;
            break;
        case 0:
            this->outputToFile = false;
            break;
        default:
            this->critical( "-o is used twice");
            break;
    }
    
	/* parsing steps count */

    switch ( options.count( "numsteps"))
    {
        case 1: 
            this->numSteps = options["numsteps"].as<int>();
            break;
        case 0:
            this->numSteps = -1;
            break;
        default:
            this->critical( "-n is used twice");
            break;
    }
    
	/* parsing some parameters */
    this->disassembler = ( options.count("disassembly") != 0);
    this->dumpRegisters = ( options.count("print-reg-state") != 0);
    this->dumpMemory = ( options.count("print-mem-state") != 0);
    this->tracing = ( options.count("trace") != 0);
	
    return 0;
}

/* get methods */

string Config::getBinaryFilename() const 
{
	return *this->binaryFilename;
}

string Config::getOutputFilename() const
{
	return *this->outputFilename;
}

string Config::getElfFilename() const
{
	return *this->elfFilename;
}

int Config::getNumSteps() const
{
	return this->numSteps;
}

bool Config::getInputType() const
{
	return this->inputType;
}

bool Config::getDisassembler() const
{
	return this->disassembler;
}

bool Config::getDumpMemory() const
{
	return this->dumpMemory;
}

bool Config::getDumpRegisters() const
{
	return this->dumpRegisters;
}

bool Config::getTracing() const
{
	return this->tracing;
}

bool Config::getOutputToFile() const
{
	return this->outputToFile;
}
 