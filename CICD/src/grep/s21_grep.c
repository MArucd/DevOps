#include "s21_grep.h"

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void add_pattern(arguments *arg, char *pattern) {
  if (pattern == NULL) {
    return;
  }
  int n = strlen(pattern);
  if (arg->len_pattern == 0) {
    arg->pattern = malloc(1024 * sizeof(char));
    arg->pattern[0] = '\0';
    arg->ass_pattern = 1024;
  }
  if (arg->ass_pattern < arg->len_pattern + n) {
    arg->pattern = realloc(arg->pattern, arg->ass_pattern * 2);
  }
  if (arg->len_pattern != 0) {
    strcat(arg->pattern + arg->len_pattern, "|");
    arg->len_pattern++;
  }
  arg->len_pattern += sprintf(arg->pattern + arg->len_pattern, "(%s)", pattern);
}

void regular_from_file(arguments *arg, char *path_to_file) {
  FILE *fp = fopen(path_to_file, "r");
  if (fp == NULL) {
    if (!arg->s) perror(path_to_file);
  }
  char *line = NULL;
  size_t asslen = 0;
  int read = getline(&line, &asslen, fp);
  while (read != -1) {
    if (line[read - 1] == '\n') line[read - 1] = '\0';
    add_pattern(arg, line);
    read = getline(&line, &asslen, fp);
  }
  free(line);
  fclose(fp);
}

arguments argument_parser(int argc, char **argv) {
  arguments arg = {0};
  int opt = 0;
  while ((opt = getopt_long(argc, argv, "e:ivclnhsf:o", NULL, NULL)) != -1) {
    switch (opt) {
      case 'e':
        arg.e = 1;
        add_pattern(&arg, optarg);
        break;
      case 'i':
        arg.i = REG_ICASE;
        break;
      case 'v':
        arg.v = 1;
        arg.o = 0;
        break;
      case 'c':
        arg.c = 1;
        break;
      case 'l':
        // arg.c = 1;
        arg.l = 1;
        break;
      case 'n':
        arg.n = 1;
        break;
      case 'h':
        arg.h = 1;
        break;
      case 's':
        arg.s = 1;
        break;
      case 'f':
        arg.f = 1;
        regular_from_file(&arg, optarg);
        break;
      case 'o':
        if (arg.v == 1) {
          arg.o = 0;
        } else
          arg.o = 1;
        break;
      default:
        printf(
            "usage: s21_grep [-cefhilnosv] [-e pattern] [-f file] [--null] "
            "[pattern] [file ...]");
        exit(1);
    }
  }
  if (arg.len_pattern == 0) {
    add_pattern(&arg, argv[optind]);
    optind++;
  }
  if (argc - optind == 1) {
    arg.h = 1;
  }
  return arg;
}

void line_output(char *line, int n) {
  for (int i = 0; i < n; i++) {
    putchar(line[i]);
  }
  if (line[n - 1] != '\n') putchar('\n');
}

void match_print(regex_t *preg, char *line) {
  regmatch_t match;
  int offset = 0;
  while (1) {
    int result = regexec(preg, line + offset, 1, &match, 0);
    if (result != 0) break;
    for (int i = match.rm_so; i < match.rm_eo; i++) {
      putchar(line[offset + i]);
    }
    putchar('\n');
    offset += match.rm_eo;
  }
}

void processFile(arguments arg, char *path, regex_t *preg) {
  FILE *fp = fopen(path, "r");
  if (fp == NULL) {
    if (!arg.s) perror(path);
    return;
  }
  char *line = NULL;
  size_t asslen = 0;
  int read = 0;
  int line_count = 1;
  int counter = 0;

  read = getline(&line, &asslen, fp);
  while (read != -1) {
    int result = regexec(preg, line, 0, NULL, 0);
    if ((result == 0 && !arg.v) || (arg.v && result != 0)) {
      if (!arg.c && !arg.l) {
        if (!arg.h) printf("%s:", path);
        if (arg.n) printf("%d:", line_count);
        if (arg.o) {
          match_print(preg, line);
        } else {
          line_output(line, read);
        }
      }
      counter++;
    }
    read = getline(&line, &asslen, fp);
    line_count++;
  }
  free(line);
  if (arg.c) {
    if (!arg.h) printf("%s:", path);
    printf("%d\n", counter);
  }
  if (arg.l && counter > 0) printf("%s\n", path), fclose(fp);
}

void output(arguments arg, int argc, char **argv) {
  regex_t preg;
  int error = regcomp(&preg, arg.pattern, REG_EXTENDED | arg.i);
  if (error) perror("Error");
  for (int i = optind; i < argc; i++) {
    processFile(arg, argv[i], &preg);
  }
  regfree(&preg);
}

int main(int argc, char **argv) {
  if (argc > 1) {
    arguments arg = argument_parser(argc, argv);
    output(arg, argc, argv);
    free(arg.pattern);
  } else
    printf(
        "usage: s21_grep [-cefhilnosv] [-e pattern] [-f file] [--null] "
        "[pattern] [file ...]");
  return 0;
}
