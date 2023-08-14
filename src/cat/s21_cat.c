#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

void getopt_on(int argc, char **argv, int *fl_b, int *fl_e, int *fl_n,
               int *fl_s, int *fl_t, int *fl_v,
               const struct option *long_options, int *err) {
  int rez = 0;
  while ((rez = getopt_long(argc, argv, "benstvTE", long_options, NULL)) !=
             -1 &&
         *err != 1) {
    switch (rez) {
      case 'b':
        *fl_b = 1;
        break;
      case 'e':
        *fl_e = 1;
        *fl_v = 1;
        break;
      case 'n':
        *fl_n = 1;
        break;
      case 's':
        *fl_s = 1;
        break;
      case 't':
        *fl_t = 1;
        *fl_v = 1;
        break;
      case 'v':
        *fl_v = 1;
        break;
      case 'E':
        *fl_e = 1;
        break;
      case 'T':
        *fl_t = 1;
        break;
      case '?':
        *err = 1;
        break;
    }
  }
}

void flag_n(int fl_n, int fl_b, int *count, int hch) {
  if (fl_n == 1 && fl_b == 0) {
    if (hch == '\n') {
      printf("%6d\t", *count);
      *count += 1;
    }
  }
}

void flag_b(int fl_b, int hch, int ch, int *count) {
  if (fl_b == 1) {
    if (hch == '\n' && ch != '\n') {
      printf("%6d\t", *count);
      *count += 1;
    }
  }
}

void flag_ev(int fl_e, int fl_v, int ch, int *tmp_vt) {
  if (fl_e == 1) {
    if (ch == '\n') {
      printf("$");
    }
  }
  if (fl_v == 1) {
    if (-1 < ch && ch != 9 && ch != 10 && ch < 32) {
      printf("^%c", ch + 64);
      *tmp_vt = 1;
    }
  }
}

void flag_t(int fl_t, int ch, int *tmp_vt) {
  if (fl_t == 1) {
    if (ch == '\t') {
      printf("^I");
      *tmp_vt = 1;
    }
  }
}
void flag_s(int *tmp_s, int fl_s, int ch) {
  if (fl_s == 1) {
    if (ch == '\n') {
      *tmp_s += 1;
    } else {
      *tmp_s = 0;
    }
  }
}

void gets_on(int fl_b, int fl_e, int fl_n, int fl_s, int fl_t, int fl_v,
             FILE *fp) {
  char hch = '\n';
  int count = 1;
  int tmp_s = 0;
  char ch;

  while ((ch = getc(fp)) != EOF) {
    int tmp_vt;
    tmp_vt = 0;

    flag_s(&tmp_s, fl_s, ch);

    if (tmp_s < 3) {
      flag_n(fl_n, fl_b, &count, hch);

      flag_b(fl_b, hch, ch, &count);

      flag_ev(fl_e, fl_v, ch, &tmp_vt);

      flag_t(fl_t, ch, &tmp_vt);

      if (tmp_vt != 1) {
        printf("%c", ch);
      }
    }
    hch = ch;
  }
}

int main(int argc, char **argv) {
  int fl_b = 0;
  int fl_e = 0;
  int fl_n = 0;
  int fl_s = 0;
  int fl_t = 0;
  int fl_v = 0;
  int err = 0;

  const struct option long_options[] = {{"number-nonblank", 0, 0, 'b'},
                                        {"number", 0, 0, 'n'},
                                        {"squeeze-blank", 0, 0, 's'},
                                        {NULL, 0, NULL, 0}};

  getopt_on(argc, argv, &fl_b, &fl_e, &fl_n, &fl_s, &fl_t, &fl_v, long_options,
            &err);

  argv++;
  int tmp = 0;
  while (*argv && !err) {
    if (**argv == '-' && tmp == 0) {
      argv++;
    } else {
      FILE *fp;
      char *name = *argv;

      if ((fp = fopen(name, "r")) == NULL) {
        printf("Не удалось открыть файл");
        getchar();
        break;
      } else {
        gets_on(fl_b, fl_e, fl_n, fl_s, fl_t, fl_v, fp);

        fclose(fp);
        argv++;
        tmp = 1;
      }
    }
  }
  return 0;
}
