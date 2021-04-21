#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>


int main(int argc, char *argv[])
{
  pid_t child, w;
  int status;

  child= fork();
  if (child == -1)
  {
    perror("fork");
    exit(EXIT_FAILURE);
  }

  if (child == 0)
  {
    /* child process */
    printf("Child PID is %ld\n", (long) getpid());
    execlp("ping", "ping", "127.0.0.1", NULL);
    pause();
    perror("Child Process: Could not execute command.");
    _exit(0);
  }
  else
  {
     /* Code executed by parent */
     do
     {
       w= waitpid(child, &status, WUNTRACED | WCONTINUED);
       if (w == -1) {perror("waitpid");
       exit(EXIT_FAILURE);
     }

     if (WIFEXITED(status))
      {
        printf("exited, status=%d\n", WEXITSTATUS(status));
      }
      else if (WIFSIGNALED(status))
      {
        printf("killed by signal %d\n", WTERMSIG(status));
      }
      else if (WIFSTOPPED(status))
      {
        printf("stopped by signal %d\n", WSTOPSIG(status));
      }
      else if (WIFCONTINUED(status))
      {
        printf("continued\n");
      }
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));

    exit(EXIT_SUCCESS);
  }
}
