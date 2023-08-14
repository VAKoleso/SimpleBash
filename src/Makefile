CFLAGS = -Wall -Werror -Wextra
CC_DEFAULT = gcc
CC=$(CC_DEFAULT) $(CFLAGS) 

all: clean s21_cat s21_grep test

s21_cat.o:
	$(CC)-c cat/s21_cat.c -o cat/s21_cat.o

s21_cat: s21_cat.o
	$(CC)cat/s21_cat.o -o cat/s21_cat

s21_grep.o : 
	$(CC)-c grep/s21_grep.c -o grep/s21_grep.o

s21_grep : s21_grep.o 
	$(CC)grep/s21_grep.o -o grep/s21_grep

clean: 
	rm -rf grep/*.o grep/s21_grep cat/*.o cat/s21_cat *.txt test *.o

test.o:
	$(CC)-c test.c -o test.o

test: test.o
	sh test.sh
	$(CC) test.o -o test -lcheck
	./test

cpplint:
	cp ../materials/linters/CPPLINT.cfg CPPLINT.cfg
	python3 ../materials/linters/cpplint.py --extensions=c grep/*.c cat/*.c *.c
	rm -rf CPPLINT.cfg

cppcheck: 
	cppcheck --enable=all --suppress=missingIncludeSystem grep/*.c cat/*.c

check: cpplint cppcheck
	