#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
//#include <sys/wait.h>
#include <pthread.h>

#define N 1000

struct vector_parms
{
	double *v;
	double res[N/4];
    int tam;
    float mult;
};


void* multiplex (void* parameters);


int main () {

//    double numero [N] = {2, 3, 4, 5, 6 ,7, 8, 9};
    double numero [N];
    for(long int i=0; i < N; i++ ){
        numero[i] = i+1;
    }
    double a;
    //double mult;
    printf("Digite o numero a ser multiplicado: ");
    scanf("%lf", &a);


    struct vector_parms argumento1, argumento2, argumento3, argumento4;

    pthread_t thread_id1;
    pthread_t thread_id2;
    pthread_t thread_id3;
    pthread_t thread_id4;

    argumento1.v = &(numero[0*N/4]);
    //argumento1.x = mult;
    argumento1.tam = N/4;
    argumento1.mult = a;

    argumento2.v = &(numero[1*N/4]);
    //argumento2.x = mult;
    argumento2.tam = N/4;
    argumento2.mult = a;

    argumento3.v = &(numero[2*N/4]);
    //argumento3.x = mult;
    argumento3.tam = N/4;
    argumento3.mult = a;

    argumento4.v = &(numero[3*N/4]);
    //argumento4.x = mult;
    argumento4.tam = N/4;
    argumento4.mult = a;

    pthread_create (&thread_id1, NULL, &multiplex, &argumento1);
    pthread_create (&thread_id2, NULL, &multiplex, &argumento2);
    pthread_create (&thread_id3, NULL, &multiplex, &argumento3);
    pthread_create (&thread_id4, NULL, &multiplex, &argumento4);

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
    //ouble x = 2.0;
    for (i = 0; i<(p->tam); i++){
        p->res[i] = p->v[i] * p->mult;
        printf("%f\n", p->res[i]);
    }
}

