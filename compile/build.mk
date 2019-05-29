#Program

INCLUDES = -I.
CFLAGS =
LFLAGS =
LIBS_FIRST =
LIBS_LAST =
SRCS = $(wildcard *.c */*.c)
APP_NAME = bin/utf_8
COMPILER = gcc

build:
	$(COMPILER) $(CFLAGS) $(INCLUDES) $(SRCS) -o $(APP_NAME) $(LIBS_FIRST) $(LFLAGS) $(LIBS_LAST)
