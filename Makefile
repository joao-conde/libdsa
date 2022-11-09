NAME = libdsa

CC = gcc

DEBUG_FLAGS = -g -Wall -Werror -Wextra -pedantic -Wshadow -Wpointer-arith -Wcast-align -Wwrite-strings -Wmissing-prototypes -Wmissing-declarations -Wredundant-decls -Wnested-externs -Winline -Wno-long-long -Wuninitialized -Wstrict-prototypes
RELEASE_FLAGS = -s -O3 -finline-functions
TEST_FLAGS = $(shell pkg-config --cflags --libs check) -g -Wall --coverage
COVERAGE_FLAGS = --function-summaries --use-hotness-colors --stdout

BIN_INSTALL = /usr/lib
INCLUDE_INSTALL = /usr/local/include

SRC_DIR = src
HDR_DIR = src/headers
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
	@echo make install - install $(NAME) in $(BIN_INSTALL)
	@echo make uninstall - uninstall $(NAME) from $(BIN_INSTALL)
	@echo make clean - clean build artifacts
	@echo make check - run all test suites
	@echo make coverage - run all test suites and measure coverage
	@echo make lint - lint source and test files

debug: $(OBJS)
	$(CC) -shared -o $(NAME).so $(OBJS) $(DEBUG_FLAGS)

release: $(OBJS)
	$(CC) -shared -o $(NAME).so $(OBJS) $(RELEASE_FLAGS)

install:
	cp $(NAME).so $(BIN_INSTALL)
	cp $(HDRS) $(INCLUDE_INSTALL)
	ldconfig

uninstall:
	-@$(RM) $(BIN_INSTALL)/$(NAME).so
	-@$(RM) $(INCLUDE_INSTALL)/$(NAME)*.h

clean:
	-@$(RM) $(OBJS)
	-@$(RM) $(NAME).so
	-@$(RM) $(TEST_RUNNER)
	-@$(RM) *.gcno *.gcda *.gcov

check:
	-@$(RM) $(TEST_RUNNER)
	-@$(RM) *.gcno *.gcda *.gcov
	$(CC) $(TEST_DIR)/$(TEST_RUNNER).c $(SRCS) $(TEST_FLAGS) -o $(TEST_RUNNER)
	./$(TEST_RUNNER)

coverage:
	$(MAKE) check
	gcov $(COVERAGE_FLAGS) $(COVS)

lint:
	cpplint --recursive $(HDR_DIR) $(SRC_DIR) $(TEST_DIR) 
