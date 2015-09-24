# install install R and tikzdevice package (see below)

# You can install the package by calling
# install.packages("filehash", repos="http://cran.r-project.org") and
# install.packages("tikzDevice", repos="http://R-Forge.R-project.org") in R.
#

# Run: R --vanilla < memory.R
require(tikzDevice)

t <- read.table("memory_total.dat")
names(t) <- c("x","rlcsa","sadakane", "og", "new", "newdisk","rlcsa_peak","sadakane_peak", "og_peak", "new_peak", "newdisk_peak")
# replace k or K by 000 in strings col
t[["x"]] <- gsub("K|k","000",as.character(t[["x"]]))
# V2 corresponds to new algorithm
# V3 corresponds to 

tikz("memory_total.tex", width = 5.0, height = 2.8, standAlone = T)

par(mar=c(4, 4, 0.5, 0.5) + 0.1)

plot(c(),c(), xlim=c(0,300000), ylim=c(0,42),
     xlab="Number of strings",ylab="Gbytes (total memory)",
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

##peak

rlcsa_col_peak <- "green"
sadakane_col_peak <- "red"
og_col_peak <- "black"
new_mem_col_peak <- "blue"
new_disk_col_peak <- "blue"


rlcsa_pch_peak <- 2 # point symbol is a triangle
sadakane_pch_peak <- 4 # point symbol is a circle
og_pch_peak <- 3
new_mem_pch_peak <- 1
new_disk_pch_peak <- 5


lines(t[["x"]], t[["sadakane"]], type="b",col=sadakane_col, pch=sadakane_pch)
lines(t[["x"]], t[["rlcsa"]], type="b", col=rlcsa_col, pch=rlcsa_pch)
lines(t[["x"]], t[["og"]], type="b",col=og_col, pch=og_pch)
lines(t[["x"]], t[["new"]], type="b", col=new_mem_col, pch=new_mem_pch)
lines(t[["x"]], t[["newdisk"]], type="b",col=new_disk_col, pch=new_disk_pch)

legend("topleft", legend=c("rlcsa","sadakane","og", "new", "newdisk"),
       col=c(rlcsa_col, sadakane_col, og_col, new_mem_col, new_disk_col),
       pch=c(rlcsa_pch, sadakane_pch, og_pch, new_mem_pch, new_disk_pch),
       bty="n",
       lty=1)

#lines(t[["x"]], t[["sadakane_peak"]], type="b",col=sadakane_col_peak, pch=sadakane_pch_peak)
#lines(t[["x"]], t[["rlcsa_peak"]], type="b", col=rlcsa_col_peak, pch=rlcsa_pch_peak)
#lines(t[["x"]], t[["og_peak"]], type="b",col=og_col_peak, pch=og_pch_peak)
#lines(t[["x"]], t[["new_peak"]], type="b", col=new_mem_col_peak, pch=new_mem_pch_peak)
#lines(t[["x"]], t[["newdisk_peak"]], type="b",col=new_disk_col_peak, pch=new_disk_pch_peak)

#legend("topleft", legend=c("rlcsa (total)","sadakane (total)","og (total)", "new (total)", "newdisk (total)", "rlcsa (peak)","sadakane (peak)","og (peak)", "new (peak)", "newdisk (peak)"),
#       col=c(rlcsa_col, sadakane_col, og_col, new_mem_col, new_disk_col, rlcsa_col_peak, sadakane_col_peak, og_col_peak, new_mem_col_peak, new_disk_col_peak),
#       pch=c(rlcsa_pch, sadakane_pch, og_pch, new_mem_pch, new_disk_pch, rlcsa_pch_peak, sadakane_pch_peak, og_pch_peak, new_mem_pch_peak, new_disk_pch_peak),
#       bty="n",
#       lty=1)

dev.off()
