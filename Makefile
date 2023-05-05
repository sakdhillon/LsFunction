# infoDemo: infodemo.c
# 	gcc -Wall -std=c99 -o infoDemo infodemo.c

# test: test.c
# 	gcc -Wall -std=c99 -o test test.c

UnixLs: UnixLs.c
	gcc -Wall -std=c99 -o UnixLs UnixLs.c

clean: 
	rm -f UnixLs
	rm -f infoDemo
	rm -f a.out
	rm -f test
	rm -f *.o 