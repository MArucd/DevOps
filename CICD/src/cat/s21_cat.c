#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct arguments {
  int b, E, n, s, T, v;
} arguments;

arguments parser(int argc, char** argv) {
  arguments arg = {0};
  if (argc == 1) return arg;
  if (argv[1][0] == '-') {
    struct option long_options[] = {{"number", no_argument, NULL, 'n'},
                                    {"number-nonblank", no_argument, NULL, 'b'},
                                    {"squeeze-blank", no_argument, NULL, 's'},
                                    {0, 0, 0, 0}};
    int opt;
    while ((opt = getopt_long(argc, argv, "bnsEeTtv", long_options, 0)) != -1) {
      switch (opt) {
        case 'b':
          arg.b = 1;
          break;
        case 'n':
          arg.n = 1;
          break;
        case 's':
          arg.s = 1;
          break;
        case 'e':
          arg.E = 1;
          arg.v = 1;
          break;
        case 'E':
          arg.E = 1;
          break;
        case 't':
          arg.T = 1;
          arg.v = 1;
          break;
        case 'T':
          arg.T = 1;
          break;
        case 'v':
          arg.v = 1;
          break;
        case '?':
          exit(1);
        default:
          break;
      }
    }
  }
  return arg;
}

char v_output(char ch) {
  if (ch == '\n' || ch == '\t') return ch;
  // if(ch < 0){
  //     printf("M-");
  //     ch = ch & 0x7f;
  // }
  if (ch <= 31) {
    putchar('^');
    ch += 64;
  } else if (ch == 127) {
    putchar('^');
    ch = '?';
  }
  return ch;
}

void outline(arguments arg, char* line, int n) {
  for (int i = 0; i < n; i++) {
    if (arg.T && line[i] == '\t')
      printf("^I");
    else {
      if (arg.E && line[i] == '\n') putchar('$');
      if (arg.v) line[i] = v_output(line[i]);
      putchar(line[i]);
    }
  }
}

void output(arguments arg, FILE* fp) {
  char* line = NULL;
  size_t assline = 0;
  int read = 0;
  int line_cout = 1;
  int empty_ass = 0;
  read = getline(&line, &assline, fp);
  while (read != -1) {
    if (line[0] == '\n')
      empty_ass++;
    else
      empty_ass = 0;
    if (arg.s && empty_ass > 1) {
    } else {
      if (arg.n && !arg.b) {
        printf("%6d\t", line_cout);
        line_cout++;
      }
      if (arg.b && line[0] != '\n') {
        printf("%6d\t", line_cout);
        line_cout++;
      }
      outline(arg, line, read);
    }
    read = getline(&line, &assline, fp);
  }
  free(line);
}

void read_file(arguments arg, int argc, char** argv) {
  FILE* fp;
  if (argc <= optind) {
    fp = stdin;
    output(arg, fp);
  } else {
    int i = optind ? optind : 1;
    for (; i < argc; i++) {
      fp = fopen(argv[i], "r");
      if (fp == NULL) {
        fprintf(stderr, "s21_cat: %s: No such file or directory\n", argv[i]);
        exit(1);
      }
      output(arg, fp);
    }
  }
}

int main(int argc, char** argv) {
  arguments arg = parser(argc, argv);
  read_file(arg, argc, argv);
  return 0;
}