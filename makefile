.PHONY: clean dirs

CFLAGS = -std=c++11 -Wfatal-errors -Wall 
LIBS = -lgtest -lpthread

UT_ALL = test/ut_all.cpp
TEST_HEADERS = test/ut_iterator.h test/ut_file.h test/ut_folder.h test/ut_node.h test/ut_visitor.h test/ut_tree_visitor.h test/ut_file_system_builder.h

SRC_HEADERS = src/file.h src/folder.h src/node.h src/link.h src/iterator.h src/null_iterator.h src/dfs_iterator.h src/visitor.h src/find_by_name_visitor.h src/stream_out_visitor.h src/order_by.h src/tree_visitor.h src/file_system_builder.h src/file_system_parser.h src/file_system_scanner.h 

all: dirs bin/ut_all

bin/ut_all: $(UT_ALL) $(TEST_HEADERS) $(SRC_HEADERS)
	g++ $(CFLAGS) -o $@ $<  $(LIBS) 

clean:
	rm -rf bin obj

dirs:
	mkdir -p bin obj
