#include <pseudoassembly.h>

/*contador de labels*/
int labelcounter = 1;

/* variavies auxiliares */
int mul_flag_ext = 0;

/* contadores de registradores*/
int reg_counter_int32 = 0;
int reg_counter_int64 = 0;
int reg_counter_float = 0; //OK
char last_reg_used[6];

/*Instruções de controle*/

int gofalse(int label)
{
  fprintf(object, "\tjz\t\t.L%d\n", label);
  return label;
}

int jump (int label)
{
  fprintf(object, "\tjmp\t\t.L%d\n", label);
  return label;
}

int jle(int label){
  fprintf(object, "\tjle\t\t.L%d\n", label);
  return 0;
}

int jlt(int label){
  fprintf(object, "\tjlt\t\t.L%d\n", label);
  return 0;
}

int jge(int label){
  fprintf(object, "\tjge\t\t.L%d\n", label);
  return 0;
}

int jgt(int label){
  fprintf(object, "\tjgt\t\t.L%d\n", label);
  return 0;
}

int jeq(int label){
  fprintf(object, "\tjeq\t\t.L%d\n", label);
  return 0;
}

int jne(int label){
  fprintf(object, "\tjne\t\t.L%d\n", label);
  return 0;
}

int cmpl() {
  switch (last_reg_used[0]) {
    case 'e':
      fprintf(object, "\tcmpl\t%%%s,\t%%eax\n",last_reg_used);
    break;
    case 'r':
      fprintf(object, "\tcmpq\t%%%s,\t%%rax\n",last_reg_used);
    break;
    case 'x':
      fprintf(object, "\tcmpq\t%%%s,\t%%xmm0\n",last_reg_used);
    break;
  }

}

int mklabel(int label)
{
  fprintf(object, ".L%d\n", label);
  return label;
}

/*Move %registrador -> var(%rip)*/

int lmovel (char const *variable, int con_flag) // move um int32 para o registrador
{
    if(con_flag){
      switch(reg_counter_int32){
        case 0:
          fprintf(object, "\tmovl\t%%eax,\t%s(%%rip)\n",variable);
        break;
        case 1:
          fprintf(object, "\tmovl\t%%ebx,\t%s(%%rip)\n",variable);
        break;
        case 2:
          fprintf(object, "\tmovl\t%%ecx,\t%s(%%rip)\n",variable);
        break;
        case 3:
          fprintf(object, "\tmovl\t%%edx,\t%s(%%rip)\n",variable);
        break;
        default:
          //ERROR
        break;
      }
    } else {
      fprintf(object, "\tmovl\t%%%s,\t%s(%%rip)\n",last_reg_used,variable);
    }
    reg_counter_int32++;
    if(reg_counter_int32==4)
      reg_counter_int32 = 0;

  return 0;
}

int lmoveq (char const *variable, int con_flag) // move um int64 para o registrador
{
  if(con_flag){
    switch(reg_counter_int64){
      case 0:
        fprintf(object, "\tmovq\t%%rax,\t%s(%%rip)\n",variable);
      break;
      case 1:
        fprintf(object, "\tmovq\t%%rbx,\t%s(%%rip)\n",variable);
      break;
      case 2:
        fprintf(object, "\tmovq\t%%rcx,\t%s(%%rip)\n",variable);
      break;
      case 3:
        fprintf(object, "\tmovq\t%%rdx,\t%s(%%rip)\n",variable);
      break;
      default:
        //ERROR
      break;
    }
    reg_counter_int64++;
    if(reg_counter_int64==4)
      reg_counter_int64 = 0;
  }else{
    fprintf(object, "\tmovq\t%%r%cx,\t%s(%%rip)\n",last_reg_used[1],variable);
  }

  return 0;
}


int lmovss (char const *variable, int con_flag)  // move um float32 para o registrador
{
  if(con_flag){
    fprintf(object, "\tmovss\t%%xmm%d, %s(%%rip)\n",reg_counter_float,variable);
    reg_counter_float++;
    if(reg_counter_float==7)
      reg_counter_float = 0;
  }else{
    fprintf(object, "\tmovss\t%%xmm%d, %s(%%rip)\n",reg_counter_float,variable);
  }
  return 0;
}


int lmovsd(char const *variable, int con_flag)  // move um float64 para o registrador
{
  fprintf(object, "\tmovsd\t%%xmm%d, %s(%%rip)\n",reg_counter_float,variable);
  reg_counter_float++;
  if(reg_counter_float==7)
    reg_counter_float = 0;

  return 0;
}

int rmovel (char const *variable, int neg_flag) // move um valor int32bits para o registrador
{
  if(mul_flag_ext==1){
    fprintf(object, "\tmovl\t$%s,\t%%edx\n",variable);
    strcpy(last_reg_used,"edx");
    mul_flag_ext = 0;
  }else if (mul_flag_ext==2){
    fprintf(object, "\tmovl\t$%s,\t%%esi\n",variable);
    strcpy(last_reg_used,"eax");
    mul_flag_ext = 0;
  }else{
    reg_counter_int32++;
    if(reg_counter_int32==4)
      reg_counter_int32=0;
    switch(reg_counter_int32){
      case 0:
        if(neg_flag){
          fprintf(object, "\tmovl\t$-%s,\t%%eax\n",variable);
        }else{
          fprintf(object, "\tmovl\t$%s,\t%%eax\n",variable);
        }
        strcpy(last_reg_used,"eax");
      break;
      case 1:
        if(neg_flag){
          fprintf(object, "\tmovl\t$-%s,\t%%ebx\n",variable);
        }else{
          fprintf(object, "\tmovl\t$%s,\t%%ebx\n",variable);
        }
        strcpy(last_reg_used,"ebx");
      break;
      case 2:
        if(neg_flag){
          fprintf(object, "\tmovl\t$-%s,\t%%ecx\n",variable);
        }else{
          fprintf(object, "\tmovl\t$%s,\t%%ecx\n",variable);
        }
        strcpy(last_reg_used,"ecx");
      break;
      case 3:
        if(neg_flag){
          fprintf(object, "\tmovl\t$-%s,\t%%edx\n",variable);
        }else{
          fprintf(object, "\tmovl\t$%s,\t%%edx\n",variable);
        }
        strcpy(last_reg_used,"edx");
      break;
      default:
        //ERROR
      break;
    }
  }
  return 0;
}

int rmoveq (char const *variable, int neg_flag) // mover um valor int64bits para o registrador
{
  if(mul_flag_ext==1){
    fprintf(object, "\tmovq\t$%s,\t%%rdx\n",variable);
    strcpy(last_reg_used,"rdx");
    mul_flag_ext = 0;
  }else if (mul_flag_ext==2){
    fprintf(object, "\tmovq\t$%s,\t%%rsi\n",variable);
    strcpy(last_reg_used,"rax");
    mul_flag_ext = 0;
  }else{
    reg_counter_int64++;
    if(reg_counter_int64==4)
      reg_counter_int64=0;

    switch(reg_counter_int64){
      case 0:
        if(neg_flag){
          fprintf(object, "\tmovq\t$-%s,\t%%rax\n",variable);
        }else{
          fprintf(object, "\tmovq\t$%s,\t%%rax\n",variable);
        }
        strcpy(last_reg_used,"rax");
      break;
      case 1:
        if(neg_flag){
          fprintf(object, "\tmovq\t$-%s,\t%%rbx\n",variable);
        }else{
          fprintf(object, "\tmovq\t$%s,\t%%rbx\n",variable);
        }
        strcpy(last_reg_used,"rbx");
      break;
      case 2:
        if(neg_flag){
          fprintf(object, "\tmovq\t$-%s,\t%%rcx\n",variable);
        }else{
          fprintf(object, "\tmovq\t$%s,\t%%rcx\n",variable);
        }
        strcpy(last_reg_used,"rcx");
      break;
      case 3:
        if(neg_flag){
          fprintf(object, "\tmovq\t$-%s,\t%%rdx\n",variable);
        }else{
          fprintf(object, "\tmovq\t$%s,\t%%rdx\n",variable);
        }
        strcpy(last_reg_used,"rdx");
      break;
      default:        
      break;
    }
  }
  reg_counter_int64++;
  if(reg_counter_int64==4)
    reg_counter_int64 = 0;

  return 0;
}

int rmovess(char const *variable)
{
  fprintf(object, "\tmovss\t%s(%%rip),\t%%xmm%s\n",variable,reg_counter_float);
  reg_counter_float++;
  if(reg_counter_float==7)
    reg_counter_float = 0;

  return 0;
}

int rmovesd(char const *variable)
{
  fprintf(object, "\tmovsd\t%s(%%rip),\t%%xmm%s\n",variable,reg_counter_float);
  if(reg_counter_float==7)
    reg_counter_float = 0;

  return 0;
}

/*ULA pseudo-instructions*/

/*unary*/

int neglog(void)
{
  fprintf(object, "\tnot %%%s\n",last_reg_used);
  return 0;
}

int negint(void)
{
  fprintf(object, "\tnot %%%s\n",last_reg_used);
  return 0;
}

int negflt(void)
{
  fprintf(object, "\tnot %%xmm%s\n",reg_counter_float);
  return 0;
}

/*Operações*/

/*Adicionais*/
int addlog(void)
{
  fprintf(object, "\tor %%eax, (%%esp)\n");
  return 0;
}
//int32 - integer
int addint()
{
  if(strcmp(last_reg_used,"eax")!=0){
    fprintf(object, "\taddl\t%%eax,\t%%%s\n",last_reg_used);
  }
 return 0;
}
//int64 - longint
int addintq(){
  if(strcmp(last_reg_used,"rav")!=0){
    fprintf(object, "\taddq\t%%rax,\t%%%s\n",last_reg_used);
  }
}
//float32 - real
int addss(void)
{
  if((reg_counter_float)!=0){
    fprintf(object, "\taddss\t%%xmm0,\t%%xmm%d\n",reg_counter_float);
  }


  return 0;
}
//float64 - double
int adddsd(void)
{
  if((reg_counter_float-1)!=0){
    fprintf(object, "\taddsd %%xmm1, %%xmm0\n",reg_counter_float-1);
  }
  return 0;
}

/*Subtratoras*/
//int32 - integer
int subint(void)
{
  if(strcmp(last_reg_used,"eax")!=0){
    fprintf(object,"\tsubl\t%%eax,\t%%%s\n",last_reg_used);
  }
  return 0;
}
//int64 - longint
int subq(void){
  if(strcmp(last_reg_used,"rax")!=0){
    fprintf(object,"\tsubl\t%%rax,\t%%%s\n",last_reg_used);
  }
  return 0;
}
//float32 - real
int subss(void)
{
  if((reg_counter_float)!=0){
    fprintf(object,"\tsubss\t%%xmm0,\t%%xmm%d\n",reg_counter_float);

  }

  return 0;
}
//float64 - double
int subsd(void)
{
  if((reg_counter_float)!=0){
    fprintf(object,"\tsubsd\t%%xmm0,\t%%xmm%s\n",reg_counter_float);
  }
  return 0;
}

/*Multiplicadoras*/

int mullog(void)
{
  fprintf(object, "\tand %%eax, (%%esp)\n");
  return 0;
}
//int32 - integer
int mulint(void)
{
  fprintf(object, "\tmull\t%%edx,\t%%eax\n");
  strcpy(last_reg_used,"eax");
  return 0;
}
//int64 - longint
int mulq(void)
{
  fprintf(object, "\tmulq\t%%rdx,\t%%rax\n");
  strcpy(last_reg_used,"rax");
  return 0;
}
//float32 - real
int mulss(void)
{
  fprintf(object, "\tmulss\t%%xmm0,\t%%xmm1\n",reg_counter_float);
  reg_counter_float = 1;
  return 0;
}
//float64 - double
int mulsd(void)
{
  fprintf(object, "\tmulsd\t%%xmm%d,\t%%xmm1\n",reg_counter_float);
  return 0;
}

/*Divisoras*/

//int32 - integer
int divint(void)
{
  fprintf(object, "\tcltd\n");
  fprintf(object, "\tidivl\t%%esi\n");

  return 0;
}
//int64 - longint
int divq(void)
{
  fprintf(object, "\tcltd\n");
  fprintf(object, "\tidivq\t%%rsi\n");
  return 0;
}
//float32 - real
int divss(void)
{
  fprintf(object, "\tidivss\t%%xmm1,\t%%xmm0\n");
  return 0;
}
//float64 - double
int divsd(void)
{
  fprintf(object, "\tidivsd\t%%xmm1,\t%%xmm0\n");
  return 0;
}
