CC = gcc
CFLAGS += -Wall 
#CFLAGS += -g -O0
CFLAGS += -D_FILE_OFFSET_BITS=64 -m64 -O3 -fomit-frame-pointer -Wno-char-subscripts 

LFLAGS = -lm -lrt -ldl

DIR = dataset/
INPUT = input-10000.txt

##

K	= 10000
MODE 	= 6
LCP_COMPUTE = 0
DA_COMPUTE = 0
CHECK	= 1
OUTPUT	= 0

DEBUG	= 0

DEFINES = -DDEBUG=$(DEBUG)

##

LIBOBJ = \
	lib/utils.o\
	lib/file.o\
	lib/suffix_array.o\
	lib/lcp_array.o\
	lib/document_array.o\
	external/malloc_count/malloc_count.o\
	src/gsais.o\
	src/gsaca-k.o


all: compile

clean:
	\rm lib/*.o src/*.o external/*.o gsais -f 

remove:
	\rm $(DIR)*.str $(DIR)*.sa $(DIR)*.lcp $(DIR)*.da $(DIR)*.da_bit -f 

#lib: lib/file.o lib/utils.o
#	$(CC) $(DEFINES) -c lib/utils.c -o lib/utils.o 

compile: main.c ${LIBOBJ} 
	$(CC) $(CFLAGS) $(LFLAGS) $(DEFINES) -o gsais main.c ${LIBOBJ}

run:
	./gsais $(DIR) $(INPUT) $(K) $(MODE) $(LCP_COMPUTE) $(DA_COMPUTE) $(CHECK) $(OUTPUT)

valgrind:
	valgrind --tool=memcheck --leak-check=full --track-origins=yes ./gsais $(DIR) $(INPUT) $(K) $(MODE) $(LCP_COMPUTE) $(DA_COMPUTE) $(CHECK) $(OUTPUT)
