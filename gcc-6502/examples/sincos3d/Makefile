PROJECT := sincos3d

C_SOURCES := $(wildcard *.c)

ASM_SOURCES := $(wildcard *.s)

EXECUTABLE = $(PROJECT).prg

DISKIMAGE = $(PROJECT).d64

CC = 6502-gcc

CCOPTS = -static -mmach=c64 -O2 -Wall -I ../include -L../lib/

LIBS = -lmath -lgraphics

DEBUGOPTS = 

#LINKEROPTS = -L /home/andreas/retro-projects/c64/gcc-6502/examples/lib

EMULATOR_APP = /usr/bin/x64

DISKIMAGE_APP = /usr/bin/c1541


.PHONY: compile
compile:
	$(CC) $(LINKEROPTS) $(CCOPTS) $(C_SOURCES) $(ASM_SOURCES) $(LIBS) -o $(EXECUTABLE)

.PHONY: image
image: compile
	$(DISKIMAGE_APP) -format $(PROJECT),1 d64 $(DISKIMAGE)
	$(DISKIMAGE_APP) $(DISKIMAGE) -write $(EXECUTABLE) $(EXECUTABLE)

.PHONY: clean
clean:
	rm *.o $(EXECUTABLE) $(DISKIMAGE)

.PHONY: emulator
emulator: image
	$(EMULATOR_APP) -autostart "$(DISKIMAGE):$(EXECUTABLE)"
