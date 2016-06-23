#! /bin/sh


A=(1453483 336 545356 1007648 1 9550966 186913 1763309)
D=("dblp.xml.50MB" "dna.50MB" "einstein.de" "english.50MB" "fib41" "kernel" "proteins.50MB" "sources.50MB")

host="louza"
dir="/home/louza/dataset/pizza"
c=1
exp="time"

#######################################################################

#mkdir -p pizza
cd ..
cp lib/settings/utils_32.h lib/utils.h -f
make clean 
make

for i in {0..7}
do

	test=${D[$i]}
	echo "--"	
	echo "${test}"	

    	for j in {1..8}
     	do	
		echo "MODE ${j}"
		
		mkdir -p pizza/${test}/
		date >> pizza/${test}/${host}.db.${exp}.txt

		echo " " >> pizza/${test}/${host}.db.${exp}.txt
		make run DIR=${dir} INPUT=${test}.txt K=${A[$i]} CHECK=$c MODE=$j >> pizza/${test}/${host}.db.${exp}.txt
	done
	
done


#########################################################################


