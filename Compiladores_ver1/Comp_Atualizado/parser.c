
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// Local include//
#include <macros.h>
#include <parser.h>
#include <gettoken.h>
#include <tokens.h>
#include <keywords.h>
#include <symtab.h>
#include <mypas.h>
#include <pseudoassembly.h>



int	lookahead;

int ERROR_COUNT = 0;



char **nome_lista(void);

int semanticErrorNum()
{
  ERROR_COUNT++;
  return ERROR_COUNT;
}

void match(int expected) //match
{
    if (expected == lookahead) {
        lookahead = gettoken(src);
        //printf(" Lookahead=%d",lookahead);
    } else {
        fprintf(stderr, "token mismatch\n");
        fprintf(stderr, "expected %d ", expected);
        fprintf(stderr, "whereas found %d\n", lookahead);
        return;
    }
}


void mypas(void)
{
  lookahead = gettoken(src);
  var_dec();
  match('.');
}


void var_dec(void)
{
  declare(); // simbolos declarados
  fprintf(object, "\t.text\n\t.globl\tmain\n\t.type main,\t@function\n"); // Apenas para semelhança com arquivo essays
  fprintf(object, "main:\n");
  sim_used(); // simbolos usados
}

//Preenche tabela de simbolos, com nome e tipo
void declare(void)
{
  if (lookahead == VAR) {
    match(VAR);
    do {
      int type,i;
      // pega os nomes das variaveis declaradas para a tabela de simbolos
      char **namev = nome_lista();
      match(':');
      // pega o tipo das variaveis declaradas para a tabela de simbolos
      type =  vartype();


      // insere os nomes e tipos das variaveis no symtab
      for(i=0; namev[i]; i++) {
        if(symtab_append(namev[i], type) == -2)
          fprintf(stderr,"%d: FATAL ERROR -2: no more space in symtab", semanticErrorNum());
      }
      match(';');
    } while(lookahead == ID);
  }
}

// Adiciona  os nomes das variáveis em uma lista para serem colocados na tabela de simbolos
char **nome_lista(void)
{
  char **symbolvec = (char **)calloc(MAX_ARG_NUM, sizeof(char **));
  int i = 0;

  _nome_lista_start:
  strcpy(symbolvec[i] = malloc(sizeof lexeme +1), lexeme); i++;
  fprintf(object, "\t.comm %s\n",lexeme);
  match(ID);
  while(lookahead == ',') {
    match(',');
    goto _nome_lista_start;
  }
  return symbolvec;
}

// Verifica qual o tipo da variavel e o retorna
int vartype(void)
{
  switch(lookahead) {
    case INTEGER:
      match(INTEGER);
      return INTEGER;

    case LONGINT:
      match(LONGINT); //  NEW
      return LONGINT;

    case REAL:
      match(REAL);
      return REAL;

    case DOUBLE:
      match(DOUBLE);    //NEW?
      return DOUBLE;

    default:
      match(BOOLEAN);
      return BOOLEAN;
  }
}

void sim_used(void)
{
  match(BEGIN);
  stmtlist();
  match(END);
}

//stmtlist -> stmt { ';' stmt }
void stmtlist(void)
{
  stmt();
  while (lookahead == ';') {
    match(';');
    stmt();
  }
}

void if_stmt(void)
{
  int _endif, _else;
  match(IF);
  expr(BOOLEAN);
  cmpl();
  fprintf(object, "\tjz .L%d\n", _endif = _else = labelcounter++);
  match(THEN);
  stmt();
  if(lookahead == ELSE) {
    match(ELSE);
    _endif = jump(labelcounter++);
    mklabel(_else);

    stmt();
  }
  mklabel(_endif);
}

void while_stmt(void)
{
  int while_head, while_tail;

  match(WHILE);
  mklabel(while_head = labelcounter++);
  expr(BOOLEAN);                        // Escreve a expressão
  cmpl();                               // Faz a comparação
  gofalse(while_tail = labelcounter++); // Se falso, vai para depois do while
  match(DO);
  stmt();
  jump(while_head);                     //volta para o começo, para o laço
  mklabel(while_tail);                  // Escreve a label da calda

}


void blockstart(void)
{
  match(BEGIN);
  stmt();
  while(lookahead == ';') {
    match(';');
    stmt();
  }
  match(END);
}

void repeat_stmt(void)
{
  int repeat_head=0,repeat_tail=0;

  repeat_head = repeat_head + labelcounter++;
  repeat_tail = repeat_tail + labelcounter++;

  match(REPEAT);
  mklabel(repeat_head);
  //fazer label
  stmt();
  while(lookahead == ';') {
    match(';');
    stmt();
  }
  match(UNTIL);
  expr(BOOLEAN);
  cmpl();
  gofalse(repeat_tail); // se falso pula para o label da repeat_tail
  jump(repeat_head);   // se verdadeiro pula de volta para o label da repeat_head
  mklabel(repeat_tail);
  //testar label e dar jmp
}

//Verifica a relação entre tipos na expressão para promover o tipo correto
//Ex: REAL -> INTEGER + REAL; (Saída REAL)
 int type_check(int ltype, int rtype)
 {
   switch(ltype) {

     case BOOLEAN:
     case INTEGER:
       if(rtype == ltype)
         return ltype;
     break;


     case LONGINT:
        switch(rtype){
          case INTEGER:
            return ltype;
        }
     break;

     case REAL:
       switch(rtype) {
         case INTEGER:
         case LONGINT:
         case REAL:
         return ltype;
       }
     break;

     case DOUBLE:
       switch(rtype) {
         case INTEGER:
         case LONGINT:
         case REAL:
         case DOUBLE:
           return ltype;
       }
     break;
   }
   return 0;
 }

int isrelop(void)
{
  switch(lookahead) {
    case '>':
      match('>');
      if(lookahead == '=') {
	       match('=');
         return GEQ; //greater or equal
      }
      return '>';

    case '<':
      match('<');
      if(lookahead == '>') {
	       match('>');
         return NEQ; //not equal
      }
      if(lookahead == '=') {
	       match('=');
         return LEQ; //less or equal
      }
      return '<';

    case '=':
      match('=');
      return '=';
  }
  return 0;
}

int smpexpr(int inherited_type)
{
  int
	add_flag = 0,
	mul_flag = 0,
	varlocality,             // posição da variavel no symtab
	lvalue_seen = 0,         // flag é 1 quando LVALUE
	acctype = inherited_type,// acumulador de tipo
	syntype,                 // tipo de simbolo declarado em symtab
	ltype,           // syntype para verificação futura
	rtype,
  neg_flag = 0,    // tipo atualizado (pode ser promovido)
  con_flag = 0;

  if(lookahead == '-'){
    neg_flag = 1;
    match('-');
    if(acctype == BOOLEAN) { // o char "menos" não é compativel com BOOLEAN
      fprintf(stderr, "%d: incompatible unary operator: fatal error.\n",semanticErrorNum());
    } else if (acctype == 0) {
      acctype = INTEGER;
    }
  } else if (lookahead == NOT) {
    match(NOT);
    if(acctype > BOOLEAN) { // "not" não é compativel com tipos não booleano
      fprintf(stderr, "%d: incompatible unary operator: fatal error.\n", semanticErrorNum());
    }
    acctype = BOOLEAN;
  }

  T_entry:
  F_entry:
    switch(lookahead){

      case ID:
        varlocality = symtab_lookup(lexeme); // pega a posição da variavel na symtab

        if(varlocality < 0) {
          fprintf(stderr, "%d: parser: %s not declared... fatal error!\n", semanticErrorNum(),lexeme);
	        syntype = -1;
        } else {
	        syntype = symtab[varlocality][1]; // pega o tipo da variavel
	      }
      	if (acctype == 0){
      	  acctype = syntype;
      	}
        match(ID);
        if (lookahead == ASGN) {
    		  lvalue_seen = 1;
    		  ltype = syntype;

    	    match(ASGN);
    	    rtype = expr(ltype);


    	    if(type_check(ltype, rtype)) { // Verifica os tipos da expressao e promove os tipos caso necessário
    	      acctype = max(rtype,acctype);
    	    } else {
    	      acctype = -1;
    	    }
  	    }else if(varlocality > -1) {
          if(mul_flag){
            if(mul_flag=='*'){
              fprintf(object, "\tmovl\t%s(%%rip),\t%%edx\n",
              symtab_stream + symtab[varlocality][0]);
              strcpy(last_reg_used,"edx");
            }else if(mul_flag=='/'){
              fprintf(object, "\tmovl\t%s(%%rip),\t%%esi\n",
              symtab_stream + symtab[varlocality][0]);
              //strcpy(last_reg_used,"esi");
            }

          }else{
            fprintf(object, "\tmovl\t%s(%%rip),\t%%eax\n",
            symtab_stream + symtab[varlocality][0]);
            strcpy(last_reg_used,"eax");
          }
        }

      break;

      case FLTCONST:
        {
          float lexval = atof(lexeme);
          char *fltIEEE = malloc(sizeof(lexeme) + 1);
          sprintf(fltIEEE, "$%i", ((int *)&lexval) );
          //rmovel(fltIEEE); OLD
          rmovess(fltIEEE);
        }
        match(FLTCONST);
      	syntype = REAL;
      	if (acctype > BOOLEAN || acctype == 0) {
      	    acctype = max(acctype, syntype);
      	}

      break;

      case INTCONST:
        con_flag = 1;
        if(neg_flag){
          rmovel((char*)(lexeme),neg_flag);
          neg_flag = 0;
        }else{
          rmovel((char*)lexeme,neg_flag);
        }

        match(INTCONST);
      	syntype = INTEGER;
      	if (acctype > BOOLEAN || acctype == 0) {
      	    acctype = max(acctype, syntype);
      	}

        break;

      default:
        match('(');
	      syntype = expr(0);


	      if(type_check(syntype, acctype)) {
	         acctype = max(acctype,syntype);
	      } else {
  		     printf("default");
  	       fprintf(stderr, "%d: incompatible unary operator: fatal error.\n", semanticErrorNum());
  		     acctype = -1;
  	    }
       match(')');
    }

    if(mul_flag){
       if (mul_flag=='*'){
          mul_flag_ext = 1;
         mulint();
       }else if (mul_flag=='/'){
          mul_flag_ext = 2;
         divint();
       }
    }

    if(mul_flag = mulop())
      goto F_entry;

    if(add_flag){
      if(add_flag=='+'){
        addint();
      }else if (add_flag=='-'){
        subint();
      }
       //printf("Eu entrei no if(add_flag)\n" );
    }

    if(add_flag = addop())
      //printf("Eu entrei no if(addop\n" );
      goto T_entry;

    if(lvalue_seen && varlocality > -1) {
      switch(ltype) {

        case INTEGER:
          lmovel(symtab_stream + symtab[varlocality][0],con_flag);
          con_flag = 0;
        break;

        case LONGINT:
          lmoveq(symtab_stream + symtab[varlocality][0]);
        break;

        case REAL:
          lmovss(symtab_stream + symtab[varlocality][0]);
        break;

        case DOUBLE:
          lmovsd(symtab_stream + symtab[varlocality][0]);
        break;

        default://BOOLEAN
        break;

      }
    }

    return acctype;
}


int expr(int inherited_type)
{
  int t1;
  t1 = smpexpr(0); // t1 é o lado direito da smpexpression
  int t2 = 0;


  if(isrelop()) { // verifica se vem um operador relacional
     t2 = smpexpr(t1);

    if(type_check(t1,t2)) {
      //	cmpl();
    } else {
       fprintf(stderr, "%d: incompatible operation %d with %d: fatal error.\n",semanticErrorNum(),t1,t2);
       return -1;
    }
  }

  if(t2){
    if(t1 == t2 && t1 == BOOLEAN || t1 > BOOLEAN && t2 > BOOLEAN){
      return BOOLEAN;
    } else {
     if((inherited_type == BOOLEAN && t1 > BOOLEAN) || (t1 == BOOLEAN && inherited_type > BOOLEAN)){
       fprintf(stderr, "%d: incompatible operation %d with %d: fatal error.\n",semanticErrorNum(),t1,t2);
       return -1;
     } else {
      return max(t1,inherited_type);
     }
    }
  }
  return -1;
}

void stmt(void){
	switch (lookahead) {
    case BEGIN:
      blockstart();
      break;

    case IF:
      if_stmt();
      break;

    case WHILE:
      while_stmt();
      break;

    case REPEAT:
      repeat_stmt();
      break;

    case ID:
    case FLTCONST:
    case INTCONST:
    case TRUE:
    case FALSE:
    case NOT:
    case '-':
    case '(':
      smpexpr(0);
      break;

    default:
      ;
  }
}

void command(void){
	while (lookahead != EOF){
	stmt();
	}
}

/* addop -> + | - | OR */
int addop (void)
{
	switch(lookahead){
	case '+':
			match('+');
			/**/addint();/**/
			return '+';
	case '-':
			match('-');
			/**/subint();/**/
			return '-';
	case OR:
      match(OR);
      /**/mullog();/**/
      return OR;
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
			/**/mulint();/**/
	case '/':
			match('/'); return '/';
			/**/divint();/**/
	case AND:
      match(AND);
      /**/addlog();/**/
      return AND;
	}
	return 0;
}
