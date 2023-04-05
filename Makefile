SHELL = /bin/bash

CC = clang
CXX = clang++

LIB = libdsa
INSTALL_BIN = /usr/lib
INSTALL_INCLUDE = /usr/include

DEBUG_FLAGS = -fPIC -shared -g -Wall -Werror -Wextra -pedantic -Wshadow -Wpointer-arith -Wcast-align -Wwrite-strings -Wmissing-prototypes -Wmissing-declarations -Wredundant-decls -Wnested-externs -Winline -Wno-long-long -Wuninitialized -Wstrict-prototypes
RELEASE_FLAGS = -fPIC -shared -s -O3 -finline-functions
TEST_FLAGS = -g -Wall --coverage
COVERAGE_REPORT_FLAGS = --function-summaries --use-colors --stdout
LINT_FLAGS = --extensions=c,cc,h --recursive
ASAN_FLAGS = -g -Wall -fno-sanitize-recover=all -fsanitize=address
LSAN_FLAGS = -g -Wall -fno-sanitize-recover=all -fsanitize=leak
MSAN_FLAGS = -g -Wall -fno-sanitize-recover=all -fsanitize=memory 
UBSAN_FLAGS = -g -Wall -fno-sanitize-recover=all -fsanitize=undefined
BENCHMARK_FLAGS = -x c++ -s -O3 -finline-functions

SRC = src
HDR = include
TEST = test
BENCH = benchmark
EXAMP = examples

SRCS = $(shell find $(SRC) -name "*.c")
HDRS = $(shell find $(HDR) -name "*.h")
INSTALL_HDRS = $(patsubst $(HDR)/%.h, "$(INSTALL_INCLUDE)/%.h", $(HDRS))
OBJS = $(SRCS:.c=.o)
COVS = $(patsubst %.c, runner-test-%.gcno, $(foreach src, $(SRCS), $(lastword $(subst /, , $(src)))))

.PHONY: usage debug release clean install uninstall test coverage coverage-report lint sanitize benchmark

default: usage

usage:
	@echo make debug - build $(LIB)
	@echo make release - build optimized $(LIB)
	@echo make clean - clean build, test and other artifacts
	@echo make install - install $(LIB) in \'$(INSTALL_BIN)\' and \'$(INSTALL_INCLUDE)\'
	@echo make uninstall - uninstall $(LIB) from \'$(INSTALL_BIN)\' and \'$(INSTALL_INCLUDE)\'
	@echo make test - run all test suites
	@echo make coverage - run all test suites and measure coverage
	@echo make coverage-report - run all test suites, measure coverage and display detailed report
	@echo make lint - lint headers, source and test files
	@echo make sanitize - check for memory leaks, undefined behavior and other vulnerabilities
	@echo make benchmark - run $(LIB) benchmarks comparing with C++ STL 

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
	gcov $(COVS)

coverage-report:
	$(MAKE) test
	gcov $(COVERAGE_REPORT_FLAGS) $(COVS)

lint:
	cpplint $(LINT_FLAGS) $(HDR) $(SRC) $(TEST) $(BENCH) $(EXAMP)

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
