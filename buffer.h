/*내부적으로 버퍼는 buffer_item 타입의 고정 길이 배열이다. 
이 배열을 환형 큐(circular queue) 방식으로 동작한다. 
buffer_item에 대한 정의 및 버퍼의 크기는 다음과 같이 헤더 파일에서 정의된다.
*/

typedef int buffer_item;
#define BUFFER_SIZE 5

buffer_item buffer[BUFFER_SIZE];

// 생산자(Producer)가 호출하는 버퍼를 변경하는 함수(삽입).
int insert_item(buffer_item item) {
	semaphore mutex;
   /* 항목을 버퍼에 추가한다. 성공하면 0을 실패하면 -1을 반환한다. */
}

// 소비자(Consumer)가 호출하는 버퍼를 변경하는 함수(삭제).
int remove_item(buffer_item *item) {
   /* 버퍼에서 한 항목을 가져와서 item 인수에 저장한다. 
      성공하면 0을, 실패하면 –1을 반환한다. */
}

// 버퍼를 초기화하는 함수도 필요하다. 이 함수에서는 empty, full 세마포와 mutex를 초기화한다.