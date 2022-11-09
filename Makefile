NAME = libdsa

CC = gcc
LINTER = cpplint
COVERAGE = gcov

DEBUG_FLAGS = -g -Wall -Werror -Wextra -pedantic -Wshadow -Wpointer-arith -Wcast-align -Wwrite-strings -Wmissing-prototypes -Wmissing-declarations -Wredundant-decls -Wnested-externs -Winline -Wno-long-long -Wuninitialized -Wstrict-prototypes
RELEASE_FLAGS = -s -O3 -finline-functions
TEST_FLAGS = $(shell pkg-config --cflags --libs check) -g -Wall --coverage
TEST_ARTIFACTS = *.gcov *.gcno *.gcda
COVERAGE_FLAGS = --function-summaries --use-hotness-colors --stdout

PREFIX = /usr
SRC_DIR = src
HDR_DIR = src
TEST_DIR = test
TEST_RUNNER = runner

SRCS = $(shell find $(SRC_DIR) -name "*.c")
HDRS = $(shell find $(HDR_DIR) -name "*.h")
OBJS = $(SRCS:.c=.o)
COVS = $(SRCS:$(SRC_DIR)/%.c=$(TEST_RUNNER)-%.gcno)

default: usage

usage:
	@echo make debug - build $(NAME)
	@echo make release - build optimized $(NAME)
	@echo make install - install $(NAME) in $(PREFIX)/lib/
	@echo make uninstall - uninstall $(NAME) from $(PREFIX)/lib/
	@echo make clean - clean build artifacts
	@echo make check - run all test suites
	@echo make coverage - run all test suites and measure coverage
	@echo make lint - run $(LINTER) on source and test files

debug: $(OBJS)
	$(CC) -shared -o $(NAME).so $(OBJS) $(DEBUG_FLAGS)

release: $(OBJS)
	$(CC) -shared -o $(NAME).so $(OBJS) $(RELEASE_FLAGS)

install:
	cp $(NAME).so $(PREFIX)/lib/
	cp $(HDRS) $(PREFIX)/local/include
	ldconfig

uninstall:
	-@$(RM) $(PREFIX)/lib/$(NAME).so
	-@$(RM) $(PREFIX)/local/include/$(NAME)*.h

clean:
	-@$(RM) $(OBJS)
	-@$(RM) $(NAME).so
	-@$(RM) $(TEST_RUNNER)
	-@$(RM) $(TEST_ARTIFACTS)
	
check:
	$(CC) $(TEST_DIR)/$(TEST_RUNNER).c $(SRCS) $(TEST_FLAGS) -o $(TEST_RUNNER)
	./$(TEST_RUNNER)

coverage:
	-@$(RM) $(TEST_ARTIFACTS)
	$(MAKE) check
	$(COVERAGE) $(COVERAGE_FLAGS) $(COVS)

lint:
	$(LINTER) src/* test/*
