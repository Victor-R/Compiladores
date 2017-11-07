#include <string.h>
//funções de print do parser.c, funções semanticas

void acc_recall(char const *name){
	int address = symtab_lookup(name);
	if (address > -1){
		acc = symtab_reg[address];
	}else{
		acc = 0;
	}
}

void calculate(int operator){
	switch(operator){
		case '+':
			acc = acc + stack[stack_pointer];
		break;
		case '-':
			acc = stack[stack_pointer] - acc;
		break;
		case '*':
			acc = acc * stack[stack_pointer];
		break;
		case '/':
			acc =  stack[stack_pointer] / acc ;
		break;
	}
	stack_pointer--;
}

void accpush(void){
	stack_pointer++;
	if(MAXSTACKSIZE >= stack_pointer){
		stack[stack_pointer] = acc;
	}
	
}

void accstore(char const *name){
	int address = symtab_lookup(name);
	
	if (address == -1){
		 address = symtab_nextentry; //incrementar nextentry;
		 symtab_nextentry++;
	}
	strcpy(symtab[address], name);
	symtab_reg[address] = acc;
	
}


void acc_immediate(double val)
{
	acc = val;
}

/** symtab.c**/
char symtab[MAXSYMENTRIES][MAXSTRLEN+1];
double symtab_reg[MAXSYMENTRIES];
int symtab_nextentry = 0;

int symtab_lookup(char const *query){
	int i;
	for(i = 0; i <symtab_nextentry; i++){
		if(strcmp(symtab[i], query) return i;
	}
	return -1;
}




/** auxiliary memory **/
double stack[MAXSTACKSIZE];
int stack_pointer = -1;
double acc = 0;
