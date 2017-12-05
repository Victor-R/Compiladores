INCFLG=-I./include
CFLAGS=$(INCFLG) $(OPTFLG)
OPTFLG=-g

project = mypas

relocatables = $(project).o gettoken.o parser.o keywords.o symtab.o pseudoassembly.o

executable = $(project)

$(executable): $(relocatables)
	cc -o $(executable) $(relocatables) -lm
clean:
	$(RM)  $(relocatables)
mostlyclean: clean
	$(RM) $(executable) *~
indent:
	indent -nfca -nsc -orig - nuts - ts4 *.[ch]
