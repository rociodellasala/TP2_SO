include ../Makefile.inc

MODULE=processRead.bin
SOURCES=$(wildcard [^_]*.c)
SOURCES_ASM=$(wildcard asm/*.asm)
OBJECTS=$(SOURCES:.c=.o)
OBJECTS_ASM=$(SOURCES_ASM:.asm=.o)
LOADERSRC=_loader.c

LOADEROBJECT=$(LOADERSRC:.c=.o)
STATICLIBS=

all: $(MODULE)

$(MODULE): $(LOADEROBJECT) $(OBJECTS) $(STATICLIBS) $(OBJECTS_ASM)
	$(LD) $(LDFLAGS) -T processRead.ld -o ../$(MODULE) $(LOADEROBJECT) $(OBJECTS) $(OBJECTS_ASM) $(STATICLIBS) 

%.o: %.c
	$(GCC) $(GCCFLAGS) -I./include -c $< -o $@ -pedantic -ansi -Wall

%.o : %.asm
	$(ASM) $(ASMFLAGS) $< -o $@

$(LOADEROBJECT):
	$(GCC) $(GCCFLAGS) $(LOADERSRC) -c -o $(LOADEROBJECT) -pedantic -ansi -Wall

clean:
	rm -rf asm/*.o *.o

.PHONY: all clean print
