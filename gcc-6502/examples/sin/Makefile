PROJECT := sin

C_SOURCES := $(wildcard *.c)

ASM_SOURCES := $(wildcard *.s)

EXECUTABLE = $(PROJECT).prg

DISKIMAGE = $(PROJECT).d64

CC = 6502-gcc

CCOPTS = -mmach=c64 -O2 -Wall

DEBUGOPTS = 

EMULATOR_APP = /usr/bin/x64

DISKIMAGE_APP = /usr/bin/c1541


.PHONY: compile
compile:
	$(CC) $(CCOPTS) $(C_SOURCES) $(ASM_SOURCES) -o $(EXECUTABLE)

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
