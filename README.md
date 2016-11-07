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

