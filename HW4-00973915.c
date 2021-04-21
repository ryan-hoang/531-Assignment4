#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int cs531_system(char* command);


int main(int argc, char *argv[])
{
  int term = open("/dev/tty", O_RDWR);
  close(1);
  dup(term);
  close(2);
  dup(term);

  int status;
  status = cs531_system(argv[1]);
  printf("\nParent process is sleeping...\n");
  sleep(10);
  return status;
}

int cs531_system(char* command)
{
  pid_t child, w;
  int status;

  child = fork();
  if (child == -1)
  {
    perror("fork");
    return EXIT_FAILURE;
  }

  if (child == 0)
  {
    /* child process */

    //printf("Child PID is %ld\n", (long) getpid());
    execlp("bash", "bash", "-c", command , (char*) NULL);
    pause();
    perror("Child Process: Could not execute command.");
    return EXIT_FAILURE;
  }
  else
  {
     /* Code executed by parent */
     struct sigaction sigOriginal, sigIgnore;
     sigIgnore.sa_handler = SIG_IGN;
     sigIgnore.sa_flags = 0;

     sigaction(SIGINT,&sigIgnore,&sigOriginal);
     do
     {
       w= waitpid(child, &status, WUNTRACED | WCONTINUED);
       if (w == -1) {perror("waitpid");
       return EXIT_FAILURE;
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
    sigaction(SIGINT,&sigOriginal,NULL);
    return EXIT_SUCCESS;
  }
}
