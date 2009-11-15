
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

struct Token
{
    TOKEN_TYPE type;

    int iVal;
    std::string sVal;

    /**
     * Creates a token representing an idetifier in the source code
     *
     * Examples:
     *      %r0 -- a processor register
     *      ld -- processor command name
     *      label -- user-defined identifier
     *
     * @param id_string The name of the identifier
     */
    static Token *createId( const std::string id_string);

    /**
     * Creates a token representing an integer constant
     *
     * @param iVal The value of the constant.
     */
    static Token *createConstInt( int iVal);

    /**
     * Creates a token that doesn't require any additional information
     *
     * @param type The type of the token, one of the following:
     *        TOKEN_LBRACKET -- left bracket, '('
     *        TOKEN_RBRACKET -- right bracket, ')'
     *        TOKEN_COLON -- colon, ':'
     *        TOKEN_COMMA -- comma, ','
     *
     * @see createEos
     */
    static Token *createScalar( TOKEN_TYPE type);

    /**
     * Create an end-of-string token
     *
     * This is an equivalent to "createScalar( TOKEN_EOS)"
     */
    static Token *createEos();

    void dump();
};


/**
 * This class is used to parse the assembler source code into tokens.
 * On TokenAn object creation it gets a file name and reads the contents
 * of the file. Then you should call 'run()' to generate a
 * vector<Token *> -- a sequence of tokens.
 */
class TokenAn
{
public:
    /**
     * Convenience constructor
     *
     * @param filename The name of the file with assembler source code.
     */
    TokenAn( const char *filename);

    /**
     * Generates a sequence of tokens from the text loaded from the file
     * given in the constructor
     *
     * Examples:
     *      "label:\n" => "label", ':', '\n'
     *      "brm %r0, (%r1)" => "brm", "%r0", ',', '(', "%r1", ')', '\n'
     *      "ld $100, %r0" => "ld", 100, "%r0"
     *
     * @return the sequence of tokens
     */
    std::vector<Token *> run();

private:
    void init_file_length( const char *filename);
    void read_file_contents( const char *filename);

    void skip_spaces();


    long filelength;
    char *data;
    char *ptr;
};

#endif

