/**@<pseudoassembly.h>::**/
#include <mypas.h>
#include <string.h>

/* auxiliary variables */
extern int mul_flag_ext;

/*unified label counter*/

extern int labelcounter;

/* contadores de registradores*/
extern int reg_counter_int32;
extern int reg_counter_int64;
extern int reg_counter_float;
extern char last_reg_used[6];

//char *reg_return(void);
/*control pseudo instructions*/

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

int lmovel (char const *variable, int con_flag);
int lmoveq (char const *variable);
int lmovss (char const *variable);
int lmovsd (char const *variable);

int rmovel (char const *variable, int neg_flag);
//int rmoveq (char const *variable);
int rmovess(char const *variable);
//int rmovesd(char const *variable);

/*ULA pseudo-instructions*/

/*unary*/
int neglog(void);
int negint(void);
int negflt(void);
int negdbl(void);

/*binary addition and inversion*/
int addlog(void);
int addint(void);
int addflt(void);
int adddbl(void);
int subint(void);
int subflt(void);
int subdbl(void);

/*binary multiplication and inverse*/
int mullog(void);
int mulint(void);
int mulflt(void);
int muldbl(void);
int addflt(void);
int adddbl(void);
int divint(void);
int divflt(void);
int divdbl(void);
