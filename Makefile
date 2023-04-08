SHELL = /bin/bash

CC = clang
CXX = clang++
COV = llvm-cov gcov
LINT = cpplint

LIB = libdsa
INSTALL_BIN = /usr/lib
INSTALL_INCLUDE = /usr/include

SRC = src
HDR = include
TEST = test
BENCH = benchmark
EXAMP = examples

SRCS = $(shell find $(SRC) -name "*.c")
HDRS = $(shell find $(HDR) -name "*.h")
INSTALL_HDRS = $(patsubst $(HDR)/%.h, "$(INSTALL_INCLUDE)/%.h", $(HDRS))
OBJS = $(SRCS:.c=.o)
COVS = $(foreach src, $(SRCS), $(lastword $(subst /, , $(src))))

DEBUG_FLAGS = -fPIC -shared -g -Wall -Werror -Wextra -pedantic -Wshadow -Wpointer-arith -Wcast-align -Wwrite-strings -Wmissing-prototypes -Wmissing-declarations -Wredundant-decls -Wnested-externs -Winline -Wno-long-long -Wuninitialized -Wstrict-prototypes
RELEASE_FLAGS = -fPIC -shared -s -O3 -finline-functions
TEST_FLAGS = -g -Wall -O0 -fprofile-arcs -ftest-coverage
LINT_FLAGS = --extensions=c,cc,h --recursive
ASAN_FLAGS = -g -Wall -fno-sanitize-recover=all -fsanitize=address
LSAN_FLAGS = -g -Wall -fno-sanitize-recover=all -fsanitize=leak
MSAN_FLAGS = -g -Wall -fno-sanitize-recover=all -fsanitize=memory 
UBSAN_FLAGS = -g -Wall -fno-sanitize-recover=all -fsanitize=undefined
BENCHMARK_FLAGS = -x c++ -s -O3 -finline-functions

.PHONY: usage debug release clean install uninstall test coverage lint sanitize benchmark examples

default: usage

usage:
	@echo make debug - compile $(LIB)
	@echo make release - compile $(LIB) with optimizations
	@echo make clean - clean build, test and other artifacts
	@echo make install - install $(LIB) in \'$(INSTALL_BIN)\' and \'$(INSTALL_INCLUDE)\'
	@echo make uninstall - uninstall $(LIB) from \'$(INSTALL_BIN)\' and \'$(INSTALL_INCLUDE)\'
	@echo make test - compile and run all test suites
	@echo make coverage - compile and run all test suites and measure coverage
	@echo make lint - lint headers, source and test files
	@echo make sanitize - compile and run all test suites and check for memory leaks, undefined behavior and other vulnerabilities
	@echo make benchmark - compile and run $(LIB) benchmarks comparing with C++ STL 
	@echo make examples - compile and run examples

debug:
	$(CC) -o $(LIB).so $(DEBUG_FLAGS) $(SRCS)

release:
	$(CC) -o $(LIB).so $(RELEASE_FLAGS) $(SRCS)

clean:
	-@$(RM) $(OBJS)
	-@$(RM) $(LIB).so
	-@$(RM) runner*
	-@$(RM) *.gcno *.gcda *.gcov

install:
	cp $(LIB).so $(INSTALL_BIN)
	cp $(HDRS) $(INSTALL_INCLUDE)
	ldconfig

uninstall:
	-@$(RM) $(INSTALL_BIN)/$(LIB).so
	-@$(RM) $(INSTALL_HDRS)

test:
	$(CC) -o runner-test $(TEST_FLAGS) $(TEST)/runner.c $(SRCS)
	./runner-test

coverage:
	$(MAKE) test
	$(COV) $(COVS)

lint:
	$(LINT) $(LINT_FLAGS) $(HDR) $(SRC) $(TEST) $(BENCH) $(EXAMP)

sanitize:
	$(CC) -o runner-asan $(ASAN_FLAGS) $(TEST)/runner.c $(SRCS)
	$(CC) -o runner-lsan $(LSAN_FLAGS) $(TEST)/runner.c $(SRCS)
	$(CC) -o runner-msan $(MSAN_FLAGS) $(TEST)/runner.c $(SRCS)
	$(CC) -o runner-ubsan $(UBSAN_FLAGS) $(TEST)/runner.c $(SRCS)
	ASAN_OPTIONS=allocator_may_return_null=1 ./runner-asan
	LSAN_OPTIONS=allocator_may_return_null=1 ./runner-lsan
	MSAN_OPTIONS=allocator_may_return_null=1 ./runner-msan
	./runner-ubsan

benchmark:
	$(CXX) -o runner-bench $(BENCHMARK_FLAGS) $(BENCH)/*.cc $(BENCH)/*.c $(SRCS) 
	./runner-bench

examples:
	$(CC) -o runner-deque $(EXAMP)/deque.c $(EXAMP)/mytype.c $(SRCS)
	$(CC) -o runner-list $(EXAMP)/list.c $(EXAMP)/mytype.c $(SRCS)
	$(CC) -o runner-map $(EXAMP)/map.c $(EXAMP)/mytype.c $(SRCS)
	$(CC) -o runner-pair $(EXAMP)/pair.c $(EXAMP)/mytype.c $(SRCS)
	$(CC) -o runner-queue $(EXAMP)/queue.c $(EXAMP)/mytype.c $(SRCS)
	$(CC) -o runner-stack $(EXAMP)/stack.c $(EXAMP)/mytype.c $(SRCS)
	$(CC) -o runner-vector $(EXAMP)/vector.c $(EXAMP)/mytype.c $(SRCS)
	./runner-deque
	./runner-list
	./runner-map
	./runner-pair
	./runner-queue
	./runner-stack
	./runner-vector
