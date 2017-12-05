#include <stdio.h>
#include <gettoken.h>

 #define MAXSYMTAB_ENTRIES 0x10000
 #define MAXSTACK_SIZE     0x40
 #define MAX_ARG_NUM 1024


int smpexpr(int inherited_type);
int expr(int inherited_type);

int addop (void);

int mulop (void);


void mypas(void);
void var_dec(void);
void declare(void);
int vartype(void);
void sim_used(void);
void stmtlist(void);
void stmt(void);
void blockstart(void);
void if_stmt(void);
void while_stmt(void);
void repeat_stmt(void);



extern int lookahead;



extern int gettoken (FILE *);

void match (int expected_token);

extern FILE *src;

extern char lexeme[];
