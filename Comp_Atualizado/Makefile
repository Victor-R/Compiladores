INCFLG=-I./include
CFLAGS=$(INCFLG) $(OPTFLG)
OPTFLG=-g

parser-main: parser-main.o gettoken.o parser.o

clean:
	$(RM) *.o
mostlyclean: clean
	$(RM) *~
