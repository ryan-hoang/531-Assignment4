#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int cs531_system(char* s);

int main(int argc, char *argv[])
{
  int status;
  status = cs531_system(argv[1]);
  printf("\nParent process is sleeping...\n");
  sleep(10);
  return status;
}

int cs531_system(char* s)
{
  
}
