#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
int main()
{
  int f2s[2], s2f[2];
  char request='V', cur_val=1;
  
  srand(time(NULL));
  pipe(f2s);
  pipe(s2f);
  if(fork() == 0)
  {
    do
    {
      read(f2s[0], &cur_val, sizeof(char));
      printf("Valor recebido = %d\n", cur_val);
      if(cur_val!=0)
        write(s2f[1], &request, sizeof(char));
    } while(cur_val!=0);
    request='F';
    write(s2f[1], &request, sizeof(char));
  }
  else
  {
    do
    {
      cur_val = rand()%0x1F;
      write(f2s[1], &cur_val, sizeof(char));
      read(s2f[0], &request, sizeof(char));
    } while(request=='V');
  }
  return 0;
}
