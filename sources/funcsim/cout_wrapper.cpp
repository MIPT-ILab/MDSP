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

