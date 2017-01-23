all:
	

clean:
	rm -rf *.o webserver




all: addtest sltest

addtest: add.c
        gcc -lpthread -lrt add.c -o addtest
sltest: sl.c
        gcc -lpthread -lrt sl.c -o sltest
clean:
        rm -rf sltest addtest
dist:
        rm -rf lab4-rishubandy.tgz
        tar -czf lab4-rishubandy.tgz add.c sl.c SortedList.h Makefile answers.txt graphs.pdf
