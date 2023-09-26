#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

struct processo
{
  int pid, fd[2];
};
void fim()
{
  fprintf(stderr, "Processo %d terminado\n",
    getpid());
  exit(0);
}
int main()
{
  struct processo p[3];
  int i;
  
  signal(SIGINT, fim);
  for(i=0; i<3; i++)
  {
    pipe(p[i].fd);
    p[i].pid = fork();
    if(p[i].pid == 0)
      while(1);
  }
  while(1);
  return 0;
}
