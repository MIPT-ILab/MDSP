/**
 * mdsp-asm/tokenan.h -- Definition of TokenAn class,
 *                       the lexical analyzer
 * Copyright 2009 MDSP team
 */

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

/**
 * A token is a part of source code independent of the formatting:
 *      "_lkjhg12" (any identifier), end of string, ',', '(', ')', ':',
 *      100 (any integer constant)
 */
class Token
{
public:
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

    /**
     * Returns the type of the token
     *
     * Getter for @p tokenType
     */
    TOKEN_TYPE type() const;

    /**
     * Returns the integer value associated with the token when the type
     * of the token is TOKEN_CONST_INT
     *
     * Getter for @p iVal
     */
    int integer() const;

    /**
     * Returns the string value associated with the token when the type
     * of the token is TOKEN_ID
     *
     * Getter for @p sVal
     */
    std::string str() const;

    /**
     * Dumps the token into a string
     */
    std::string dump() const;

private:
    /**
     * The type of the token, one of the following:
     *      TOKEN_ID        -- identifier ("asdfgh", "%r0", ...)
     *      TOKEN_EOS       -- end of string ('\n' or end of file)
     *      TOKEN_COMMA     -- ','
     *      TOKEN_LBRACKET  -- '('
     *      TOKEN_RBRACKET  -- ')'
     *      TOKEN_CONST_INT -- integer constant (100, ...)
     *      TOKEN_COLON     -- ':'
     */
    TOKEN_TYPE tokenType;

    /**
     * The value of integer constant (when tokenType is TOKEN_CONST_INT)
     */
    int iVal;

    /**
     * The string of identifier (when tokenType is TOKEN_ID)
     */
    std::string sVal;
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
     * dtor
     */
    ~TokenAn();

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
    /**
     * Initializes @p fileLength with the length of a file
     *
     * @param filename The name of the file.
     */
    void initFileLength( const char *filename);

    /**
     * Allocates the buffer @p data and copies the contents of a file
     * to that buffer
     *
     * @param filename The name of the file.
     */
    void readFileContents( const char *filename);

    /**
     * Moves the current character pointer @p ptr forward while it points
     * to a whitespace character
     */
    void skipSpaces();


    /**
     * The length of the input file, initializes before reading the file
     */
    long fileLength;

    /**
     * The input file contents buffer
     */
    char *data;

    /**
     * The pointer to the current character in the buffer
     */
    char *ptr;
};

#endif

