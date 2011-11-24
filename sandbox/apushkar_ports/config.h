
/**
 * config.h - class for analysing and handling of inputed arguments
 * @author Pavel Kryukov
 * Copyright 2010 MDSP team
 */

#ifndef CONFIG_H
#define CONFIG_H

#include "log.h"

#include <string>
using namespace std;

class Config: public log
{
private:
    /* variables */
    string binaryFilename;
    string elfFilename;
    string outputFilename;

    /* if numSteps is equal -1, it means that there is no limit of simulation */
    int numSteps;
    
    /*  if InputType is true, input is binary, otherwise it's ELF*/
    bool inputType;
    bool disassembler;
    bool dumpRegisters;
    bool dumpMemory;
    bool tracing;
    bool outputToFile;
    
    void usage();
public:
    /* constructors */
    Config();
    ~Config();

    /* methods */
    int handleArgs( int argc, char** argv);

    /* get methods */
    string getBinaryFilename() const;
    string getOutputFilename() const;
    string getElfFilename() const;

    int getNumSteps() const;

    bool getInputType() const;
    bool getDisassembler() const;
    bool getDumpMemory() const;
    bool getDumpRegisters() const;
    bool getTracing() const;
    bool getOutputToFile() const;

};

#endif  // CONFIG_H
