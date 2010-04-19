
/**
 * config.h - class for analysing and handling of inputed arguments 
 * @author Dmitry Lukiyanchuk
 * Copyright 2009 MDSP team
 */

#ifndef CONFIG_H
#define CONFIG_H

#include <string>
using namespace std;

class Config
{
private:
    /* variables */
    string* input_filename;
    string* log_filename;

    /* auxiliary methods */
    bool checkFileExisting(const char* filename) const;
    bool checkSymbols(const char* filename) const;

public:
    /* constructors */
    Config();
    ~Config();

    /* methods */
    int handleArgs( int argc, char** argv);
    string getInputFilename() const;
    string getLogFilename() const;
};

#endif  // CONFIG_H
