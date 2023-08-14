CFLAGS = -Wall -Werror -Wextra
CC_DEFAULT = gcc
CC=$(CC_DEFAULT) $(CFLAGS)

all: clean s21_grep

s21_grep.o:
	$(CC) -c s21_grep.c -o s21_grep.o

s21_grep: s21_grep.o
	$(CC) s21_grep.o -o s21_grep

clean:
	rm -rf *.o s21_grep
