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

/* basic method */
int Config::handleArgs( int argc, char** argv)
{
    namespace po = boost::program_options;

    po::options_description description( "allowed options");

    description.add_options()
        ( "binary,b", po::value<string>(), "Select binary file")
        ( "elf,e", po::value<string>(), "Select ELF file")
        ( "numsteps,n", po::value<int>(), "Select numsteps")
        ( "disasm,d", "Print disassembly")
        ( "print-reg-state,r", "Dump registers")
        ( "print-mem-state,m", "Dump memory")
        ( "output-file,o",po::value<string>(), "Select output file")
        ( "trace,t", "Print tracing")
        ( "help,h", "Print this help message");

    po::positional_options_description posDescription;
	
	posDescription.add( "binary",1);
		
    po::variables_map vm;

    try 
    {
        po::store(po::command_line_parser(argc, argv).
	                                  options(description).
									  positional(posDescription).
									  run(), 
									  vm);
	    po::notify(vm);
    } 
    catch (const std::exception& e) 
    {
        (void)e;
        cout << description << endl;
        exit(0);
    }
    
    /* parsing help */
    if ( vm.count( "help") )
    {
         cout << "Functional simulator of multimedia digital signal processor." << endl;
         cout << "Version: 0.2" << endl << endl;
         cout << description << endl;
         exit(0);
    }

    /* parsing input file name */
    if ( vm.count( "binary") == 1 ) 
    {
        binaryFilename = vm["binary"].as<string>();
        this->inputType = true;
    }
    else
    {
        if ( vm.count( "binary") > 1)
        {
            cout << "Key -b is used twice" << endl;
            cout << endl;
            cout << description << endl;
            exit(0);
        }
        if ( vm.count( "elf") == 1)
        {
            elfFilename = vm["elf"].as<string>();
            this->inputType = false;
        }
        else
        {
            if ( vm.count( "elf") > 1)
            {
                cout << "Key -e is used twice" << endl;
                cout << endl;
                cout << description << endl;
                exit(0);
            }
            else
            {
                cout << "No input file" << endl;
                cout << endl;
                cout << description << endl;
                exit(0);
            }
        }
    }

    /* parsing output-file */
    switch ( vm.count( "output-file"))
    {
        case 1: 
            outputFilename = vm[ "output-file"].as<string>();
            this->outputToFile = true;
            break;
        case 0:
            this->outputToFile = false;
            break;
        default:
            cout << "-o is used twice" << endl;
            cout << endl;
            cout << description << endl;
            exit(0);
            break;
    }
    
    /* parsing steps count */

    switch ( vm.count( "numsteps"))
    {
        case 1: 
            this->numSteps = vm["numsteps"].as<int>();
            break;
        case 0:
            this->numSteps = -1;
            break;
        default:
            cout << "-n is used twice" << endl;
            cout << endl;
            cout << description << endl;
            exit(0);
            break;
    }
    
    /* parsing some parameters */
    this->disassembler = ( vm.count("disasm") != 0);
    this->dumpRegisters = ( vm.count("print-reg-state") != 0);
    this->dumpMemory = ( vm.count("print-mem-state") != 0);
    this->tracing = ( vm.count("trace") != 0);
    
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
 