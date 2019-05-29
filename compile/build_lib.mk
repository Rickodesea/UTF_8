#UTF_8 LIBRARY

INCLUDES = -I.
CFLAGS =-c
LFLAGS =
LIBS_FIRST =
LIBS_LAST =
SRCS = utf_8.c
APP_NAME = bin/utf_8.o
COMPILER = gcc

build:
	gcc -c -I. ./utf_8.c -o ./bin/utf_8.o
	gcc -c -fPIC -I. ./utf_8.c -o ./bin/utf_8.shared.o
	ar rcs ./bin/utf_8.a ./bin/utf_8.o
	gcc -shared ./bin/utf_8.shared.o -o ./bin/utf_8.so
