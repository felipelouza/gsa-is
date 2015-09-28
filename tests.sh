#! /bin/sh

#Array=(0 200000 400000 800000 1600000 3200000 6400000 12800000 25600000 50825784)
Array=(0 200 400 800 1600 3200 6400 12800 25600 50825)

#29266939

host="jau"

#########################################################################

pwd
make

mkdir -p tests

#ests

for i in 1 2 3 4 5 6 7 8 9
do

        echo " "        
        echo "dataset:  '${Array[$i]}' strings" 
        echo "--"       

#       mkdir -p tests/ests/
#       date > tests/ests/dataset."${Array[$i]}".txt
#
#       #ests
#       for j in 1 2 3 4
#       do
#               echo " " >> tests/ests/dataset."${Array[$i]}".txt
#               make run DIR=/home/louza/database/ests/ INPUT=all_ests.fasta K=${Array[$i]} CHECK=0 MODE=$j >> tests/ests/dataset."${Array[$i]}".txt
#       done
#       
#       mkdir -p tests/reads/
#       date > tests/reads/dataset."${Array[$i]}".txt
#       
#       #reads
#       for j in 1 2 3 4
#       do
#               echo " " >> tests/reads/dataset."${Array[$i]}".txt
#               make run DIR=/home/louza/database/protein/ INPUT=uniprot_trembl.fasta K=${Array[$i]} CHECK=0 MODE=$j >> tests/reads/dataset."${Array[$i]}".txt
#       done
#
        mkdir -p tests/protein/
        date > tests/protein/uniprot.${host}."${Array[$i]}".txt

        #proteins
        for j in 1 2 3 4
        do
                echo " " >> tests/protein/uniprot.${host}."${Array[$i]}".txt
                make run DIR=$HOME/database/protein/ INPUT=uniprot_trembl.fasta K=${Array[$i]} CHECK=1 MODE=$j >> tests/protein/uniprot.${host}."${Array[$i]}".txt
        done
done

########################################################################
