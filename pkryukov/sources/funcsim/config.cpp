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

}
Config::~Config()
{

}

void Config::usage()
{
    /* Print help information and stop program */
    cout << "Usage:" << endl;
    cout << endl;
    cout << "\t" << "--binary <file>, -b <file> - instructs simualtor to load raw machine code from file." << endl;
    cout << "\t" << "--elf,-e - load binary ELF file sections to memory." << endl;
    cout << "\t" << "--num-steps,-n - do only specified amount of steps and then exit."; 
    cout << "By default core runs until it encounters hlt instruction or there is a simulation error." << endl;
    cout << "\t" << "--disasm,-d - print disassembly of every current instruction." << endl;
    cout << "\t" << "--print-reg-state,-r - dump register state after simulation has finished." << endl;
    cout << "\t" << "--print-mem-state,-m - dump memory state after simulation has finished." << endl;
    cout << "\t" << "--output-file,-o - redirect normal output to the given file. By default we print to stdout." << endl;
    cout << "\t" << "--trace,-t - report all architectural state changes (register modified, memory written etc)" << endl;
    cout << "\t" << "--help,-h - print help with this paragraph." << endl;
    exit(0); 
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
	    ( "trace,t","tracing")
        ( "help,h","help message");


    po::variables_map options;

     try 
     {
         po::store(po::parse_command_line(argc, argv, description), options);
     } 
     catch (const std::exception& e) 
     {
         usage();
     }
    
    /* parsing help */
    if ( options.count( "help") )
    {
         cout << "Functional simulator of multimedia digital signal processor." << endl;
         cout << "Version: 0.1" << endl;
         usage();
    }

    /* parsing input file name */
    if ( options.count( "binary") == 1 ) 
    {
        binaryFilename = options["binary"].as<string>();
        this->inputType = true;
    }
    else
    {
        if ( options.count( "binary") > 1)
		{
	        cout << "Key -b is used twice" << endl;
            cout << endl;
            usage();
		}
		if ( options.count( "elf") == 1)
        {
            elfFilename = options["elf"].as<string>();
            this->inputType = false;
        }
        else
        {
            if ( options.count( "elf") > 1)
	        {
		        cout << "Key -e is used twice" << endl;
                cout << endl;
                usage();
	        }
		    else
            {
                cout << "No input file" << endl;
                cout << endl;
                usage();
            }
        }
    }

    /* parsing output-file */
    switch ( options.count( "output-file"))
    {
        case 1: 
            outputFilename = options[ "output-file"].as<string>();
            this->outputToFile = true;
            break;
        case 0:
            this->outputToFile = false;
            break;
        default:
            cout << "-o is used twice" << endl;
            cout << endl;
            usage();
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
            cout << "-n is used twice" << endl;
            cout << endl;
            usage();
            break;
    }
    
	/* parsing some parameters */
    this->disassembler = ( options.count("disasm") != 0);
    this->dumpRegisters = ( options.count("print-reg-state") != 0);
    this->dumpMemory = ( options.count("print-mem-state") != 0);
    this->tracing = ( options.count("trace") != 0);
	
    return 0;
}

/* get methods */

string Config::getBinaryFilename() const 
{
	return this->binaryFilename;
}

string Config::getOutputFilename() const
{
	return this->outputFilename;
}

string Config::getElfFilename() const
{
	return this->elfFilename;
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
 