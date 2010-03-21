/**
 * cout_wrapper.cpp - Implementation of stdout wrapper
 * @author Alexander Potashev
 * Copyright 2010 MDSP team
 */

#include <stdarg.h>
#include <stdio.h>
#include <iostream>
#include <sstream>

std::ostream *cout_handler = &std::cout;
std::stringstream *cout_buffer = NULL;
bool cout_standard_wrapper = true;

void setStandardCoutHandler()
{
    if (!cout_standard_wrapper)
    {
        cout_handler = &std::cout;
        cout_standard_wrapper = true;
    }
}

void setTestingCoutHandler()
{
    if (cout_standard_wrapper)
    {
        setStandardCoutHandler();

        if (cout_buffer != NULL)
            delete cout_buffer;
        cout_handler = cout_buffer = new std::stringstream(std::ostringstream::out);

        cout_standard_wrapper = false;
    }
}

std::string getTestingCoutBuffer()
{
    return cout_buffer->str();
}

int printfHandler(const char *format, ...)
{
    va_list params;
    int ret;
    static char buffer[1024];

    va_start(params, format);

    if (cout_standard_wrapper)
    {
        ret = vprintf(format, params);
    }
    else
    {
        ret = vsnprintf(buffer, sizeof(buffer), format, params);
        (*cout_handler) << buffer;
    }

    va_end(params);
    return ret;
}

