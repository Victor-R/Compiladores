
#include <mypas.h>
#include <string.h>

/* variavies auxiliares */
extern int mul_flag_ext;

/*contador de labels*/

extern int labelcounter;

/*contadores de registradores*/
extern int reg_counter_int32;
extern int reg_counter_int64;
extern int reg_counter_float;
extern char last_reg_used[6];


/*Instruções de controle*/
int gofalse(int label);
int jump (int label);
int jle(int label);
int jlt(int label);
int jge(int label);
int jgt(int label);
int jeq(int label);
int jne(int label);
int cmpl();
int mklabel (int label);


/*Instruções de armazenamento*/
/*Move %registrador -> var(%rip)*/
int lmovel (char const *variable, int con_flag);
int lmoveq (char const *variable);
int lmovss (char const *variable);
int lmovsd (char const *variable);

/*Move $valor -> %registrador */
int rmovel (char const *variable, int neg_flag);
int rmoveq (char const *variable);
int rmovess(char const *variable);
int rmovesd(char const *variable);

/*ULA pseudo-instructions*/

/*Negação*/
int neglog(void);
int negint(void);
int negflt(void);

/*adição e subtração*/
int addlog(void);
int addint(void);
int addintq(void);
int addss(void);
int adddsd(void);
int subint(void);
int subq(void);
int subss(void);
int subsd(void);

/*multiplicação e divisão*/
int mullog(void);
int mulint(void);
int mulss(void);
int mulsd(void);
int divint(void);
int divq(void);
int divss(void);
int divsd(void);
