#! /bin/sh

Array=(0 100 200 300 400 500 600 700 800)
#Array=(0 200000 400000 800000 1600000 3200000 6400000)

#29266939


#########################################################################

pwd
make

mkdir -p tests
	
#ests

for i in 1 2 3 4 5 6
do

	echo " "	
	echo "dataset:  '${Array[$i]}' strings"	
	echo "--"	

	mkdir -p tests/ests/
	date > tests/ests/dataset."${Array[$i]}".txt

	#ests
	for j in 1 2 3 4
	do
		echo " " >> tests/ests/dataset."${Array[$i]}".txt
		make run DIR=/home/louza/database/ests/ INPUT=all_ests.fasta K=${Array[$i]} CHECK=0 MODE=$j >> tests/ests/dataset."${Array[$i]}".txt
	done
	
	mkdir -p tests/reads/
	date > tests/reads/dataset."${Array[$i]}".txt
	
	#reads
	for j in 1 2 3 4
	do
		echo " " >> tests/reads/dataset."${Array[$i]}".txt
		make run DIR=/home/louza/database/protein/ INPUT=uniprot_trembl.fasta K=${Array[$i]} CHECK=0 MODE=$j >> tests/reads/dataset."${Array[$i]}".txt
	done

	mkdir -p tests/protein/
	date > tests/protein/dataset."${Array[$i]}".txt

	#proteins
	for j in 1 2 3 4
	do
		echo " " >> tests/protein/dataset."${Array[$i]}".txt
		make run DIR=/home/louza/database/reads/ INPUT=Vr6_L001_R1.clipped.fastq K=${Array[$i]} CHECK=0 MODE=$j >> tests/protein/dataset."${Array[$i]}".txt
	done
done
	




########################################################################
