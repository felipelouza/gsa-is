#gsa-is

This code is an implementation of gSAIS and gSACA-K [1], which extend the
linear-time suffix sorting algorithms SAIS [2] and SACA-K [3] to compute the
generalized suffix array for a collection of strings, maintaining their
theoretical bounds and improving their practical performance.

--

Moreover, we show how gSAIS and gSACA-K can be modified to also compute the
longest common prefix (LCP) array and the document array (DA) as a byproduct,
with the same theoretical bounds [3].

--

Our algorithms, gSACA-K, gSACA-K+LCP and gSACA-K+DA are optimal for strings
from constant alphabets. Experimental results have shown that our algorithms
are fast with a very small memory footprint.


--
##run:

To run a test type:

```sh
make
make run DIR=dataset INPUT=input-10000.txt K=10000 MODE=6
```

One can change to 64 bits integers (when n > 2^31) in lib/utils.h, setting m64
to 1.

```sh
make clean
make 
```

--

**Settings:**

MODE parameter specifies which algorithm is called by main.c:

* 1:  SAIS\* 
* 2:  SACA-K\* 
* 3:  SAIS  
* 4:  SACA-K 
* 5:  gSAIS
* 6:  gSACA-K

SAIS\* and SACA-K\* are versions that receive an integer alphabet as input.

--

**LCP-array:**

MODE parameter:

* 7:  gSAIS+LCP
* 8:  gSACA-K+LCP

```sh
make run MODE=8
```

One can compute LCP after SA construction using Phi-algorithm [5]:

```sh
make run MODE=6 LCP_COMPUTE=1
```

--

**Document-array:**

MODE parameter:

* 9:  gSAIS+DA
* 10: gSACA-K+DA

```sh
make run MODE=10
```

One can compute DA after SA construction using a variation of Algorithm 7.30 from Ohlebusch's book [6, page 347]:

```sh
make run MODE=6 DA_COMPUTE=1
```

Alternatively, DA can be computed with a bitvector in external/bitvector/main.cpp, implemented using [sdsl-lite v.2](https://github.com/simongog/sdsl-lite). 

```sh
cd external/bitvector/
make
make run MODE=6 SDV=0
```

SDV=1 uses a sparse bitvector.

--

**Validate:**

One can check if the output produced is correct:

```sh
make run CHECK=1
```

**Output:**

One can output SA (LCP and DA) as $DIR$INPUT.sa (.lcp and .da):

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

\[1\] Louza, F. A., Gog, S., Telles, G. P., Induced Suffix Sorting for String Collections. In Proc. DCC, pp. 43-58, 2016, [IEEE](http://ieeexplore.ieee.org/document/7786148/).

\[2\] Nong G., Zhang S., Chan W. H., Two efficient algorithms for linear time suffix array construction, IEEE Trans. Comput., vol. 60, no. 10, pp. 1471–1484, 2011

\[3\] Nong, G., Practical linear-time O(1)-workspace suffix sorting for constant alphabets, ACM Trans. Inform. Syst., vol. 31, no. 3, pp. 1–15, 2013

\[4\] Louza, F. A., Gog, S., and Telles, G. P., Inducing enhanced suffix arrays for string collections. Submitted to a journal, pages 1–34.

\[5\] Kärkkäinen, J., Manzini, G., & Puglisi, S. J. (2009). Permuted Longest-Common-Prefix Array. In G. Kucherov & E. Ukkonen (Eds.), Proc. CPM (Vol. 5577, pp. 181–192).

\[6\] Ohlebusch, E., Bioinformatics Algorithms: Sequence Analysis, Genome Rearrangements, and Phylogenetic Reconstruction. Oldenbusch Verlag, 2013.

