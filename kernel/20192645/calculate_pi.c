#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <time.h>

#define NUM_POINTS 10000000
#define NUM_THREADS 5

int circle_count = 0;
pthread_mutex_t mutex;

void* calculate_pi(void* thread_id) {
	int points_per_thread = NUM_POINTS / NUM_THREADS;
	int in_circle = 0;
	double x, y;
	long tid = (long)thread_id;

	unsigned int seed = time(NULL) + (tid + 1); //각 쓰레드에 랜덤 시드 생성

	for(int i = 0; i < points_per_thread; i++) {
		x = rand_r(&seed) / ((double)RAND_MAX + 1) * 2 - 1;
		y = rand_r(&seed) / ((double)RAND_MAX + 1) * 2 - 1;

		if(x * x + y * y <= 1) {
			in_circle++;
		}
	}

	//원 안의 점 개수 업데이트 race condition 방지를 위한 mutex lock과 unlock
	pthread_mutex_lock(&mutex);
	circle_count += in_circle;
	pthread_mutex_unlock(&mutex);

	return NULL;
}

int montecarlo() {
	circle_count = 0;
	
	pthread_t threads[NUM_THREADS];
	pthread_mutex_init(&mutex, NULL);

	//쓰레드 생성
	for(int i = 0; i < NUM_THREADS; i++) {
		if(pthread_create(&threads[i], NULL, calculate_pi, (void*)(long)i) != 0) {
			perror("Failed to create thread");
			return 1;
		}
	}

	//쓰레드 종료 대기
	for(int i = 0; i < NUM_THREADS; i++) {
		pthread_join(threads[i], NULL);
	}

	//파이 계산 출력
	double pi_estimate = 4.0 * circle_count / NUM_POINTS;
	printf("n_thread = %d, Estimated PI = %f\n", NUM_THREADS, pi_estimate);

	//뮤텍스 소멸
	pthread_mutex_destroy(&mutex);

	return 0;
}

