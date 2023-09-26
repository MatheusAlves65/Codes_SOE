#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>

#define N 50000

struct vector_parms
{
	double *v;
	double res[N/4];
    int tam;
    int mult;
    int sum;
};






void* multiplex (void* parameters);


int main () {


    double posicoes [N];
    for(long int i=0; i < N; i++ ){
        posicoes[i] = i;
    }
    double x;
    //double mult;
    printf("Digite o numero a ser multiplicado: ");
    scanf("%lf", &x);
    
    double y;
    //double soma
    printf("Digite o numero a ser Somado: ");
    scanf("%lf", &y);


    struct vector_parms parte1, parte2, parte3, parte4;

    pthread_t thread_id1;
    pthread_t thread_id2;
    pthread_t thread_id3;
    pthread_t thread_id4;

    parte1.v = &(posicoes[0*N/4]); // endereco v[0]
    parte1.tam = N/4;
    parte1.mult = x;
    parte1.sum = y;
    

    parte2.v = &(posicoes[1*N/4]);// endereco v[12500]
    parte2.tam = N/4;
    parte2.mult = x;
    parte2.sum = y;

    parte3.v = &(posicoes[2*N/4]);//endereco v[25000]
    parte3.tam = N/4;
    parte3.mult = x;
    parte3.sum = y;

    parte4.v = &(posicoes[3*N/4]);//endereco v[50000]
    parte4.tam = N/4;
    parte4.mult = x;
    parte4.sum = y;

    pthread_create (&thread_id1, NULL, &multiplex, &parte1);
    pthread_create (&thread_id2, NULL, &multiplex, &parte2);
    pthread_create (&thread_id3, NULL, &multiplex, &parte3);
    pthread_create (&thread_id4, NULL, &multiplex, &parte4);

    pthread_join(thread_id1, NULL);
	pthread_join(thread_id2, NULL);
	pthread_join(thread_id3, NULL);
	pthread_join(thread_id4, NULL);


    return 0;
}

void* multiplex(void* parameters)
{
    struct vector_parms* p = (struct vector_parms*) parameters;
    int i;
    
    for (i = 0; i<(p->tam); i++){
        p->res[i] = (p->v[i] *p->mult); //multiplica
        p->res[i] = (p->v[i] +p->sum); //soma
        printf("%f\n", p->res[i]);
    }
}



