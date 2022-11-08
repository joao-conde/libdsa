NAME := libdsa

CC=gcc
WARNINGS := -Wall -Werror -Wextra -pedantic -Wshadow -Wpointer-arith -Wcast-align -Wwrite-strings -Wmissing-prototypes -Wmissing-declarations -Wredundant-decls -Wnested-externs -Winline -Wno-long-long -Wuninitialized -Wstrict-prototypes
CFLAGS += -std=c17 -I$(HDR_DIR) -c -fpic -nostdlib $(WARNINGS)

PREFIX := /usr
SRC_DIR := src
HDR_DIR := src

SRCS := $(shell find $(SRC_DIR) -name "*.c")
HDRS := $(shell find $(HDR_DIR) -name "*.h")
OBJS := $(SRCS:.c=.o)

default: usage

usage:
	@echo make debug - build library
	@echo make release - build optimized library
	@echo make clean - clean build artifacts
	@echo make install - install library in $(PREFIX)/lib/
	@echo make uninstall - uninstall library
	@echo make reinstall - uninstall and install library

release: $(OBJS)
	$(CC) -shared -o $(NAME).so $(OBJS) -s

debug: $(OBJS)
	$(CC) -shared -o $(NAME).so $(OBJS) -g

install:
	cp $(NAME).so $(PREFIX)/lib/
	cp $(HDRS) $(PREFIX)/local/include
	ldconfig

uninstall:
	-@$(RM) $(PREFIX)/lib/$(NAME).so
	-@$(RM) $(PREFIX)/local/include/$(NAME)*.h

reinstall: uninstall install

clean:
	-@$(RM) $(OBJS)
	-@$(RM) $(NAME).so
