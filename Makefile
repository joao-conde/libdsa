LIB = libdsa
INSTALL_BIN = /usr/lib
INSTALL_INCLUDE = /usr/include

SHELL = /bin/bash

DEBUG_FLAGS = -g -Wall -Werror -Wextra -pedantic -Wshadow -Wpointer-arith -Wcast-align -Wwrite-strings -Wmissing-prototypes -Wmissing-declarations -Wredundant-decls -Wnested-externs -Winline -Wno-long-long -Wuninitialized -Wstrict-prototypes
RELEASE_FLAGS = -s -O3 -finline-functions
TEST_FLAGS = -g -Wall --coverage

SRC = src
HDR = include
TEST = test
BENCH = benchmark

SRCS = $(shell find $(SRC) -name "*.c")
HDRS = $(shell find $(HDR) -name "*.h")
INSTALL_HDRS = $(patsubst $(HDR)/%.h, "$(INSTALL_INCLUDE)/%.h", $(HDRS))
OBJS = $(SRCS:.c=.o)
COVS = $(patsubst %.c, runner-%.gcno, $(foreach src, $(SRCS), $(lastword $(subst /, , $(src)))))

default: usage

usage:
	@echo make debug - build $(LIB)
	@echo make release - build optimized $(LIB)
	@echo make install - install $(LIB) in \'$(INSTALL_BIN)\' and \'$(INSTALL_INCLUDE)\'
	@echo make uninstall - uninstall $(LIB) from \'$(INSTALL_BIN)\' and \'$(INSTALL_INCLUDE)\'
	@echo make check - run all test suites
	@echo make coverage - run all test suites and measure coverage
	@echo make coverage-report - run all test suites, measure coverage and display detailed report
	@echo make lint - lint headers, source and test files
	@echo make memcheck - analyze memory usage and report memory leaks
	@echo make clean - clean build and test artifacts

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

check:
	$(MAKE) clean
	gcc $(TEST)/runner.c $(SRCS) $(TEST_FLAGS) -o runner
	CK_FORK=no ./runner

coverage:
	$(MAKE) check
	gcov $(COVS)

coverage-report:
	$(MAKE) check
	gcov --function-summaries --use-colors --stdout $(COVS)

lint:
	cpplint --extensions=c,h --recursive $(HDR) $(SRC) $(TEST) 

memcheck:
	$(MAKE) clean
	gcc $(TEST)/runner.c $(SRCS) $(TEST_FLAGS) -o runner
	CK_FORK=no valgrind --error-exitcode=1 --leak-check=full -s ./runner

bench:
	$(MAKE) clean
	gcc $(BENCH)/vector.c $(SRCS) $(RELEASE_FLAGS) -o vectorc
	g++ $(BENCH)/vector.cpp -s -O3 -finline-functions -o vectorcpp

clean:
	-@$(RM) $(OBJS)
	-@$(RM) $(LIB).so
	-@$(RM) runner
	-@$(RM) *.gcno *.gcda *.gcov
