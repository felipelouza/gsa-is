DEBUG = 0

all:
	gcc -c gsacak.c experiments/external/malloc_count/malloc_count.c -DDEBUG=$(DEBUG)
	gcc test_sap.c -o test gsacak.o  -ldl -DDEBUG=$(DEBUG)
