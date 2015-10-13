#! /bin/sh

#Array=(0 100 200 400 800 1600 3200 6400 12800 25600 50825)

#uniprot
Ap=(0 100000 200000 400000 800000 1600000 3200000 6400000 12800000 25600000 50825784)
#reads
Ar=(0 100000 200000 400000 800000 1600000 3200000 6400000 12800000 25600000 32621862)
#wikipedia
Aw=(0 7624 15248 30497 60995 121990 243981 487963 975926 1951852 3903704)


#29266939

host="jau"
dir="/mnt/data/bio/projects/gpt"

#########################################################################

mkdir -p tests
	
##proteins

cp lib/utils_32.h lib/utils.h -f
make clean 
make

for i in 1
#for i in {1..10}
do

	if [ $i -eq 7 ]; then
		cp lib/utils_64.h lib/utils.h -f
		make clean
		make
	fi

	echo "dataset:  '${Ap[$i]}' strings"	

	mkdir -p tests/protein/
	date >> tests/protein/uniprot.${host}."${Ap[$i]}".txt

	for j in 3 4
	do
		echo " " >> tests/protein/uniprot.${host}."${Ap[$i]}".txt
		make run DIR=${dir} INPUT=uniprot_trembl.fasta K=${Ap[$i]} CHECK=0 MODE=$j >> tests/protein/uniprot.${host}."${Ap[$i]}".txt
	done

done

#########################################################################
##reads

cp lib/utils_32.h lib/utils.h -f
make clean 
make

for i in 1
#for i in {1..10}
do

        if [ $i -eq 9 ]; then
               cp lib/utils_64.h lib/utils.h -f
               make clean
               make
       fi

       echo "dataset:  '${Ap[$i]}' strings"    

       mkdir -p tests/reads/
       date >> tests/reads/reads.${host}."${Ar[$i]}".txt
       
       for j in 3 4
       do
               echo " " >> tests/reads/reads.${host}."${Ar[$i]}".txt
               make run DIR=${dir} INPUT=reads.fastq K=${Ar[$i]} CHECK=0 MODE=$j >> tests/reads/reads.${host}."${Ar[$i]}".txt
       done


done

#########################################################################
##wikipedia

cp lib/utils_32.h lib/utils.h -f
make clean 
make

for i in 1
#for i in {1..10}
do

        if [ $i -eq 8 ]; then
                cp lib/utils_64.h lib/utils.h -f
                make clean
                make
        fi

        echo "dataset:  '${Ap[$i]}' strings"    

        mkdir -p tests/wikipedia/
        date >> tests/wikipedia/text_SURF.${host}."${Aw[$i]}".txt

        for j in 3 4
        do
                echo " " >> tests/wikipedia/text_SURF.${host}."${Aw[$i]}".txt
                make run DIR=${dir} INPUT=text_SURF.txt K=${Aw[$i]} CHECK=1 MODE=$j >> tests/wikipedia/text_SURF.${host}."${Aw[$i]}".txt
        done

done



########################################################################
