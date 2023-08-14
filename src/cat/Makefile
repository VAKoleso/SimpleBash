CFLAGS = -Wall -Werror -Wextra
CC_DEFAULT = gcc
CC=$(CC_DEFAULT) $(CFLAGS)

all: clean s21_cat

s21_cat.o:
	$(CC) -c s21_cat.c -o s21_cat.o

s21_cat: s21_cat.o
	$(CC) s21_cat.o -o s21_cat

clean:
	rm -rf  *.o s21_cat 
