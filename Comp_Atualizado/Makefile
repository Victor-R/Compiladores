INCFLG=-I./include
CFLAGS=$(INCFLG) $(OPTFLG)
OPTFLG=-g

project = mypas

relocatables = $(project).o lexer.o parser.o keywords.o symtab.o pseudoassembly.o

$(executable): $(relocatables)
	cc -o $(executable) $(relocatables) -lm

parser-main: parser-main.o gettoken.o parser.o

clean:
	$(RM) $(relocatables)
mostlyclean: clean
		$(RM) $(executable) *~
indent:
				indent -nfca -nsc -orig - nuts - ts4 *.[ch]
