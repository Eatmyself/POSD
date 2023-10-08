
.PHONY: directories clean stat

all: directories obj/iterator bin/ut_all

obj/iterator:
	g++ -std=c++11 -c src/iterator.cpp -o obj/iterator.o

bin/ut_all: test/ut_all.cpp test/ut_all.h src/iterator.h src/dfs_iterator.h src/file.h src/folder.h src/node.h src/null_iterator.h
	g++ -std=c++11 obj/iterator.o test/ut_all.cpp -o bin/ut_all -lgtest -lpthread

directories:
	mkdir -p bin obj

clean:
	rm -f bin/*

stat:
	wc src/* test/*
