#include <pseudoassembly.h>

/*unified label counter*/

int labelcounter = 1;

/* contadores de registradores*/

int reg_counter_int32 = 0;
int reg_counter_int64 = 0;
int reg_counter_float = 0; //OK
char last_reg_used[6];

/*control pseudo instructions*/

int gofalse(int label)
{
  fprintf(object, "\tjz .L%d\n", label);
  return label;
}

int jump (int label)
{
  fprintf(object, "\tjmp .L%d\n", label);
  return label;
}

int jle(int label){
  fprintf(object, "\tjle .L%d\n", label);
  return 0;
}

int jlt(int label){
  fprintf(object, "\tjlt .L%d\n", label);
  return 0;
}

int jge(int label){
  fprintf(object, "\tjge .L%d\n", label);
  return 0;
}

int jgt(int label){
  fprintf(object, "\tjgt .L%d\n", label);
  return 0;
}

int jeq(int label){
  fprintf(object, "\tjeq .L%d\n", label);
  return 0;
}

int jne(int label){
  fprintf(object, "\tjne .L%d\n", label);
  return 0;
}

int cmpl() {
  fprintf(object, "\tcmpl %%%s, %%eax\n",last_reg_used);
}

int mklabel(int label)
{
  fprintf(object, ".L%d\n", label);
  return label;
}

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

  //fprintf(object, "\tmovl %%eax,%s\n",variable); OLD

  return 0;
}

int lmoveq (char const *variable) // move um int64 para o registrador
{

  switch(reg_counter_int64){
    case 0:
      fprintf(object, "\tmovl\t%s(%%rip), %%rax\n",variable);
    break;
    case 1:
      fprintf(object, "\tmovl\t%s(%%rip), %%rbx\n",variable);
    break;
    case 2:
      fprintf(object, "\tmovl\t%s(%%rip), %%rcx\n",variable);
    break;
    case 3:
      fprintf(object, "\tmovl\t%s(%%rip), %%rdx\n",variable);
    break;
    default:
      //ERROR
    break;
  }
  reg_counter_int64++;
  if(reg_counter_int64==4)
    reg_counter_int64 = 0;

  //fprintf(object, "\tmovq %%rax,%s\n",variable); OLD
  //fprintf(object, "\tmovq a(%rip), %rax",value,variable);
  return 0;
}


int lmovss (char const *variable)  // move um float32 para o registrador
{
  fprintf(object, "\tmovss\t%%xmm%s, %s(%%rip)\n",reg_counter_float,variable);
  reg_counter_float++;
  if(reg_counter_float==7)
    reg_counter_float = 0;

  return 0;
}


int lmovsd(char const *variable)  // move um float64 para o registrador
{
  fprintf(object, "\tmovsd\t%%xmm%s, %s(%%rip)\n",reg_counter_float,variable);
  if(reg_counter_float==7)
    reg_counter_float = 0;

  return 0;
}

int rmovel (char const *variable, int neg_flag) // move um valor int32bits para o registrador
{

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
  return 0;
}
/*
int rmoveq (char const *variable) // mover um valor int64bits para o registrador
{
  /*
  fprintf(object, "\tpushl %%rax\n");
  fprintf(object, "\tmovq %s, %%rax\n",variable); OLD

  switch(reg_counter_int64){
    case 0:
      fprintf(object, "\tmovl %s, %%rax",variable);
    break;
    case 1:
      fprintf(object, "\tmovl %s, %%rbx",variable);
    break;
    case 2:
      fprintf(object, "\tmovl %s, %%rcx",variable);
    break;
    case 3:
      fprintf(object, "\tmovl %s, %%rdx",variable);
    break;
    default:
      //ERROR
    break;
  }
  reg_counter_int64++;
  if(reg_counter_int64==4)
    reg_counter_int64 = 0;

  return 0;
}
*/

int rmovess(char const *variable)
{
  fprintf(object, "\tmovss\t%%xmm%s, %s(%%rip)\n",reg_counter_float,variable);
  reg_counter_float++;
  if(reg_counter_float==7)
    reg_counter_float = 0;

  return 0;
}
/*
int rmovesd(char const *variable)
{
  fprintf(object, "\tmovsd %%xmm%s, %s(%%rip)\n",reg_counter_float,variable);
  if(reg_counter_float==7)
    reg_counter_float = 0;

  return 0;
}*/

/*ULA pseudo-instructions*/

/*unary*/

int neglog(void)
{
  fprintf(object, "\tnot %%eax\n");
  return 0;
}

int negint(void)
{
  fprintf(object, "\tnot %%eax\n");
  return 0;
}

int negflt(void)
{
  fprintf(object, "\taddss %%xmm1, %%xmm0\n");
  fprintf(object, "\tmovss %%xmm0, x(%%rip)\n");
  fprintf(object, "\tnot %%esp\n");
  return 0;
}

int negdbl(void)
{
  fprintf(object, "\taddsd %%xmm1, %%xmm0\n");
  fprintf(object, "\tmovsd %%xmm0, x(%%rip)\n");
  fprintf(object, "\tnot %%esp\n");
  return 0;
}

/*binary addition and inversion*/

/*dbl and flt functions expects the value in the last label
then move the value from the label to register
then apply operation (value on register with value on top of stack)
  int functions expects value in register then just apply operation
*/

int addlog(void)
{
  fprintf(object, "\tor %%eax, (%%esp)\n");
  fprintf(object, "\tpopl %%eax\n");
  return 0;
}

int addint() //(var_left,var_right)
{
  if(strcmp(last_reg_used,"eax")!=0){
    fprintf(object, "\taddl\t%%eax,\t%%%s\n",last_reg_used);
  }
 return 0;
}

int addflt(void)
{
  fprintf(object, "\tmovss (%%rsp), %%xmm0\n");
  fprintf(object, "\tmovss %%rax, %%xmm1\n");
  fprintf(object, "\taddss %%xmm1, %%xmm0\n");
  fprintf(object, "\tmovss %%xmm0, %%rax\n");
  fprintf(object, "\taddq $8,%%rsp\n");
  /*
  addflt32:
  movss a(%rip), %xmm1
  movss b(%rip), %xmm0
  addss %xmm1, %xmm0
  */
  /*
  fprintf(object, "\tmovss %s(%%rip), %%xmm1\n",variavel_left);
  fprintf(object, "\tmovss %s(%%rip), %%xmm0\n",variavel_right);
  fprintf(object, "\taddss %%xmm1, %%xmm0\n");
  */
  return 0;
}

int adddbl(void)
{
  fprintf(object, "\tmovsd (%%rsp), %%xmm0\n");
  fprintf(object, "\tmovsd %%rax, %%xmm1\n");
  fprintf(object, "\tmulsd %%rbp, %%xmm0\n");
  fprintf(object, "\tmovsd %%xmm0, %%rax\n");
  fprintf(object, "\taddq $8,%%rsp\n");
  /*
  addflt64
  movsd a(%rip), %xmm1
  movsd b(%rip), %xmm0
  addsd %xmm1, %xmm0
  */
  /*
  fprintf(object, "\tmovsd %s(%%rip), %%xmm1\n",variavel_left);
  fprintf(object, "\tmovsd %s(%%rip), %%xmm0\n",variavel_right);
  fprintf(object, "\taddsd %%xmm1, %%xmm0\n");
  */
  return 0;
}

int subint(void)
{ /*
  fprintf(object, "\tmovl (%%rsp), %%ebx\n");
  fprintf(object, "\tmovl %%rax, %%eax\n");
  fprintf(object, "\tsubl %%esp,%%eax\n");
  fprintf(object, "\tmovsd %%xmm0, %%rax\n");
  fprintf(object, "\taddq $8,%%rsp\n");*/
  printf("Eu entro aqui?\n" );
  if(strcmp(last_reg_used,"eax")!=0){
    fprintf(object,"\tsubl\t%%eax,\t%%%s\n",last_reg_used);
  }
  return 0;
}

int subflt(void)
{
  fprintf(object, "\tmovsd (%%rsp), %%xmm0\n");
  fprintf(object, "\tmovsd %%rax, %%xmm1\n");
  fprintf(object, "\tsubss %%rbp, %%xmm0\n");
  fprintf(object, "\tmovsd %%xmm0, %%rax\n");
  fprintf(object, "\taddq $8,%%rsp\n");
  return 0;
}
int subdbl(void)
{
  fprintf(object, "\tmovsd (%%rsp), %%xmm0\n");
  fprintf(object, "\tmovsd %%rax, %%xmm1\n");
  fprintf(object, "\tsubsd %%rbp, %%xmm0\n");
  fprintf(object, "\tmovsd %%xmm0, %%rax\n");
  fprintf(object, "\taddq $8,%%rsp\n");
  return 0;
}

/*binary multiplication and inverse*/

int mullog(void)
{
  fprintf(object, "\tand %%eax, (%%esp)\n");
  fprintf(object, "\tpopl %%eax\n");
  return 0;
}

int mulint(void)
{
  fprintf(object, "\tmovl (%%rsp), %%ebx\n");
  fprintf(object, "\tmovl %%rax, %%eax\n");
  fprintf(object, "\timull %%esp, %%eax\n");
  fprintf(object, "\tmovsd %%xmm0, %%rax\n");
  fprintf(object, "\taddq $8,%%rsp\n");
  return 0;
}

int mulflt(void)
{
  fprintf(object, "\tmovsd (%%rsp), %%xmm0\n");
  fprintf(object, "\tmovsd %%rax, %%xmm1\n");
  fprintf(object, "\tmulss %%rbp), %%xmm0\n");
  fprintf(object, "\tmovsd %%xmm0, %%rax\n");
  fprintf(object, "\taddq $8,%%rsp\n");
  return 0;
}

int muldbl(void)
{
  fprintf(object, "\tmovsd (%%rsp), %%xmm0\n");
  fprintf(object, "\tmovsd %%rax, %%xmm1\n");
  fprintf(object, "\tmulsd %%rbp, %%xmm0\n");
  fprintf(object, "\tmovsd %%xmm0, %%rax\n");
  fprintf(object, "\taddq $8,%%rsp\n");

  return 0;
}

int divint(void)
{
  fprintf(object, "\tmovsd (%%rsp), %%xmm0\n");
  fprintf(object, "\tmovsd %%rax, %%xmm1\n");
  fprintf(object, "\tcltd\n");
  fprintf(object, "\tidivl %%rbp\n");
  fprintf(object, "\tmovsd %%xmm0, %%rax\n");
  fprintf(object, "\taddq $8,%%rsp\n");
  return 0;
}

int divflt(void)
{
  fprintf(object, "\tmovsd (%%rsp), %%xmm0\n");
  fprintf(object, "\tmovsd %%rax, %%xmm1\n");
  fprintf(object, "\tdivss %%rbp, %%xmm0;\n");
  fprintf(object, "\tmovsd %%xmm0, %%rax\n");
  fprintf(object, "\taddq $8,%%rsp\n");
  return 0;
}

int divdbl(void)
{
  fprintf(object, "\tmovsd (%%rsp), %%xmm0\n");
  fprintf(object, "\tmovsd %%rax, %%xmm1\n");
  fprintf(object, "\tdivss %%rbp), %%xmm0;\n");
  fprintf(object, "\tmovsd %%xmm0, %%rax\n");
  fprintf(object, "\taddq $8,%%rsp\n");
  return 0;
}
