
.PHONY: directories clean stat

all: directories bin/ut_all

bin/ut_all: test/ut_all.cpp test/ut_all.h src/iterator.h src/dfs_iterator.h src/file.h src/folder.h src/node.h src/null_iterator.h
	g++ -std=c++11 test/ut_all.cpp -o bin/ut_all -lgtest -lpthread

directories:
	mkdir -p bin

clean:
	rm -f bin/*

stat:
	wc src/* test/*
