/* lincalc
 *
 * Some code taken from CS 347 -- Micro shell
 * Sept 21, 2000,  Phil Nelson
 * Modified April 8, 2001 
 * Modified January 6, 2003
 * Modified January 8, 2017
 * Modified April 13, 2020 for assignment 1 by Harrison Saliba
 * Modified October 19, 2020 for lincalc by Harrison Saliba
 * 
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include "defn.h"


int exitval;
FILE *infile;

/* struct of available commands */
struct bi availcmd[] = {
  { .name = "quit", .exec = quitlc },
  { .name = "testable", .exec = quitlc },
  { .name = "testing", .exec = quitlc },
};
int navailcmd = sizeof(availcmd) / sizeof(availcmd[0]);

int main(int argc, char **argv) {

  /* Handle signals */
  signal(SIGINT, handlesig);

  /* Create buffer for reading */
  char buffer[LINELEN];
  int len;

  /* Initalize the input file as stdin */
  infile = stdin;

  /* Read from file if specified */
  if (argc > 1)
  {
    infile = fopen(argv[1], "r");
    if (infile == 0)
    {
      perror("Error opening file.");
      exit(127);
    }
  }

  while (1) {
    /* prompt and get line */
    if (infile == stdin) {
      fprintf(stderr, "[lincalc] ");
    }
    if (fgets(buffer, LINELEN, infile) != buffer) {
      break;
    }

    /* Get rid of \n at end of buffer. */
    len = strlen(buffer);
    if (buffer[len - 1] == '\n') {
      buffer[len - 1] = 0;
    }

    /* Remove comments */
    removeComments(buffer);

    /* Run it ... */
    processline(buffer, 0, 1);
  }

  if (!feof(infile)) {
    perror("read");
  }

  return 0;
}

int processline(char *line, int infd, int outfd) {

  /* Process the args */
  int argc = 0;
  char **argv = arg_parse(line, &argc);
  if (argc == 0) {
    return -1;
  }

  /* Do the job. */
  execbi(argc, argv);

  return 0;
}

/* Parse Arguments
 * 
 * Processes a string containing an executable command into an array of arguments.
 * 
 */
char **arg_parse(char *line, int *argcptr) {
  /* count argv */
  int count = 0;
  char *pos = line;
  while (*pos != '\0') {
    if (*pos == ' ') {
      pos++;
    } else {
      count++;
      while (*pos != '\0' && *pos != ' ') {
        if (*pos == '"') {
          pos++;
          while (*pos != '"') {
            if (*pos == '\0') {
              printf("Wrong number of double qoutes.\n");
              return NULL;
            }
            pos++;
          }
          pos++;
        } else {
          pos++;
        }
      }
    }
  }
  *argcptr = count;

  /* malloc size + 1 */
  char **argv = (char **)malloc(sizeof(char *) * (count + 1));
  argv[count] = NULL;

  /* assign pointers and add EOS chars */
  count = 0;
  pos = line;
  while (*pos != '\0') {
    if (*pos == ' ') {
      pos++;
    } else {
      argv[count] = pos;
      count++;
      while (*pos != '\0' && *pos != ' ') {
        if (*pos == '"') {
          pos++;
          while (*pos != '"') {
            pos++;
          }
          pos++;
        } else {
          pos++;
        }
      }
      if (*pos != '\0') {
        *pos = '\0';
        pos++;
      }
    }
  }

  /*remove qoutes */
  count--;
  char *nq;
  while (count >= 0) {
    pos = argv[count];
    nq = argv[count];
    while (*nq != '\0' && *pos != '\0') {
      while (*nq == '"') {
        nq++;
      }
      *pos = *nq;
      pos++;
      nq++;
    }
    *pos = '\0';
    count--;
  }

  return argv;
}


/* Remove comments
 * 
 * Removes all text following a '#' in a single line.
 * 
 */
int removeComments(char *line) {
  char *ptr = line;
  while (*ptr != '\0') {
    if (*ptr == '$') {
      ptr++;
      if (*ptr == '#') {
        ptr++;
      }
    } else if (*ptr == '#') {
      *ptr = '\0';
    } else {
      ptr++;
    }
  }
  return 0;
}

/* Run command (execute built-in)
 *
 * Runs command based on first string
 * 
 */
int execbi(int argc, char **argv) {
  /* loop thorugh availible commands */
  int matches = navailcmd;
  int pos = 0;
  while (matches > 1 && pos < strlen(argv[0])) {
    matches = 0;
    pos++;
    for (int ccmd = 0; ccmd < navailcmd; ccmd++) {
      if (strncmp(availcmd[ccmd].name, argv[0], pos) == 0) {
        matches++;
      }
    }
  }
  if (matches == 1) {
    for (int ccmd = 0; ccmd < navailcmd; ccmd++) {
      if (strncmp(availcmd[ccmd].name, argv[0], pos) == 0) {
        /* execute command */
        availcmd[ccmd].exec(argc, argv);
      }
    }
  } else if (matches > 1) {
    printf("Unknown command.\nDid you mean:\n");
    for (int ccmd = 0; ccmd < navailcmd; ccmd++) {
      if (strncmp(availcmd[ccmd].name, argv[0], pos) == 0) {
        printf("%s\n", availcmd[ccmd].name);
      }
    }
  } else {
    printf("Unknown command.\n");
  }
  return 0;
}

/* Exit
 *
 * Exits lincalc.
 * 
 */
void quitlc(int argc, char **argv) {
  if (argc == 1) {
    exit(0);
  } else if (argc > 1) {
    exit(atoi(argv[1]));
  }
  return;
}

/* Handle signals
 *
 * add 128 to the return value.
 */
void handlesig(int signal) {
  exitval = signal + 128;
}
