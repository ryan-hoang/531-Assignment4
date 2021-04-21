#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/*
Methods:
fork -
execlp -
wait -
signal
dup

Macros:
WEXITSTATUS-
WTERMSIG-
WSTOPSIG-
WIFCONTINUED-
*/
int cs531_system(char* command);

int main(int argc, char *argv[])
{
  int status;
  status = cs531_system(argv[1]);
  printf("\nParent process is sleeping...\n");
  sleep(10);
  return status;
}

int cs531_system(char* command)
{
  int status = 0;
  pid_t child_pid, w;

  switch(child_pid = fork())
  {
    case -1: //fork failed
      status = -1;
      break;

    case 0: //in child process
      execlp("/bin/sh", "sh", "-c", command, (char*) NULL);
      perror("Child Process: Could not execute command.");
      exit(-1);
      break;

    default: //in parent process, wait for child to terminate
      signal(SIGINT, SIG_IGN);

      do
      {
        w = waitpid(child_pid, &status, WUNTRACED | WCONTINUED);
        if(w == -1)
        {
          perror("waitpid failed.");
          exit(-1);
        }

        if(WIFEXITED(status))
        {
          printf("Exited, status = %d.\n", WEXITSTATUS(status));
        }
        else if(WIFSIGNALED(status))
        {
          printf("Killed by signal %d.\n",WTERMSIG(status));
        }
        else if(WIFSTOPPED(status))
        {
          printf("Stopped by signal %d.\n", WSTOPSIG(status));
        }
        else if(WIFCONTINUED(status))
        {
          printf("Continued.\n");
        }

      }while(!WIFEXITED(status) && !WIFSIGNALED(status));

      signal(SIGINT,SIG_DFL);

    break;
  }
  exit(EXIT_SUCCESS);

}
