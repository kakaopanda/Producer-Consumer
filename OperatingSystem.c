/*
유한 버퍼를 가진 생산자-소비자 문제를 해결한다. 
생산자와 소비자의 동작을 동기화하기 위하여 2가지 세마포와 하나의 mutex 락을 사용한다. 
empty, full 세마포는 카운팅 세마포로서 각각 비어있는 버퍼 수와 채워진 버퍼 수를 표시한다. 
버퍼에 대한 접근을 동기화하기 위해 mutex 락을 사용한다.

두 쓰레드를 생성한 후 main 함수는 sleep 상태에 들어간다. 
이 sleep 상태에서 깨어나면 main 함수를 프로그램 실행을 종료한다. 
*/

#include <stdlib.h>
#include <stdio.h>
#include "buffer.h"
#include <windows.h>
#include <semaphore.h>

void *producer(void *param) {
	// 생산자 쓰레드는 랜덤 시간동안 sleep한 후 랜덤 정수를 버퍼에다 추가하는 일을 반복한다. 
	// (랜덤 정수는 rand() 함수를 이용하여 생성한다.) 
	int integer = (rand() % 1000) + 100;
	buffer_item item;
	while (true) {
		 /* sleep for a random period of time */
		Sleep(integer);
		/* generate a random number */
		item = rand();
		if (insert_item(item))
			fprintf(NULL, "report error condition");
		else
			printf("producer produced %d∖n",item);
   }
}

void *consumer(void *param) {
	// 소비자는 랜덤 시간동안 sleep한 후 깨어나서 버퍼로부터 항목을 제거하려고 한다. 
	// (랜덤 정수는 rand() 함수를 이용하여 생성한다.) 
	int integer = (rand() % 1000) + 100;
	buffer_item item;
	while (true) {
      /* sleep for a random period of time */
      Sleep();
      if (remove_item(&item))
         fprintf(NULL, "report error condition");
      else
         printf("consumer consumed %d∖n",item);
   }
}

int main(int argc, char *argv[]) {
	// main함수는 버퍼를 초기화하고, 생산자와 소비자를 위한 쓰레드를 생성한다.
	// main 함수는 아래의 3개 명령 줄 인수를 받는다.
	/* 1. Get command line arguments argv[1],argv[2],argv[3] */
	int sleep_time = atoi(argv[1]); // argv[1] : 종료하기 전 sleep하는 시간
	int producer_count = atoi(argv[2]); // argv[2] : 생산자 쓰레드 수
	int consumer_count = atoi(argv[3]); // argv[3] : 소비자 쓰레드 수
	DWORD producer_ThreadId[producer_count];
    HANDLE producer_ThreadHandle[producer_count];
	DWORD consumer_ThreadId[consumer_count];
    HANDLE consumer_ThreadHandle[consumer_count];
	int Param;
	
	/* 2. Initialize buffer */


	/* 3. Create producer thread(s) */
	for(int i=0; i<producer_count; i++){
	producer_ThreadHandle[i] = CreateThread(
			NULL,
			0,
			producer,
			&Param,
			0,
			&producer_ThreadId[i]
		);
	}

	/* 4. Create consumer thread(s) */
	for(int i=0; i<consumer_count; i++){
	consumer_ThreadHandle[i] = CreateThread(
			NULL,
			0,
			consumer,
			&Param,
			0,
			&consumer_ThreadId[i]
		);
	}

	/* 5. Sleep */
	WaitForMultipleObjects(producer_count, producer_ThreadHandle, TRUE, INFINITE);
	WaitForMultipleObjects(consumer_count, consumer_ThreadHandle, TRUE, INFINITE);

	/* 6. Exit */
	Sleep(sleep_time);
	return 0;
}