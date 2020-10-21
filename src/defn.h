/* defn.h
 *
 * October 19, 2020 Harrison Saliba
 *  
 */

/* Definitions */

#define LINELEN 1024

/* Structure Prototypes */

struct bi {
  char *name;
  void (*exec)(int, char **);
};

/* Command Prototypes */

void quitlc(int argc, char **argv);
void loadvar(int argc, char **argv);
void displayvar(int argc, char **argv);

/* lincalc Function Prototypes */

int processline(char *line, int infd, int outfd);
char **arg_parse(char *line, int *argcptr);
int removeComments(char *line);
int execbi(int argc, char **argv);
void handlesig(int signal);