/**@<gettoken.c>::**/

#include <ctype.h>
#include <stdio.h>
#include <gettoken.h>

char lexeme[MAXSTRLEN+1];

char *tokeninfo[] = {
	"ID",
    "DEC",
    "EQ",
    "NEQ",
    "GEQ",
    "LEQ",
    "SCI",
    "DECFP",
    "OCT",
    "HEX"
};

void skipspaces(FILE *tape)
{
    int	head;
    while (isspace(head = getc(tape)));
    
    ungetc(head, tape);
}

int isID(FILE *tape)
{
    int	head;
    int i = 0;

    if (isalpha(lexeme[i] = getc(tape))) {
		i++;
		
        while (isalnum(lexeme[i] = getc(tape)))
			if(i < MAXSTRLEN) {
			   lexeme[i] = head; i++;
			}
        ungetc(head, tape);
        lexeme[i] = 0;
        printf("ID");
        return ID;
    }
    ungetc(head, tape);    
    return 0;
}

int isDEC(FILE *tape)
{
    int	head;
    int i = 0;
    if (isdigit(head = getc(tape))) {
		lexeme[i] = head; i++;
        if (head == '0'){
            return DEC;
        }
        while (isdigit(head = getc(tape)))
			if(i < MAXSTRLEN) {
			   lexeme[i] = head; i++;
			}
        ungetc(head, tape);
        lexeme[i] = 0;
        return DEC;
    }
    ungetc(head, tape);
    return 0;
}

int isEQ(FILE *tape)
{
    int	head;
    if ((head = getc(tape)) == '=') {
        if ((head = getc(tape)) == '=') {
            return EQ;
        }
        ungetc(head, tape);
        ungetc('=', tape);
        return 0;
    }
    ungetc(head, tape);
    return 0;
}

int isNEQ(FILE * tape)
{
    int             head;
    if ((head = getc(tape)) == '!') {
        if ((head = getc(tape)) == '=') {
            return NEQ;
        }
        ungetc(head, tape);
        ungetc('!', tape);
        return 0;
    }
    ungetc(head, tape);
    return 0;
}

int isGEQ(FILE * tape)
{
    int             head;
    if ((head = getc(tape)) == '>') {
        if ((head = getc(tape)) == '=') {
            return GEQ;
        }
        ungetc(head, tape);
        ungetc('>', tape);
        return 0;
    }
    ungetc(head, tape);
    return 0;
}

int isLEQ(FILE * tape)
{
    int             head;
    if ((head = getc(tape)) == '<') {
        if ((head = getc(tape)) == '=') {
            return LEQ;
        }
        ungetc(head, tape);
        ungetc('<', tape);
        return 0;
    }
    ungetc(head, tape);
    return 0;
}

int isSCI(FILE *tape) //acho que eh essa q precisa arrumar
{
  int head, sgn = 0;
  if(toupper(head = getc(tape)) == 'E'){
    if((head - getc(tape)) == '+' || head == '-'){
      sgn = head;
      if(!isdigit(head = getc(tape))){
	ungetc(head, tape);
	ungetc(sgn, tape);
	ungetc('E', tape);
	return 0;
      }
    }else{
      if(!isdigit(head)){
	ungetc(head, tape);
	ungetc('E', tape);
	return 0;}
    }
  while(isdigit(head = getc(tape))); ungetc(head, tape); return SCI;
  }
  ungetc(head, tape);
  return 0;
}

int isDECFP(FILE *tape)
{
  int head, token = 0;
  if(token = isDEC(tape)){
    if((head = getc(tape)) == '.'){
      token = DECFP;
      while(isdigit(head = getc(tape)));
      }
      ungetc(head, tape);
      isSCI(tape) && (token == DEC) && (token = DECFP);
      return token;
  }else if(head = getc(tape) == '.'){
		if(!isdigit(head = getc(tape))){
			ungetc(head, tape);
			ungetc('.', tape);
			return 0;
		}
		while(isdigit(head = getc(tape)));
		ungetc(head, tape);
		isSCI(tape);
		return DECFP;
  }
	ungetc(head, tape);
	return 0;
}

int isOCT(FILE *tape)
{
	int token = 0;
	token = getc(tape);
	int head = getc(tape);
	if(token == '0'){
		if(head >= '0' && head <= '7'){
			while ( (head = getc(tape))	>= '0' && head <= '7');
			ungetc(head, tape);
			return OCT;
		} else {
			ungetc(head, tape);
			ungetc(token, tape);
			return 0;
		}
	}
	ungetc(token, tape);
	return 0;
}

int isHEX(FILE *tape)
{
	int head = getc(tape);
	int aux = head;
	if ( head == '0'){
		head = getc(tape);
		if (head =='x'){
			if ( ((head = getc(tape)) >= '0' && head <= '9') || (head >= 'a' && head <= 'f') || (head >= 'A' && head <= 'F')){
				while ( ((head = getc(tape)) >= '0' && head <= '9') || (head >= 'a' && head <= 'f') || (head >= 'A' && head <= 'F') );
				if(head = getc(tape)!=EOF)
					return 0;
				else{
					ungetc(head,tape);
					return HEX;
				}
			}
			else{
				ungetc(head,tape);
			}
		}else{
			ungetc(head,tape);
			ungetc(aux,tape);
		}
	}else{
		ungetc(head,tape);
	}
	return 0;
}	

int gettoken(FILE *tape)
{
    int	token;
    skipspaces(tape);
    if(
        (token = isID(tape))   ||
        (token = isDEC(tape))  || //NUM
        (token = isEQ(tape))   ||
        (token = isNEQ(tape))  ||
        (token = isGEQ(tape))  ||
        (token = isLEQ(tape))  ||
		(token = isSCI(tape))  ||
		(token = isDECFP(tape))||
		(token = isOCT(tape))  ||
		(token = isHEX(tape))
		) {printf(" tolkien=%d ", token);return token;}
			
		
		token = getc(tape);

		return token;
	/*lexeme[0] = getc(tape); //.-.
	lexeme[1] = 0;
    return lexeme[0];*/
}

		
