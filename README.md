#gsa-is

This code is an implementation of gSAIS and gSACA-K [1], which extend the
linear-time suffix sorting algorithms SAIS [2] and SACA-K [3] to compute the
generalized suffix array, maintaining their theoretical bounds, respecting 
the order among all suffixes, and improving their practical performance

Overall, gSACA-K's time-space trade-off is Pareto optimal compared to the all
other algorithms in the experiments.

**New**: gSAIS+LCP and gSACA-K+LCP extends the algorithms gSAIS and gSACA-K to
also compute the LCP-array. The new algorithms are based on the algorithms by
Fischer [5] and by Louza et. al [6].

**New**: gSAIS+DA and gSACA-K+DA extends the algorithms gSAIS and gSACA-K to
also compute the Document array (DA). 

--
##run:

To run a test type:

```sh
make
make run DIR=dataset INPUT=input-10000.txt K=10000 MODE=6 LCP_COMPUTE=1
```

One can change to 32 bits integers (when n < 2^31) in lib/utils.h, setting m64
to 0.

--

**Settings:**

MODE parameter specifies which algorithm is called by main.c:

* 1:  SAIS\* 
* 2:  SACA-K\* 
* 3:  SAIS  
* 4:  SACA-K 
* 5:  gSAIS
* 6:  gSACA-K
* 7:  gSAIS+LCP
* 8:  gSACA-K+LCP
* 9:  gSAIS+DA
* 10: gSACA-K+DA

SAIS\* and SACA-K\* are versions that receive an integer alphabet as input.

--

**LCP-array:**

One can also compute the LCP-array after the SA construction using Phi-algorithm [4]:

```sh
make run LCP_COMPUTE=1
```

**Document-array:**

One can also compute the Document-array after the SA construction using a slightly variation of Algorithm 7.30 from Ohlebusch's book [7, page 347]:

```sh
make run DA_COMPUTE=1
```

**Validate:**

One can check if the output produced is correct:

```sh
make run CHECK=1
```

**Output:**

One can output the GSA (and the LCP) produced as .sa (or .sa_lcp):

```sh
make run OUPUT=1
```

**Compare:**

One can compare all algorithms:

```sh
for i in {1..10}; do make run DIR=dataset INPUT=input-10000.txt K=10000 LCP_COMPUTE=1 DA_COMPUTE=1 MODE=$i; done
```

--
##references

\[1\] Louza, F. A., Gog, S., Telles, G. P., Induced Suffix Sorting for String Collections. In Proc. DCC, pp. 43-58, 2016.

\[2\] Nong G., Zhang S., Chan W. H., Two efficient algorithms for linear time suffix array construction, IEEE Trans. Comput., vol. 60, no. 10, pp. 1471–1484, 2011

\[3\] Nong, G., Practical linear-time O(1)-workspace suffix sorting for constant alphabets, ACM Trans. Inform. Syst., vol. 31, no. 3, pp. 1–15, 2013

\[4\] Kärkkäinen, J., Manzini, G., & Puglisi, S. J. (2009). Permuted Longest-Common-Prefix Array. In G. Kucherov & E. Ukkonen (Eds.), Proc. CPM (Vol. 5577, pp. 181–192).

\[5\] Fischer, J., Inducing the LCP-Array, in: Proc. WADS, 2011, pp. 374-385.

\[6\] Louza, F. A., Gog, S., Telles, G. P., Optimal suffix sorting and LCP array construction for constant alphabets, Inf. Process. Lett. 118 (2017) 30-34, http://www.sciencedirect.com/science/article/pii/S0020019016301375

\[7\] Ohlebusch, E., Bioinformatics Algorithms: Sequence Analysis, Genome Rearrangements, and Phylogenetic Reconstruction. Oldenbusch Verlag, 2013.

--


##experiments:


**Collections:**

| Collection | size (GB)  |      d     |        n       |    n/d    | available at |
|------------|:----------:|-----------:|---------------:|----------:|:-------------|
| Revision   |    0.39    |     20,433 |    419,437,293 |    20,527 | http://jltsiren.kapsi.fi/data/fiwiki.bz2 |
| Page       |    3.74    |      1,000 |  4,019,585,128 | 4,019,585 | http://jltsiren.kapsi.fi/data/fiwiki.bz2 |
| Influenza  |    0.56    |    394,217 |    597,471,768 |     1,516 | ftp://ftp.ncbi.nih.gov/genomes/INFLUENZA/influenza.fna.gz |
| Enwiki     |    8.32    |  3,903,703 |  8,933,518,792 |     2,288 | http://algo2.iti.kit.edu/gog/projects/ALENEX15/collections/ENWIKIBIG/text_SURF.sdsl |
| DNA reads  |    2.87    | 32,621,862 |  3,082,739,100 |        94 | http://gage.cbcb.umd.edu/data/Hg_chr14/Data.quakeCor.tgz | 
| Uniprot    |    15.77   | 50,825,784 | 16,931,428,229 |       333 | ftp://ftp.uniprot.org/pub/databases/uniprot/previous_releases/release-2015_09/ |


| Dataset      | d          | N+d            | avgLen       | mean_lcp  | max_lcp   |
|--------------|------------|----------------|--------------|-----------|-----------|
| pages 1      | 2          | 2,371,241      | 1,185,620.50 | 2,930.62  | 11,784    |
| pages 2      | 7          | 14,707,622     | 2,101,088.86 | 7,277.33  | 35,602    |
| pages 3      | 15         | 35,043,296     | 2,336,219.73 | 7,557.62  | 53,561    |
| pages 4      | 31         | 52,890,374     | 1,706,141.10 | 9,417.36  | 511,497   |
| pages 5      | 62         | 119,466,260    | 1,926,875.16 | 9,785.91  | 511,497   |
| pages 6      | 125        | 412,148,014    | 3,297,184.11 | 32,100.61 | 1,995,055 |
| pages 7      | 250        | 840,886,051    | 3,363,544.20 | 24,089.69 | 1,995,055 |
| pages 8      | 450        | 2,127,332,977  | 4,727,406.62 | 32,745.40 | 2,912,604 |
| pages 9      | 650        | 2,635,913,891  | 4,055,252.14 | 30,586.03 | 2,912,604 |
| pages 10     | 1,000      | 4,019,585,128  | 4,019,585.13 | 29,595.13 | 2,912,604 |
| revision 1   | 40         | 99,138         | 2,478.45     | 789.39    | 3,272     |
| revision 2   | 80         | 260,366        | 3,254.58     | 1,036.75  | 3,866     |
| revision 3   | 159        | 914,542        | 5,751.84     | 2,433.32  | 9,767     |
| revision 4   | 319        | 2,091,943      | 6,557.82     | 2,805.35  | 10,458    |
| revision 5   | 638        | 4,294,715      | 6,731.53     | 2,887.88  | 11,784    |
| revision 6   | 1,277      | 16,058,904     | 12,575.49    | 7,017.83  | 35,558    |
| revision 7   | 2,554      | 34,168,931     | 13,378.59    | 7,675.18  | 53,518    |
| revision 8   | 5,108      | 59,888,778     | 11,724.51    | 9,124.09  | 511,497   |
| revision 9   | 10,217     | 144,241,776    | 14,117.82    | 10,981.09 | 511,497   |
| revision 10  | 20,433     | 419,437,293    | 20,527.45    | 31,612.79 | 1,995,055 |
| influenza 1  | 769        | 924,268        | 1,201.91     | 118.64    | 2,326     |
| influenza 2  | 1,539      | 1,773,953      | 1,152.67     | 138.74    | 2,326     |
| influenza 3  | 3,079      | 3,600,436      | 1,169.35     | 173.99    | 2,326     |
| influenza 4  | 6,159      | 7,056,864      | 1,145.78     | 213.45    | 2,335     |
| influenza 5  | 12,319     | 14,100,766     | 1,144.64     | 245.48    | 2,369     |
| influenza 6  | 24,638     | 32,959,239     | 1,337.74     | 368.04    | 2,369     |
| influenza 7  | 49,277     | 70,800,914     | 1,436.79     | 433.34    | 2,369     |
| influenza 8  | 98,554     | 142,930,737    | 1,450.28     | 466.11    | 2,369     |
| influenza 9  | 197,108    | 289,558,572    | 1,469.04     | 505.14    | 2,379     |
| influenza 10 | 394,217    | 597,471,768    | 1,515.59     | 533.83    | 2,379     |
| wikipedia 1  | 7,624      | 13,303,449     | 1,744.94     | 12.67     | 1,275     |
| wikipedia 2  | 15,248     | 25,737,808     | 1,687.95     | 14.06     | 1,823     |
| wikipedia 3  | 30,497     | 53,002,468     | 1,737.96     | 15.54     | 4,852     |
| wikipedia 4  | 60,995     | 101,073,689    | 1,657.08     | 16.58     | 4,852     |
| wikipedia 5  | 121,990    | 189,880,688    | 1,556.53     | 17.93     | 7,134     |
| wikipedia 6  | 243,981    | 478,842,959    | 1,962.62     | 18.48     | 11,705    |
| wikipedia 7  | 487,963    | 1,071,827,039  | 2,196.53     | 19.25     | 14,815    |
| wikipedia 8  | 975,926    | 2,315,093,668  | 2,372.20     | 20.45     | 24,330    |
| wikipedia 9  | 1,951,852  | 4,459,594,679  | 2,284.80     | 22.72     | 24,330    |
| wikipedia 10 | 3,903,703  | 8,933,518,792  | 2,288.47     | 27.12     | 61,055    |
| reads 1      | 100,000    | 9,030,390      | 90.30        | 12.52     | 101       |
| reads 2      | 200,000    | 17,703,050     | 88.52        | 13.95     | 101       |
| reads 3      | 400,000    | 36,808,318     | 92.02        | 16.56     | 101       |
| reads 4      | 800,000    | 75,089,460     | 93.86        | 20.43     | 101       |
| reads 5      | 1,600,000  | 149,953,139    | 93.72        | 25.56     | 101       |
| reads 6      | 3,200,000  | 302,041,259    | 94.39        | 31.99     | 101       |
| reads 7      | 6,400,000  | 604,318,315    | 94.42        | 37.89     | 101       |
| reads 8      | 12,800,000 | 1,209,578,418  | 94.50        | 42.19     | 101       |
| reads 9      | 25,600,000 | 2,419,646,287  | 94.52        | 42.35     | 101       |
| reads 10     | 32,621,862 | 3,082,739,100  | 94.50        | 43.35     | 101       |
| protein 1    | 100,000    | 26,198,280     | 261.98       | 26.22     | 1,786     |
| protein 2    | 200,000    | 52,503,813     | 262.52       | 25.85     | 1,936     |
| protein 3    | 400,000    | 106,286,416    | 265.72       | 35.81     | 3,245     |
| protein 4    | 800,000    | 219,589,476    | 274.49       | 43.31     | 3,245     |
| protein 5    | 1,600,000  | 531,194,430    | 332.00       | 44.48     | 7,885     |
| protein 6    | 3,200,000  | 1,253,483,804  | 391.71       | 73.48     | 7,885     |
| protein 7    | 6,400,000  | 2,667,015,568  | 416.72       | 108.15    | 22,560    |
| protein 8    | 12,800,000 | 5,162,366,462  | 403.31       | 100.39    | 22,560    |
| protein 9    | 25,600,000 | 9,070,832,678  | 354.33       | 88.54     | 22,560    |
| protein 10   | 50,825,784 | 16,931,428,229 | 333.13       | 91.03     | 32,822    |




