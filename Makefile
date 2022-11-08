NAME = libdsa

CC = gcc
DEBUG_FLAGS = -g -Wall -Werror -Wextra -pedantic -Wshadow -Wpointer-arith -Wcast-align -Wwrite-strings -Wmissing-prototypes -Wmissing-declarations -Wredundant-decls -Wnested-externs -Winline -Wno-long-long -Wuninitialized -Wstrict-prototypes
RELEASE_FLAGS = -s -O3 -finline-functions

PREFIX = /usr
SRC_DIR = src
HDR_DIR = src
TEST_DIR = test
TEST_RUNNER = test_runner

SRCS = $(shell find $(SRC_DIR) -name "*.c")
HDRS = $(shell find $(HDR_DIR) -name "*.h")
OBJS = $(SRCS:.c=.o)

default: usage

usage:
	@echo make debug - build $(NAME)
	@echo make release - build optimized $(NAME)
	@echo make install - install $(NAME) in $(PREFIX)/lib/
	@echo make uninstall - uninstall $(NAME)
	@echo make clean - clean build artifacts
	@echo make check - run all test suites

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

.PHONY: $(TEST_RUNNER)
check: $(TEST_DIR)/*.c
	$(CC) $(TEST_DIR)/$(TEST_RUNNER).c -lcheck -o $(TEST_RUNNER)
	./$(TEST_RUNNER)