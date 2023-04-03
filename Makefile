LIB = libdsa
INSTALL_BIN = /usr/lib
INSTALL_INCLUDE = /usr/include

SHELL = /bin/bash

DEBUG_FLAGS = -g -Wall -fsanitize=address,undefined -Werror -Wextra -pedantic -Wshadow -Wpointer-arith -Wcast-align -Wwrite-strings -Wmissing-prototypes -Wmissing-declarations -Wredundant-decls -Wnested-externs -Winline -Wno-long-long -Wuninitialized -Wstrict-prototypes
RELEASE_FLAGS = -s -O3 -finline-functions
TEST_FLAGS = -g -Wall --coverage
MEMCHECK_FLAGS = -s -O3 -finline-functions
BENCHMARK_FLAGS = -s -O3 -finline-functions

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

.PHONY: usage debug release clean install uninstall test coverage coverage-report lint memcheck benchmark

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
	@echo make memcheck - analyze memory usage and report memory leaks
	@echo make benchmark - run $(LIB) benchmarks comparing with C++ STL 

debug:
	gcc $(DEBUG_FLAGS) -fPIC -shared -o $(LIB).so $(SRCS)

release:
	gcc $(RELEASE_FLAGS) -fPIC -shared -o $(LIB).so $(SRCS)

install:
	cp $(LIB).so $(INSTALL_BIN)
	cp $(HDRS) $(INSTALL_INCLUDE)
	ldconfig

uninstall:
	-@$(RM) $(INSTALL_BIN)/$(LIB).so
	-@$(RM) $(INSTALL_HDRS)

test:
	$(MAKE) clean
	gcc -o runner-test $(TEST_FLAGS) $(TEST)/runner.c $(SRCS)
	./runner-test

coverage:
	$(MAKE) test
	gcov $(COVS)

coverage-report:
	$(MAKE) test
	gcov --function-summaries --use-colors --stdout $(COVS)

lint:
	cpplint --extensions=c,cc,h --recursive $(HDR) $(SRC) $(TEST) $(BENCH) $(EXAMP)

memcheck:
	$(MAKE) clean
	gcc -o runner-test $(MEMCHECK_FLAGS) $(TEST)/runner.c $(SRCS)
	g++ -o runner-bench $(MEMCHECK_FLAGS) $(BENCH)/*.cc $(BENCH)/*.c $(SRCS)
	valgrind --error-exitcode=1 --leak-check=full --track-origins=yes -s ./runner-test
	valgrind --error-exitcode=1 --leak-check=full --track-origins=yes -s ./runner-bench

benchmark:
	$(MAKE) clean
	g++ -o runner $(BENCHMARK_FLAGS) $(BENCH)/*.cc $(BENCH)/*.c $(SRCS)
	./runner

clean:
	-@$(RM) $(OBJS)
	-@$(RM) $(LIB).so
	-@$(RM) runner*
	-@$(RM) *.gcno *.gcda *.gcov
