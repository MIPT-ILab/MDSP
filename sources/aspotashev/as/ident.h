
#define isidstart(c) ((c) == '_' || isalpha(c))
#define isidchar(c)  (isidstart(c) || isdigit(c))

#if not (_XOPEN_SOURCE >= 600 || _ISOC99_SOURCE)
#define isblank(c) ((c) == ' ' || (c) == '\t')
#endif

