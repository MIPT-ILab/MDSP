/**
 * config.h - class for analysing and handling of inputed arguments 
 * @author Dmitry Lukiyanchuk
 * Copyright 2009 MDSP team
 */

#ifndef CONFIG_H
#define CONFIG_H

class Config
{
private:
    /* static variables */
    static const unsigned short int version_size = 10;
    static const unsigned short int file_name_size = 80;
    /* variables */
    int argc;
    char** argv;
    char input_filename[file_name_size];
    char log_filename[file_name_size];
    char version[version_size];

    /* auxiliary methods */
    bool checkFileExisting(const char* filename) const;
    bool checkSymbols(const char* filename) const;

public:
    /* constructors */
    Config();
    Config( const int argc, char** argv);
    ~Config();

    /* methods */
    int handleArgs();
    char* getInputFilename();
    char* getLogFilename();
};

#endif  // CONFIG_H
