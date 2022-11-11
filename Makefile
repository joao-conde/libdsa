LIB = libdsa
INSTALL_BIN = /usr/lib
INSTALL_INCLUDE = /usr/include

DEBUG_FLAGS = -g -Wall -Werror -Wextra -pedantic -Wshadow -Wpointer-arith -Wcast-align -Wwrite-strings -Wmissing-prototypes -Wmissing-declarations -Wredundant-decls -Wnested-externs -Winline -Wno-long-long -Wuninitialized -Wstrict-prototypes
RELEASE_FLAGS = -s -O3 -finline-functions
TEST_FLAGS = $(shell pkg-config --cflags --libs check) -g -Wall --coverage

SRC = src
HDR = include
TEST = test

SRCS = $(shell find $(SRC) -name "*.c")
HDRS = $(shell find $(HDR) -name "*.h")
OBJS = $(SRCS:.c=.o)
COVS = $(SRCS:$(SRC)/%.c=runner-%.gcno)

default: usage

usage:
	@echo make debug - build $(LIB)
	@echo make release - build optimized $(LIB)
	@echo make install - install $(LIB) in \'$(INSTALL_BIN)\' and \'$(INSTALL_INCLUDE)\'
	@echo make uninstall - uninstall $(LIB) from \'$(INSTALL_BIN)\' and \'$(INSTALL_INCLUDE)\'
	@echo make clean - clean build artifacts
	@echo make check - run all test suites
	@echo make coverage - run all test suites and measure coverage
	@echo make lint - lint source and test files

debug: $(OBJS)
	gcc -shared -o $(LIB).so $(OBJS) $(DEBUG_FLAGS)

release: $(OBJS)
	gcc -shared -o $(LIB).so $(OBJS) $(RELEASE_FLAGS)

install:
	cp $(LIB).so $(INSTALL_BIN)
	cp $(HDRS) $(INSTALL_INCLUDE)
	ldconfig

uninstall:
	-@$(RM) $(INSTALL_BIN)/$(LIB).so
	-@$(RM) $(INSTALL_INCLUDE)/$(patsubst $(HDR)/%.h, "%.h", $(HDRS))

clean:
	-@$(RM) $(OBJS)
	-@$(RM) $(LIB).so
	-@$(RM) runner
	-@$(RM) *.gcno *.gcda *.gcov

check:
	$(MAKE) clean
	gcc $(TEST)/runner.c $(SRCS) $(TEST_FLAGS) -o runner
	./runner

coverage:
	$(MAKE) check
	gcov --function-summaries $(COVS)

lint:
	cpplint --recursive $(HDR) $(SRC) $(TEST) 
