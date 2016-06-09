#! /bin/sh

#sources
#A=(7065006 4210907 1866 43894765 1 545356 1 9550966 296135875)
#A=(7065006 4210907 1866 21894765 1 545356 1 9550966 7619949)
#D=("sources" "proteins" "dna" "english" "cere" "einstein" "fib41" "kernel" "dblp") 

A=(1453483 336 545356 1007648 1 9550966 186913 1763309)
A=(145348 33 54535 100764 0 955096 18691 176330)
D=("dblp.xml.50MB" "dna.50MB" "einstein.de" "english.50MB" "fib41" "kernel" "proteins.50MB" "sources.50MB")

host="louza"
dir="/home/louza/dataset/pizzachili"
c=1
exp="time"

#######################################################################

#mkdir -p pizzachili
cd ..
cp lib/settings/utils_32.h lib/utils.h -f
make clean 
make


	
for i in {0..7}
do

	test=${D[$i]}
>&2	echo "--"	
>&2	echo "${test}"	

	for j in {0..7}
	do	
>&2		echo "MODE ${j}"
		
#		mkdir -p pizzachili/${test}/
#		date >> pizzachili/${test}/${host}.db.${exp}.txt

#		echo " " >> pizzachili/${test}/${host}.db.${exp}.txt
		make run DIR=${dir} INPUT=${test}.txt K=${A[$i]} CHECK=$c MODE=$j # >> pizzachili/${test}/${host}.db.${exp}.txt
	done
	
done


#########################################################################


