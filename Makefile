CC = gcc
CFLAGS += -Wall 
#CFLAGS += -g -O0
CFLAGS += -D_FILE_OFFSET_BITS=64 -m64 -O3 -fomit-frame-pointer -Wno-char-subscripts 

LFLAGS = -lm -lrt -ldl

DIR = dataset/
INPUT = input.1000.txt

#DIR = /home/louza/database/ests/
#INPUT = all_ests.fasta

#DIR = /home/louza/database/protein/
#INPUT = uniprot_trembl.fasta

#DIR = /home/louza/database/reads/
#INPUT = Vr6_L001_R1.clipped.fastq

K = 3
MODE = 1
CHECK = 1

LIBOBJ = \
	lib/utils.o\
	lib/file.o\
	lib/suffix_array.o\
	external/malloc_count/malloc_count.o\
	gsais.o\
	gsaca-k.o

all: compile

clean:
	\rm lib/*.o *.o external/*.o gsais -v

compile: main.c ${LIBOBJ} 
	$(CC) $(CFLAGS) $(LFLAGS) -o gsais main.c ${LIBOBJ}

run:
	./gsais $(DIR) $(INPUT) $(K) $(MODE) $(CHECK)

valgrind:
	valgrind --tool=memcheck --leak-check=full --track-origins=yes ./gsais $(DIR) $(INPUT) $(K) $(MODE) $(CHECK)
