#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

sem_t chopstick[5];
void * signal(void *);
void eat(int);

int main()
 {
         int i,n[5];
         pthread_t nit[5];
//Kreiranje semafora za viljuske
         for(i=0;i<5;i++)
         sem_init(&chopstick[i],0,1);
//Kreiranje niti
         for(i=0;i<5;i++){
                 n[i]=i;
                 pthread_create(&nit[i],NULL,signal,&n[i]);
                 }

         for(i=0;i<5;i++)
                 pthread_join(nit[i],NULL);
 }
void * signal(void * n)
 {
         int ph=*(int *)n;
         printf("Filozof %d želi jesti \n",ph);
         printf("Filozof %d pokušava da izabere levu viljušku\n",ph);
         sem_wait(&chopstick[ph]);
         printf("Filozof %d uzima levu viljušku\n",ph);
         printf("Filozof %d pokušava da uzme desnU viljušku\n",ph);
         sem_wait(&chopstick[(ph+1)%5]);
         printf("Filozof %d uzima desnu viljušku\n",ph);
         eat(ph);
         sleep(2);
         printf("Filozof %d završava sa jelom\n",ph);
         sem_post(&chopstick[(ph+1)%5]);
         printf("Filozof %d vraća levu viljušku na mesto\n",ph);
         sem_post(&chopstick[ph]);
         printf("Filozof %d vraća desnu viljušku na mesto\n",ph);
 }
 void eat(int ph)
 {
         printf("Filozof %d počinje da jede\n",ph);
 }

