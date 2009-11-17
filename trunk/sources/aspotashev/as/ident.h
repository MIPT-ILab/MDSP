/**
 * mdsp-asm/ident.h -- Character classification functions
 * Copyright 2009 MDSP team
 */

/**
 * Returns whether a character may be the first character of an identifier
 */
#define isidstart(c) ((c) == '_' || isalpha(c))

/**
 * Returns whether a character may be a character in an identifier
 */
#define isidchar(c)  (isidstart(c) || isdigit(c))

/**
 * Returns whether a character is a whitespace character
 */
#define isblank(c) ((c) == ' ' || (c) == '\t') // Don't rely on libc

