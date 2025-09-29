all:
	gcc -c gsacak.c experiments/external/malloc_count/malloc_count.c -DDEBUG=0
	gcc test_sap.c -o test gsacak.o  -ldl -DDEBUG=0
