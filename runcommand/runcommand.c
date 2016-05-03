

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>

#include <foo.h>
#include <debug.h>

/* Execute a command in a subprocess as specified by argument 'command'. 
   See documentation of command_t for further information. */

int runcommand (command_t *command) 
{
  int pid, status;
  int aux;
  int pipefd[2];
  char c;
  
  pipe(pipefd);

  command->termination = ABNORMAL_TERMINATION;
  command->exit_status = EXIT_FAILURE;

  /* Create the subproccess. */

  if(command->io != NULL) {
    if(command->io[0] != -1) { dup2(command->io[0], STDIN_FILENO);}
    if(command->io[1] != -1) { dup2(command->io[1], STDOUT_FILENO);}
    if(command->io[2] != -1) { dup2(command->io[2], STDERR_FILENO);}
  }
  pid = fork();
  fail (pid<0, -1);

  if (pid>0)			/* Parent (caller). */
    {
      aux = wait (&status);
      fail (aux<0, -1);
      command->exit_status = WEXITSTATUS (status);

      close(pipefd[1]);
      if(read(pipefd[0], &c, 1) > 0)
        return -2;
      else
        return pid;
    }
  else				/* Child (subprocess). */
    {
      aux = execvp (command->args[0], command->args);

      close(pipefd[0]);
      write(pipefd[1], "o", 1);

      if (aux<0)
	exit (-1);
    }
  command->termination = NORMAL_TERMINATION;
  return pid;			/* Only parent reaches this point. */
}
