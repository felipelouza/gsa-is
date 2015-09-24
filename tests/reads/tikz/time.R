# install install R and tikzdevice package (see below)

# You can install the package by calling
# install.packages("filehash", repos="http://cran.r-project.org") and
# install.packages("tikzDevice", repos="http://R-Forge.R-project.org") in R.
#

# Run: R --vanilla < time.R

require(tikzDevice)

t <- read.table("time.dat")
names(t) <- c("x","sais","saca-k","gsais", "gsaca-k")
# replace k or K by 000 in strings col
t[["x"]] <- gsub("K|k","000",as.character(t[["x"]]))
# V2 corresponds to new algorithm
# V3 corresponds to 

tikz("time.tex", width = 5.0, height = 2.8, standAlone = T)

par(mar=c(4, 4, 0.5, 0.5) + 0.1)

plot(c(),c(), xlim=c(0,12800000), ylim=c(0,600),
     xlab="Number of strings",ylab="Time in seconds",
     xaxt="n"
     )
axis(1, at=t[["x"]], labels=gsub("000$","K",t[["x"]]))
grid()

rlcsa_col <- "green"
sadakane_col <- "red"
og_col <- "black"
new_mem_col <- "blue"
new_disk_col <- "blue"


rlcsa_pch <- 2 # point symbol is a triangle
sadakane_pch <- 4 # point symbol is a circle
og_pch <- 3
new_mem_pch <- 1
new_disk_pch <- 5

lines(t[["x"]], t[["sais"]], type="b",col=sadakane_col, pch=sadakane_pch)
lines(t[["x"]], t[["saca-k"]], type="b", col=rlcsa_col, pch=rlcsa_pch)
lines(t[["x"]], t[["gsais"]], type="b",col=og_col, pch=og_pch)
lines(t[["x"]], t[["gsaca-k"]], type="b", col=new_mem_col, pch=new_mem_pch)

legend("topleft", legend=c("sais","saca-k","gsais", "gsaca-k"),
       col=c(rlcsa_col, sadakane_col, og_col, new_mem_col),
       pch=c(rlcsa_pch, sadakane_pch, og_pch, new_mem_pch),
       bty="n",
       lty=1)

dev.off()
