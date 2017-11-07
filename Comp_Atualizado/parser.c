/**@<parser.c>::**/

#include <stdlib.h>
#include <stdio.h>
#include <gettoken.h>
#include <parser.h>
#include <string.h>

int	lookahead;

void match(int expected) //match
{
    if (expected == lookahead) {
        lookahead = gettoken(src);
        printf(" Lookahead=%d",lookahead);
    } else {
        fprintf(stderr, "token mismatch\n");
        fprintf(stderr, "expected %d ", expected);
        fprintf(stderr, "whereas found %d\n", lookahead);
        exit(-2);
    }
}

/** Syntax definition **/

/*
 * C-like expression LL(1)-grammar
 */

 void recall(char const *name){
	printf("\trecall(%s)\n",name);
}

 void calculate(int operator){
	switch(operator){
		case '+':
			printf("\tacc= acc + stack[sp]; sp--;\n");
		break;
		case '-':
			printf("\tacc= acc - stack[sp]; sp--;\n");
		break;
		case '*':
			printf("\tacc= acc * stack[sp]; sp--;\n");
		break;
		case '/':
			printf("\tacc= acc / stack[sp]; sp--;\n");
		break;
	}
}

 int
 isoplus(int oplus){
	switch (oplus) {
			case '+':
				/*6*/printf("\tacc = acc + stack[sp]; sp--;\n")/*6*/;
				return '+';
			case '-':
				/*7*/printf("\tacc = acc - stack[sp]; sp--;\n")/*7*/;
				return '-';
	}
	return 0;
}
int isotimes(int otimes){
	switch (otimes) {
			case '*':
				/*6*/printf("\tacc = acc * stack[sp]; sp--;\n")/*6*/;
				return '*';
			case '/':
				/*7*/printf("\tacc = acc / stack[sp]; sp--;\n")/*7*/;
				return '/';
	}
	return 0;
}

/*
 * E -> T R
 */
void E(void){
	int sign = 0, oplus = 0, otimes = 0;
	char name[MAXSTRLEN+1];

E_start:
	if(/*10*/sign = (lookahead == '-')/*10*/){
		match('-');
	}
T_start:
	if(oplus + otimes) { //isto não deveria ser setado antes?
		printf("\tpush(acc);\n");
	}

F_start:
//factor begins hereafter
	if(oplus + otimes){
			printf("\tpush(acc);\n");
	}
	printf("Lookahead2=%d",lookahead);
switch (lookahead) {
    case ID:
        match(ID);
        if((lookahead) == '=')
        {
			match('=');
			E();
		}else{
			recall(name);
		}
		break;
    case DEC:
			/*5*//*acc_immediate(atof(lexeme));*/
		//match(lookahead); break; Realizar opercoes diferentes conforme o formato
    case DECFP:
		/*5*//*acc_immediate(atof(lexeme));*/
		//match(lookahead); break; Realizar opercoes diferentes conforme o formato
    case OCT:
    case HEX:

        /*/if(!isfirst){
		printf("\tpush(acc);\n");
	}
	printf("\tacc = %s;\n",lexeme)/**/;

        match(lookahead);
        break;
    default:
        match('(');
        E();
        match(')');
        break;
   }
   /*12*/
   if(otimes){
	   calculate(otimes);//fazer execop
	   otimes=0;
	   }
   /*12*/
   if(/*14*/otimes = isotimes(lookahead)){
		match(lookahead);
		goto F_start;
	}
	/*11*/if(sign){
		printf("\tacc = - acc;\n");
		sign = 0;
	}/*11*/
	/*13*/
	if(oplus){
		calculate(oplus);
		oplus=0;
	}/*13*/

	if(/*15*/oplus = isoplus(lookahead)){
			match(lookahead);
			goto T_start;
	}
}

int isFIRST_E(void){
	switch(lookahead){
		case ('('):
		case ID:
		case DEC:
		case OCT:
		case HEX:
			return lookahead;
		case ';':
			return 0;
		default:
			return -1;
	}
}



void stmt(void){
	int status;
	if((status = isFIRST_E()) > 0){

	E();
	///*17*/ printf("%lg\n",acc)/*17*/;
	}else if(status < 0){
		fprintf(stderr, "error! expected variable, constant or '(', exiting with error status\n\n");

		exit(-3);
	}
	match(';');
}

void command(void){
	while (lookahead != EOF){
	stmt();
	}
}

/*
 * addop -> '+' | '-' | "||" | == | != ...
*/
int addop (void)
{
	switch(lookahead){
	case '+':
			match('+');
			return '+';
	case '-':
			match('-');
			return '-';
	}
	return 0;
}

/*
 * mulop -> '*' | '/' | && | %
 */
int mulop (void)
{
	switch(lookahead){
	case '*':
			match('*'); return '*';
	case '/':
			match('/'); return '/';
	}
	return 0;
}
