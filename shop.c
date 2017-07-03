#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int shops[5];
pthread_mutex_t m1=PTHREAD_MUTEX_INITIALIZER;

void shoping(int*need){
	int buy, namber;
	while((*need)!=0){
	        pthread_mutex_lock(&m1);
		namber=rand()%5;
	        buy=450+rand()%51;
		if(shops[namber]>buy){
			shops[namber]-=buy;
			(*need)-=buy;
			if((*need)<0){
				*need=0;
                        }
		}
		else
			buy=0;
		printf("Shop №%d buy %d need %d goods %d\n",namber,buy,*need,shops[namber]);
		sleep(2);
       		pthread_mutex_unlock(&m1);
	}
}

void supply(){
	int product;
	int i;
	while(1){
	        pthread_mutex_lock(&m1);
	        product=300;
		i=rand()%5;
		shops[i]+=product;
                printf("product %d  goods% d shop №%d\n", product, shops[i], i);
		sleep(4);
   	        pthread_mutex_unlock(&m1);
	}
}

int main(){
	srand(time(NULL));
	int need[3];
	int i,k;
	pthread_t tid[4];
	for(i=0;i<5;i++){
		shops[i]=950+rand()%101;
	}
	for(i=0; i<3; i++){
		need[i]=2900+rand()%200;
		pthread_create(&tid[i],NULL,shoping,&need[i]);
	}
        pthread_create(&tid[3],NULL,supply,NULL);
	for(i=0; i<3; i++){
		pthread_join(tid[i],NULL);
	}
	pthread_cancel(tid[3]);
}
