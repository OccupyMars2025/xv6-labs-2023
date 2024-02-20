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