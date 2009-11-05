
#ifndef __TOKENAN_H__
#define __TOKENAN_H__


#include <vector>
#include <string>

enum TOKEN_TYPE
{
    TOKEN_ID = 1,
    TOKEN_EOS,
    TOKEN_COMMA,
    TOKEN_LBRACKET,
    TOKEN_RBRACKET,
    TOKEN_CONST_INT,
    TOKEN_COLON,
};

class TokenAn
{
public:
    struct Token
    {
        TOKEN_TYPE type;

        int iVal;
        std::string sVal;

        static Token *createId( const std::string id_string);
        static Token *createConstInt( int iVal);
        static Token *createScalar( TOKEN_TYPE type);
        static Token *createEos();
        void dump();
    };

public:
    TokenAn( const char *filename);
    std::vector<Token *> run();

private:
    void init_file_length( const char *filename);
    void read_file_contents( const char *filename);

    void skip_spaces();

private:
    long filelength;
    char *data;
    char *ptr;
};

#endif

