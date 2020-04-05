CCFLAGS:=-std=c11 -pedantic

FACTORAL:=factorial
BINSERACH:=binsearch

factorial:
	gcc -O2 factorial_tailrec.c $(CCFLAGS) -o $(FACTORAL)

binsearch:
	gcc -O2 prefetch_binsearch.c $(CCFLAGS) -o $(BINSERACH)

time_binsearch:
	/usr/bin/time -v ./$(BINSERACH)

time_binsearch_prefetched:
	DO_PREFETCH=1  /usr/bin/time -v ./$(BINSERACH)

valngrid_binsearch_no_prefetch:
	valgrind --tool=cachegrind ./$(BINSERACH)

valngrid_binsearch_prefetched:
	DO_PREFETCH=1 valgrind --tool=cachegrind ./$(BINSERACH)

clean:
	$(RM) -r $(FACTORAL) $(BINSERACH) *.out*