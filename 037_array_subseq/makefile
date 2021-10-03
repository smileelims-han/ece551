test-subseq: test-subseq.o maxSeq.o
	gcc -o test-subseq test-subseq.c maxSeq.o
test-subseq.o: test-subseq.c
	gcc -std=gnu99 -Wall -pedantic -c test-subseq.c
maxSeq.o: maxSeq.c
	gcc -std=gnu99 -Wall -pedantic -c maxSeq.c
