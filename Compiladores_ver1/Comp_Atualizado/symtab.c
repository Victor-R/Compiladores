#include <string.h>
#include <parser.h>
#include <gettoken.h>
#include <symtab.h>


int symtab[MAX_SYMTAB_ENTRIES][2]; // Declara symtab como symtab[32 variaveis][nome,tipo]
int symtab_nextentry = 0; // position of next entry in symtab

// symtab_stream: vetor com todos os simbolos declarados
// posição do simbolo na symtab_stream é colocado na symtab
char symtab_stream[MAX_SYMTAB_ENTRIES*(MAXID_SIZE+1)];
// posição do próximo item de symtab_stream
int symtab_stream_next_descriptor = 0;

// Verifica se já existe variavel com o mesmo nome e retorna a posição
int symtab_lookup(char const *name)
{
  int i;
  for(i = symtab_nextentry - 1; i > -1; i--){
   if( strcmp(symtab_stream + symtab[i][0],name) == 0)
    break;
  }

  return i;
}

int symtab_append(char const *name, int type)
{
  int location = symtab_lookup(name);

  if(symtab_nextentry == MAX_SYMTAB_ENTRIES)
    return -2; // sem espaço na symtab (Tabela de símbolos)
  if(location > -1 )
    return -3; // Erro na location

  strcpy(symtab_stream + symtab_stream_next_descriptor, name); // insere o nome da variavel na tabela

  // coloca a posição da symtab_stream no vetor de symtab
  symtab[symtab_nextentry][0] = symtab_stream_next_descriptor;
  // coloca o tipo no vetor de symtab
  symtab[symtab_nextentry][1] = type;
  // prevê a posição da próxima entrada de variavel na symtab através do tamanho da variavel
  symtab_stream_next_descriptor += strlen(name) +1;

  return symtab_nextentry++;
}

//print_symtab_stream: uma função que imprime todos os calculos de symtab *para debugar*
void print_symtab_stream(void)
{
  int a,b,fim,ini;
  for (a=0;a<symtab_nextentry;a++)
  {
    //acha onde a stream começa
    b = symtab[a][0];
    printf("\nsymtab entry #%d ",a);
    //imprime até o final da stream
    while(symtab_stream[b]!='\0')
    {
      printf("%c",symtab_stream[b]);
      b++;
    }
  }
}
