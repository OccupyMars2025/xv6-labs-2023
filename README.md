## https://pdos.csail.mit.edu/6.1810/2023/labs/pgtbl.html
## Q: In this lab, we need to define "LAB_PGTBL", where is it defined ?
## A: In "./Makefile":
```make

ifdef LAB
LABUPPER = $(shell echo $(LAB) | tr a-z A-Z)
XCFLAGS += -DSOL_$(LABUPPER) -DLAB_$(LABUPPER)
endif


ifeq ($(LAB),pgtbl)
UPROGS += \
	$U/_pgtbltest
endif

grade:
	@echo $(MAKE) clean
	@$(MAKE) clean || \
          (echo "'make clean' failed.  HINT: Do you have another running instance of xv6?" && exit 1)
	./grade-lab-$(LAB) $(GRADEFLAGS)

```
## and in "conf/lab.mk", we have "LAB=pgtbl"

## If you want to check each PTE carefully, you can use check_page_table.py in this branch

## Q: why are XRW = 0 in L2 and L1 PTEs?
## A: indicate that it is a not a leaf PTE

```
Goal: efficiently detect which pages have been accessed
  Idea: exploit hardware page-table walk:
    it sets PTE_A when page is accessed (read or write)
    it sets PTE_D when page is written ("made dirty")
```