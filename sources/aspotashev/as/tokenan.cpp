
#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include <iostream>
#include <sstream>

#include "tokenan.h"
#include "ident.h"

TokenAn::TokenAn( const char *filename)
{
    data = NULL;
    ptr = NULL;

    readFileContents( filename);
}

TokenAn::~TokenAn()
{
    if ( data)
    {
        delete [] data;
    }

    data = NULL;
}

void TokenAn::initFileLength( const char *filename)
{
    FILE *f = fopen( filename, "r");
    assert( f);

    fseek( f, 0, SEEK_END);
    fileLength = ftell( f);
    fclose( f);
}

void TokenAn::readFileContents( const char *filename)
{
    assert( data == NULL); // allow reading a file only once

    initFileLength( filename);

    data = new char[fileLength + 1];
    data[fileLength] = '\0';

    FILE *f = fopen( filename, "r");
    if ( fread( data, 1, fileLength, f) != (size_t)fileLength)
        throw;
    
    fclose( f);
}

std::vector<Token *> TokenAn::run()
{
    assert( data);

    ptr = data;
    std::vector<Token *> res;

    while ( *ptr != '\0')
    {
        skipSpaces();

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
            assert( 0);
        }
    }

    return res;
}

void TokenAn::skipSpaces()
{
    assert( ptr);

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
    assert( tokenType == TOKEN_CONST_INT);

    return iVal;
}

std::string Token::str() const
{
    assert( tokenType == TOKEN_ID);

    return sVal;
}

std::string Token::dump() const
{
    std::stringstream res;

    switch ( tokenType)
    {
    case TOKEN_ID:        res << sVal; break;
    case TOKEN_EOS:       res << "--------------- (\\n)"; break;
    case TOKEN_COMMA:     res << ","; break;
    case TOKEN_LBRACKET:  res << "("; break;
    case TOKEN_RBRACKET:  res << ")"; break;
    case TOKEN_CONST_INT: res << iVal; break;
    case TOKEN_COLON:     res << ":"; break;
    default: throw;
    }

    return res.str();
}

