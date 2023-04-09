SHELL = /bin/bash

CC = gcc
CXX = g++
COV = gcov
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
OBJS = $(patsubst %.c, %.o, $(foreach src, $(SRCS), $(lastword $(subst /, , $(src)))))
COVS = $(patsubst %.c, %.gcno, $(foreach src, $(SRCS), $(lastword $(subst /, , $(src)))))

LIB_FLAGS = -fPIC -shared
DEBUG_FLAGS = -g -Wall -Werror -Wextra -Wpedantic
RELEASE_FLAGS = -O3 -s -finline-functions
SANITIZER_FLAGS = -fno-sanitize-recover=all -fsanitize=address -fsanitize=leak -fsanitize=undefined
COVERAGE_FLAGS = --coverage
COVERAGE_REPORT_FLAGS = --function-summaries --use-colors --stdout
LINT_FLAGS = --recursive --extensions=c,cc,h

.PHONY: usage debug release clean install uninstall test coverage coverage-report lint benchmark examples

default: usage

usage:
	@echo make debug - compile $(LIB)
	@echo make release - compile $(LIB) with optimizations
	@echo make clean - clean build, test and other artifacts
	@echo make install - install $(LIB) in \'$(INSTALL_BIN)\' and \'$(INSTALL_INCLUDE)\'
	@echo make uninstall - uninstall $(LIB) from \'$(INSTALL_BIN)\' and \'$(INSTALL_INCLUDE)\'
	@echo make test - compile and run all test suites
	@echo make coverage - compile and run all test suites and measure coverage
	@echo make coverage-report - compile and run all test suites and display coverage report
	@echo make lint - lint headers and source files
	@echo make benchmark - compile and run $(LIB) benchmarks comparing with C++ STL 
	@echo make examples - compile and run examples

debug:
	$(MAKE) clean
	$(CC) -o $(LIB).so $(LIB_FLAGS) $(DEBUG_FLAGS) $(SANITIZER_FLAGS) $(SRCS)

release:
	$(MAKE) clean
	$(CC) -o $(LIB).so $(LIB_FLAGS) $(RELEASE_FLAGS) $(SRCS)

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
	$(MAKE) clean
	$(CC) -o runner-test $(DEBUG_FLAGS) $(SANITIZER_FLAGS) $(TEST)/*.c $(SRCS)
	ASAN_OPTIONS=allocator_may_return_null=1 ./runner-test

coverage:
	$(MAKE) clean
	$(CC) -c $(DEBUG_FLAGS) $(COVERAGE_FLAGS) $(SRCS)
	$(CC) -o runner-coverage $(COVERAGE_FLAGS) $(DEBUG_FLAGS) $(TEST)/*.c $(OBJS)
	./runner-coverage
	$(COV) $(COVS)

coverage-report:
	$(MAKE) clean
	$(CC) -c $(DEBUG_FLAGS) $(COVERAGE_FLAGS) $(SRCS)
	$(CC) -o runner-coverage-report $(COVERAGE_FLAGS) $(DEBUG_FLAGS) $(TEST)/*.c $(OBJS)
	./runner-coverage-report
	$(COV) $(COVERAGE_REPORT_FLAGS) $(COVS)

lint:
	$(LINT) $(LINT_FLAGS) $(HDR) $(SRC) $(TEST) $(BENCH) $(EXAMP)

benchmark:
	$(MAKE) clean
	$(CXX) -o runner-bench $(RELEASE_FLAGS) $(BENCH)/*.cc $(BENCH)/*.c $(SRCS) 
	./runner-bench

examples:
	$(MAKE) clean
	$(CC) -o runner-deque $(SANITIZER_FLAGS) $(EXAMP)/deque.c $(EXAMP)/mytype.c $(SRCS)
	$(CC) -o runner-list $(SANITIZER_FLAGS) $(EXAMP)/list.c $(EXAMP)/mytype.c $(SRCS)
	$(CC) -o runner-map $(SANITIZER_FLAGS) $(EXAMP)/map.c $(EXAMP)/mytype.c $(SRCS)
	$(CC) -o runner-pair $(SANITIZER_FLAGS) $(EXAMP)/pair.c $(EXAMP)/mytype.c $(SRCS)
	$(CC) -o runner-queue $(SANITIZER_FLAGS) $(EXAMP)/queue.c $(EXAMP)/mytype.c $(SRCS)
	$(CC) -o runner-stack $(SANITIZER_FLAGS) $(EXAMP)/stack.c $(EXAMP)/mytype.c $(SRCS)
	$(CC) -o runner-vector $(SANITIZER_FLAGS) $(EXAMP)/vector.c $(EXAMP)/mytype.c $(SRCS)
	./runner-deque
	./runner-list
	./runner-map
	./runner-pair
	./runner-queue
	./runner-stack
	./runner-vector
