CC = gcc
CFLAGS += -Wall 
#CFLAGS += -g -O0
CFLAGS += -D_FILE_OFFSET_BITS=64 -m64 -O3 -fomit-frame-pointer -Wno-char-subscripts 

LFLAGS = -lm -lrt -ldl

DIR = dataset/
INPUT = input.100.txt

K	= 3
MODE 	= 1
CHECK	= 1
OUTPUT	= 0

LIBOBJ = \
	lib/utils.o\
	lib/file.o\
	lib/suffix_array.o\
	external/malloc_count/malloc_count.o\
	src/gsais.o\
	src/gsaca-k.o

all: compile

clean:
	\rm lib/*.o src/*.o external/*.o gsais -v

compile: main.c ${LIBOBJ} 
	$(CC) $(CFLAGS) $(LFLAGS) -o gsais main.c ${LIBOBJ}

run:
	./gsais $(DIR) $(INPUT) $(K) $(MODE) $(CHECK) $(OUTPUT)

valgrind:
	valgrind --tool=memcheck --leak-check=full --track-origins=yes ./gsais $(DIR) $(INPUT) $(K) $(MODE) $(CHECK) $(OUTPUT)
