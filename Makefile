NAME = libdsa

CC = gcc
LINTER=cpplint
COVERAGE=gcov

DEBUG_FLAGS = -g -Wall -Werror -Wextra -pedantic -Wshadow -Wpointer-arith -Wcast-align -Wwrite-strings -Wmissing-prototypes -Wmissing-declarations -Wredundant-decls -Wnested-externs -Winline -Wno-long-long -Wuninitialized -Wstrict-prototypes
RELEASE_FLAGS = -s -O3 -finline-functions
TEST_FLAGS = $(shell pkg-config --cflags --libs check)
COVERAGE_FLAGS = $(TEST_FLAGS) -g -Wall --coverage

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
	@echo make uninstall - uninstall $(NAME)
	@echo make clean - clean build artifacts
	@echo make check - run all test suites
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
	-@$(RM) *.gcov *.gcno *.gcda
	
check:
	$(CC) $(TEST_DIR)/$(TEST_RUNNER).c $(SRCS) $(TEST_FLAGS) -o $(TEST_RUNNER)
	./$(TEST_RUNNER)

coverage:
	-@$(RM) *.gcov *.gcno *.gcda
	$(CC) $(COVERAGE_FLAGS) -o $(TEST_RUNNER) $(TEST_DIR)/$(TEST_RUNNER).c $(SRCS)
	./$(TEST_RUNNER)
	$(COVERAGE) $(COVS)

lint:
	$(LINTER) src/* test/*
