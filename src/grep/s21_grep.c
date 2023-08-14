#include <regex.h>
#include <stdio.h>
#include <stdlib.h>

char *s21_strcpy(char *dest, const char *src) {
  if (src != NULL && dest != NULL) {
    int i = 0;
    do {
      *(dest + i) = *(src + i);
      i++;
    } while (*(dest + i - 1) != '\0');
  }
  return dest;
}

char *s21_strcat(char *dest, const char *src) {
  int i = 0;
  while (*(dest + i) != '\0') {
    i++;
  }
  int k = 0;
  do {
    *(dest + i) = *(src + k);
    i++;
    k++;
  } while (*(dest + i - 1) != '\0');
  return dest;
}

void parser(int *err, char **cln, int *fl_e, int *fl_i, int *fl_v, int *fl_c,
            int *fl_l, int *fl_n, int *fl_h, char *capi, int *fl_s) {
  while (*cln && *err == 0) {
    if (**cln != '-') {
      cln++;
    } else {
      *cln += 1;
      while (**cln != '\0' && *err == 0) {
        if (**cln == 'e' || **cln == 'v' || **cln == 'i' || **cln == 'c' ||
            **cln == 'l' || **cln == 'n' || **cln == 'h' || **cln == 's') {
          if (**cln == 'e') {
            *fl_e = 1;
            *cln += 1;
            if (**cln == '\0') {
              *cln = NULL;
              cln++;
            }
            s21_strcat(capi, *cln);
            s21_strcat(capi, "|");
            break;
          }
          if (**cln == 'i') *fl_i = 1;
          if (**cln == 'v') *fl_v = 1;
          if (**cln == 'c') *fl_c = 1;
          if (**cln == 'l') *fl_l = 1;
          if (**cln == 'n') *fl_n = 1;
          if (**cln == 'h') *fl_h = 1;
          if (**cln == 's') *fl_s = 1;
          *cln += 1;
        } else {
          if (!*fl_s) printf("unknown --directories option");
          *err += 1;
        }
      }
      *cln = NULL;
      cln++;
    }
  }
}
void open_files(int fl_c, int fl_n, int fl_l, FILE *fp, int fl_v, regex_t regex,
                int number_files, char *capita, int fl_h) {
  char *line = NULL;
  size_t len = 0;
  int tmp = 0;
  int namber_lines = 0;
  while ((getline(&line, &len, fp)) != -1) {
    namber_lines++;
    if ((regexec(&regex, line, 0, NULL, 0)) == 0 && !fl_v) {
      if (!fl_c && !fl_l && !fl_n && !fl_h && number_files > 1)
        printf("%s:", capita);
      if (!fl_c && !fl_l && !fl_n) printf("%s", line);
      if (!fl_c && !fl_l && fl_n && !fl_h && number_files > 1)
        printf("%s:", capita);
      if (!fl_c && !fl_l && fl_n) printf("%d:%s", namber_lines, line);
      tmp += 1;
    }
    if ((regexec(&regex, line, 0, NULL, 0)) != 0 && fl_v) {
      if (!fl_c && !fl_l && !fl_n && !fl_h && number_files > 1)
        printf("%s:", capita);
      if (!fl_c && !fl_l && !fl_n) printf("%s", line);
      if (!fl_c && !fl_l && fl_n && !fl_h && number_files > 1)
        printf("%s:", capita);
      if (!fl_c && !fl_l && fl_n) printf("%d:%s", namber_lines, line);
      tmp++;
    }
  }
  if (fl_c && !fl_h && number_files > 1) {
    printf("%s:", capita);
  }
  if (fl_c && !fl_l) {
    printf("%d\n", tmp);
  }
  if (fl_c && fl_l && tmp > 0) {
    printf("1\n");
  } else if (fl_c && fl_l && tmp == 0) {
    printf("0\n");
  }
  if (fl_l && tmp > 0) {
    printf("%s\n", capita);
  }
  if (line) free(line);
  fclose(fp);
}

int main(int argc, char *argv[]) {
  int fl_e = 0, fl_i = 0, fl_v = 0, fl_c = 0, fl_l = 0, fl_n = 0, fl_h = 0,
      fl_s = 0, err = 0;

  char **cln, *capi = malloc(10000);
  s21_strcpy(capi, "(");
  cln = argv;
  argv++, argc--;
  parser(&err, cln, &fl_e, &fl_i, &fl_v, &fl_c, &fl_l, &fl_n, &fl_h, capi,
         &fl_s);
  if (!err) {
    char capita[256][256];
    int number_files = 0;
    while (argc) {
      if (*argv != NULL && fl_e == 0) {
        s21_strcat(capi, *argv);
        s21_strcat(capi, "|");
        fl_e = 1;
      } else if (*argv != NULL) {
        s21_strcpy(capita[number_files], *argv);
        number_files++;
      }
      argv++, argc--;
    }
    for (int i = 0; capi[i] != '\0'; i++) {
      argc = i;
    }
    capi[argc] = ')';
    if (err == 0) {
      for (int i = 0; i < number_files; i++) {
        regex_t regex;
        FILE *fp;
        if (fl_i) {
          regcomp(&regex, capi, REG_EXTENDED | REG_ICASE);
        } else {
          regcomp(&regex, capi, REG_EXTENDED);
        }
        if ((fp = fopen(capita[i], "r")) == NULL) {
          if (!fl_s) printf("Не удалось найти файл %s\n", capita[i]);
        } else {
          open_files(fl_c, fl_n, fl_l, fp, fl_v, regex, number_files, capita[i],
                     fl_h);
        }
        regfree(&regex);
      }
    }
  }
  free(capi);
  return 0;
}
