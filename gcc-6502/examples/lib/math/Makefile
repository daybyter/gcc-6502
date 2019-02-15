PROJECT := libmath

C_SOURCES := $(wildcard *.c)

ASM_SOURCES := $(wildcard *.s)

OBJECTS := $(patsubst %.c,%.o,$(C_SOURCES)) $(patsubst %.s,%.o,$(ASM_SOURCES))

LIB = $(PROJECT).a

CC = 6502-gcc

CCOPTS = -mmach=c64 -O2 -Wall

AR = ar65

AROPTS = a

DEBUGOPTS = 


$(OBJECTS): $(C_SOURCES) $(ASM_SOURCES)
	$(CC) $(CCOPTS) -c $(C_SOURCES) $(ASM_SOURCES)

.PHONY: lib
lib: $(OBJECTS)
	$(AR) $(AROPTS) $(LIB) *.o

.PHONY: install
install: lib
	cp $(LIB) ../
	cp *.h ../../include/

.PHONY: clean
clean:
	rm -f *.o $(LIB)

