
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
    if ( fread( data, 1, filelength, f) != (size_t)filelength)
        throw;
    
    fclose( f);

//    for ( int i = 0; i < filelength; i ++)
//        printf( "f[%d] = %d\n", i, (int)data[i]);
}

std::vector<Token *> TokenAn::run()
{
    ptr = data;
    std::vector<Token *> res;

    while ( *ptr != '\0')
    {
        skip_spaces();

        if ( *ptr == '%' || isidstart( *ptr))
        {
            char *id_start = ptr ++;
            while ( isidchar( *ptr))
                ptr ++;

            res.push_back( Token::createId(
                std::string( id_start, ptr - id_start)));
        }
        else if ( *ptr == ',')
        {
            res.push_back( Token::createScalar( TOKEN_COMMA));
            ptr ++;
        }
        else if ( *ptr == '(')
        {
            res.push_back( Token::createScalar( TOKEN_LBRACKET));
            ptr ++;
        }
        else if ( *ptr == ')')
        {
            res.push_back( Token::createScalar( TOKEN_RBRACKET));
            ptr ++;
        }
        else if ( *ptr == ':')
        {
            res.push_back( Token::createScalar( TOKEN_COLON));
            ptr ++;
        }
        else if ( *ptr == '$' && isdigit( ptr[1]))
        {
            ptr ++;

            int iVal = 0;
            sscanf( ptr, "%d", &iVal);
            res.push_back( Token::createConstInt( iVal));

            while ( isdigit( *ptr))
                ptr ++;
        }
        else if ( *ptr == '\r' && ptr[1] == '\n') // DOS
        {
            res.push_back( Token::createEos());
            ptr += 2;
        }
        else if ( *ptr == '\n' || *ptr == '\r') // Unix, Mac
        {
            res.push_back( Token::createEos());
            ptr ++;
        }
        else if ( *ptr == '\0')
        {
            res.push_back( Token::createEos());
//            res.push_back( Token::createScalar( TOKEN_EOF));
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

Token *Token::createId( const std::string id_string)
{
    Token *res = new Token;
    res->tokenType = TOKEN_ID;
    res->sVal = id_string;

    return res;
}

Token *Token::createConstInt( int iVal)
{
    Token *res = new Token;
    res->tokenType = TOKEN_CONST_INT;
    res->iVal = iVal;

    return res;
}

Token *Token::createScalar( enum TOKEN_TYPE type)
{
    Token *res = new Token;
    res->tokenType = type;

    return res;
}

Token *Token::createEos() // end of line
{
    return createScalar( TOKEN_EOS);
}

TOKEN_TYPE Token::type() const
{
    return tokenType;
}

int Token::integer() const
{
    assert(tokenType == TOKEN_CONST_INT);

    return iVal;
}

std::string Token::str() const
{
    assert(tokenType == TOKEN_ID);

    return sVal;
}

void Token::dump() const
{
    switch ( tokenType)
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

