#ifndef FOO_H
#define FOO_H
#define NORMAL_TERMINATION 0
#define ABNORMAL_TERMINATION 1
#define EXECFAIL 1
#define EXECOK 0

/* This struct is passed to function runcommand. */

typedef struct 
{
  char **args;			/* A command vector as it is passed to exec. */
  int exit_status;		/* Exit status code returned by the program. */
  int termination;
  int *io;
} command_t;


/* Run a command in a subprocess. */

int runcommand (command_t *command);



#endif	/* FOO_H */
