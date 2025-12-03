CC = gcc
#CC = clang

LD = $(CC)

CFLAGS =
CFLAGS += -g
CFLAGS += -std=gnu99 
CFLAGS += -Wall 
CFLAGS += -Wshadow
#CFLAGS += -pedantic 
CFLAGS += -Wno-unused-function
CFLAGS += -Werror

OBJECTS =
OBJECTS += main.o
OBJECTS += student_test.o
OBJECTS += pal_test.o
OBJECTS += playlist.o

EXE = ./test

.PHONY: all
all: $(EXE)

main.o: playlist.h test.h
playlist.o: playlist.h

$(EXE): $(OBJECTS)
	$(LD) $^ -o $@

.PHONY: run
run: all
	$(EXE)

.PHONY: check
check:
	aspell --home-dir=`pwd` -l nl -c README.md

.PHONY: clean
clean: 
	$(RM) $(OBJECTS)
	$(RM) $(EXE)

.PHONY: force
force: clean
force: $(EXE)