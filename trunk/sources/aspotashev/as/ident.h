
#define isidstart(c) ((c) == '_' || isalpha(c))
#define isidchar(c)  (isidstart(c) || isdigit(c))
#define isblank(c) ((c) == ' ' || (c) == '\t') // Don't rely on libc

