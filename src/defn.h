/* defn.h
 *
 * October 19, 2020 Harrison Saliba
 *  
 */

/* Definitions */

#define LINELEN 1024

/* Prototypes */

int processline(char *line, int infd, int outfd);
char **arg_parse(char *line, int *argcptr);
int removeComments(char *line);
int execbi(int argc, char **argv);
void handlesig(int signal);