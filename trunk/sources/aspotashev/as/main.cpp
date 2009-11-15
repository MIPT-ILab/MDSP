
#include <iostream>

#include "tokenan.h"
#include "semantican.h"
#include "assembler.h"


int main()
{
    TokenAn *tokenan = new TokenAn( "1.S");
    std::vector<Token *> tokens = tokenan->run();

/*    for ( int i = 0; i < (int)tokens.size(); i ++)
    {
        std::cout << "tokens[" << i << "]: ";
        tokens[i]->dump();
        std::cout << std::endl;
    }*/

    SemanticAn *seman = new SemanticAn( tokens);
    std::vector<SemanticUnit *> units = seman->run();

/*    for ( int i = 0; i < (int)units.size(); i ++)
    {
        std::cout << "units[" << i << "]: ";
        units[i]->dump();
        std::cout << std::endl;
    }*/

    Assembler *as = new Assembler( units);
    std::map<unsigned int, hostUInt8> image = as->run();

    unsigned int image_sz = image.rbegin()->first + 1;

    FILE *f = fopen( "a.out", "wb");
    for ( unsigned int i = 0; i < image_sz; i ++)
    {
        hostUInt8 x = 0;
        if ( image.find(i) != image.end())
        {
            x = image[i];
        }

        assert( fwrite( &x, 1, 1, f) == 1);
    }
    fclose( f);

    return 0;
}

