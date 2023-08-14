cd cat

./s21_cat -e ../text/*.txt >> ../s21_cat_log.txt

./s21_cat -benstv ../text/*.txt >> ../s21_cat_log.txt

./s21_cat -bn ../text/*.txt >> ../s21_cat_log.txt

./s21_cat --number-nonblank ../text/*.txt >> ../s21_cat_log.txt

./s21_cat -nnnnnn -ssssss -ttttt ../text/*.txt >> ../s21_cat_log.txt

cat -e ../text/*.txt >> ../cat_log.txt

cat -benstv ../text/*.txt >> ../cat_log.txt

cat -bn ../text/*.txt >> ../cat_log.txt

cat -b ../text/*.txt >> ../cat_log.txt

cat -nnnnnn -ssssss -ttttt ../text/*.txt >> ../cat_log.txt

cd ../grep

./s21_grep -e qw ../text/*.txt >> ../s21_grep_log.txt
grep -e qw ../text/*.txt >> ../grep_log.txt

./s21_grep -e qw -e qw ../text/*.txt >> ../s21_grep_log.txt
grep -e qw -e qw ../text/*.txt >> ../grep_log.txt

./s21_grep -e qw -e [a-z] ../text/*.txt -i >> ../s21_grep_log.txt
grep -e qw -e [a-z] ../text/*.txt -i >> ../grep_log.txt

./s21_grep -e qw -e qw ../text/*.txt -v >> ../s21_grep_log.txt
grep -e qw -e qw ../text/*.txt -v >> ../grep_log.txt

./s21_grep -e qw -e qw ../text/*.txt -c >> ../s21_grep_log.txt
grep -e qw -e qw ../text/*.txt -c >> ../grep_log.txt

./s21_grep -e qw -e qw ../text/*.txt -l >> ../s21_grep_log.txt
grep -e qw -e qw ../text/*.txt -l >> ../grep_log.txt

./s21_grep -e qw -e qw ../text/*.txt -n >> ../s21_grep_log.txt
grep -e qw -e qw ../text/*.txt -n >> ../grep_log.txt

./s21_grep -e qweasd -lvin ../text/*.txt >> ../s21_grep_log.txt
grep -e qweasd -lvin ../text/*.txt >> ../grep_log.txt

# ./s21_grep -e qweasd -lc ../text/*.txt >> ../s21_grep_log.txt
# grep -e qweasd -lc ../text/*.txt >> ../grep_log.txt
