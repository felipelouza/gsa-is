#! /bin/sh

#Array=(0 100 200 400 800 1600 3200 6400 12800 25600 50825)

#uniprot
#Array=(0 100000 200000 400000 800000 1600000 3200000 6400000 12800000 25600000 50825784)
#reads
#Array=(0 100000 200000 400000 800000 1600000 3200000 6400000 12800000 25600000 32621862)
#wikipedia
Array=(0 7624 15248 30497 60995 121990 243981 487963 975926 1951852 3903704)


#29266939

host="jau"
dir="/mnt/data/bio/projects/gpt"
#########################################################################

cp lib/utils_32.h lib/utils.h -f
pwd
make clean 
make

mkdir -p tests
	
#ests

for i in {1..10} 
do

	if [ $i -eq 7 ]; then
		cp lib/utils_64.h lib/utils.h -f
		make clean
		make
	fi

	echo " "	
	echo "dataset:  '${Array[$i]}' strings"	
	echo "--"	

#	mkdir -p tests/reads/
#	date > tests/reads/reads.${host}."${Array[$i]}".txt
#	
#	#reads
#	for j in 1 2 3 4
#	do
#		echo " " >> tests/reads/reads.${host}."${Array[$i]}".txt
#		make run DIR=${dir} INPUT=reads.fastq K=${Array[$i]} CHECK=0 MODE=$j >> tests/reads/reads.${host}."${Array[$i]}".txt
#	done

#	mkdir -p tests/protein/
#	date > tests/protein/uniprot.${host}."${Array[$i]}".txt
#
#	#proteins
#	for j in 1 2 3 4
#	do
#		echo " " >> tests/protein/uniprot.${host}."${Array[$i]}".txt
#		make run DIR=${dir} INPUT=uniprot_trembl.fasta K=${Array[$i]} CHECK=0 MODE=$j >> tests/protein/uniprot.${host}."${Array[$i]}".txt
#	done

	mkdir -p tests/wikipedia/
	date > tests/wikipedia/text_SURF.${host}."${Array[$i]}".txt
	
	#reads
	for j in 1 2 3 4
	do
		echo " " >> tests/wikipedia/text_SURF.${host}."${Array[$i]}".txt
		make run DIR=${dir} INPUT=text_SURF.txt K=${Array[$i]} CHECK=1 MODE=$j >> tests/wikipedia/text_SURF.${host}."${Array[$i]}".txt
	done

done



########################################################################
