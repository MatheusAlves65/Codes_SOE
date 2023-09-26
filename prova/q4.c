#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 100

struct vector
{
  int *v;
  int N;
  long int s;
};
void* thread_function(void* params)
{
  struct vector* p = (struct vector*) params;
  p->s = 0;
  for(int i = 0; i < (p->N); ++i)
    p->s += (long int)(p->v[i]);
  return NULL;
}
int main ()
{
  pthread_t threads[4];
  struct vector vecs[4];
  int v[TAM];
  long int valor_final=0;
  int i;

  srand(time(NULL));
  for(i=0; i<TAM; i++)
    v[i] = rand()&0xFF;
  for(i=0; i<4; i++)
  {
    vecs[i].v = &(v[i*(TAM/4)]);
    vecs[i].N = (TAM/4);
    pthread_create(&(threads[i]), NULL,
      &thread_function, &(vecs[i]));
  }
  valor_final = 0;
  for(i=0; i<4; i++)
  {
    pthread_join(threads[i], NULL);
    valor_final += vecs[i].s;
  }
  printf("Resultado = %ld\n", valor_final);
  return 0; 
}
