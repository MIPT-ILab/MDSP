
#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include <iostream>

#include "tokenan.h"
#include "ident.h"

TokenAn::TokenAn( const char *filename)
{
    read_file_contents( filename);
}

void TokenAn::init_file_length( const char *filename)
{
    FILE *f = fopen( filename, "r");
    fseek( f, 0, SEEK_END);
    filelength = ftell( f);
    fclose( f);
}

void TokenAn::read_file_contents( const char *filename)
{
    init_file_length( filename);

    data = new char[filelength + 1];
    data[filelength] = '\0';

    FILE *f = fopen( filename, "r");
    if ( fread( data, 1, filelength, f) != filelength)
        throw;
    
    fclose( f);

//    for ( int i = 0; i < filelength; i ++)
//        printf( "f[%d] = %d\n", i, (int)data[i]);
}

std::vector<TokenAn::Token *> TokenAn::run()
{
    ptr = data;
    std::vector<TokenAn::Token *> res;

    while ( *ptr != '\0')
    {
        skip_spaces();

        if ( *ptr == '%' || isidstart( *ptr))
        {
            char *id_start = ptr ++;
            while ( isidchar( *ptr))
                ptr ++;

            res.push_back( TokenAn::Token::createId(
                std::string( id_start, ptr - id_start)));
        }
        else if ( *ptr == ',')
        {
            res.push_back( TokenAn::Token::createScalar( TOKEN_COMMA));
            ptr ++;
        }
        else if ( *ptr == '(')
        {
            res.push_back( TokenAn::Token::createScalar( TOKEN_LBRACKET));
            ptr ++;
        }
        else if ( *ptr == ')')
        {
            res.push_back( TokenAn::Token::createScalar( TOKEN_RBRACKET));
            ptr ++;
        }
        else if ( *ptr == ':')
        {
            res.push_back( TokenAn::Token::createScalar( TOKEN_COLON));
            ptr ++;
        }
        else if ( *ptr == '$' && isdigit( ptr[1]))
        {
            ptr ++;

            int iVal = 0;
            sscanf( ptr, "%d", &iVal);
            res.push_back( TokenAn::Token::createConstInt( iVal));

            while ( isdigit( *ptr))
                ptr ++;
        }
        else if ( *ptr == '\r' && ptr[1] == '\n') // DOS
        {
            res.push_back( TokenAn::Token::createEos());
            ptr += 2;
        }
        else if ( *ptr == '\n' || *ptr == '\r') // Unix, Mac
        {
            res.push_back( TokenAn::Token::createEos());
            ptr ++;
        }
        else if ( *ptr == '\0')
        {
            res.push_back( TokenAn::Token::createEos());
//            res.push_back( TokenAn::Token::createScalar( TOKEN_EOF));
        }
        else
        {
            std::cerr << "bad char: " << *ptr <<
                " (code: " << (int)*ptr << ")" << std::endl;
            assert(0);
        }
    }

    return res;
}

void TokenAn::skip_spaces()
{
    while ( *ptr != '\0' && isblank( *ptr))
        ptr ++;
}

TokenAn::Token *TokenAn::Token::createId( const std::string id_string)
{
    TokenAn::Token *res = new TokenAn::Token;
    res->type = TOKEN_ID;
    res->sVal = id_string;

    return res;
}

TokenAn::Token *TokenAn::Token::createConstInt( int iVal)
{
    TokenAn::Token *res = new TokenAn::Token;
    res->type = TOKEN_CONST_INT;
    res->iVal = iVal;

    return res;
}

TokenAn::Token *TokenAn::Token::createScalar( enum TOKEN_TYPE type)
{
    TokenAn::Token *res = new TokenAn::Token;
    res->type = type;

    return res;
}

TokenAn::Token *TokenAn::Token::createEos() // end of line
{
    return createScalar( TOKEN_EOS);
}

void TokenAn::Token::dump()
{
    switch ( type)
    {
    case TOKEN_ID:        std::cout << sVal; break;
    case TOKEN_EOS:       std::cout << "--------------- (\\n)"; break;
    case TOKEN_COMMA:     std::cout << ","; break;
    case TOKEN_LBRACKET:  std::cout << "("; break;
    case TOKEN_RBRACKET:  std::cout << ")"; break;
    case TOKEN_CONST_INT: std::cout << iVal; break;
    case TOKEN_COLON:     std::cout << ":"; break;
    default: throw;
    }
}

