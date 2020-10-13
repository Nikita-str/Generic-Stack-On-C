Files=code.o tests_1.o tests_2.o
all: GS_Test.exe

GS_Test.exe: $(Files)
	gcc -m64 -o $@ $(Files) -lm

%.o: %.c
	gcc -m64 -c $< -o $@ -lm

code.o: code.c tests_1.o tests_2.o  
tests_2.o: tests_2.h GenericStackConfigEnum.h GenericStack.h tests_2.c
tests_1.o: tests_1.h GenericStackConfigEnum.h GenericStack.h tests_1.c

.PHONY: all clean clean_o

clean_o:
	-rm $(Files)

clean:
	-rm $(Files)
	-rm GS_Test.exe
