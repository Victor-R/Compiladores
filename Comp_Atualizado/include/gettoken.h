/**@<gettoken.h>::**/

#define MAXSTRLEN 1024
extern char lexeme[MAXSTRLEN+1];
extern char *tokeninfo[];

enum {
    ID = 1024,
    DEC,
    EQ,
    NEQ,
    GEQ,
    LEQ,
    SCI,
    DECFP,
    OCT,
    HEX,
};

int gettoken(FILE *);
