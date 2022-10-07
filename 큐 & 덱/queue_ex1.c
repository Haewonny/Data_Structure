#include <stdio.h>
#include <stdlib.h>
#include <time.h> // random number 사용
/*
  [ 생산자 / 소비자 응용 프로그램 ]
  - random number sequence를 통해 생산자와 소비자를 결정함
  - 상황을 시뮬레이션하는 프로그램
 */
// 원형큐 코드는 queue2.c에 있는 거 활용
// ***** 원형큐 코드의 시작
#define MAX_QUEUE_SIZE 5 // 큐의 최대 크기
typedef int element; // 큐의 요소 타입 (정수)
typedef struct { // 큐 타입
    int front;
    int rear;
    element data[MAX_QUEUE_SIZE]; // 데이터 배열
} QueueType;

// 오류 함수 -> 오류 메시지 출력
void error(char* message) {
    fprintf(stderr, "%s\n", message);
    exit(1); // 종료
}

// 큐 초기화 - 초기 상태는 front, rear 값이 0
void init_queue(QueueType* q) {
    q -> front = 0;
    q-> rear = 0;
}

// 포화 상태 검출 함수 - 큐에 빈 공간이 없나?
// **표현 방법 알아두기 => 인덱스 맞추려고
int is_full(QueueType* q) {
    return ((q -> rear + 1) % MAX_QUEUE_SIZE == q -> front);
}

// 공백 상태 검출 함수 - 큐가 비었는가?
int is_empty(QueueType* q) {
    return (q -> front == q -> rear); // front == rear 이면 true(1)
}

// 큐의 출력
void queue_print(QueueType* q) {
    printf("QUEUE(front = %d rear = %d) = ", q -> front, q -> rear);
    if(!is_empty(q)) { // 큐가 공백이 아닌 동안
        int i = q -> front;
        do { // front + 1, front + 2, ... 이렇게 최대 한 바퀴를 돌게 됨
            i = (i + 1) % MAX_QUEUE_SIZE;
            printf("%d | ", q -> data[i]);
            if(i == q -> rear)
                break;
        } while(i != q -> front);
    }
    printf("\n");
}

// 삽입 함수
void enqueue(QueueType* q, int item) {
    if(is_full(q)) // 큐가 포화 상태이면
        error("큐가 포화상태입니다.");

    // **삽입 전에 rear = 7이었다면 rear = (7+1)%8 = 0이 됨!
    q -> rear = (q -> rear + 1) % MAX_QUEUE_SIZE; // rear가 가리키는 곳 이동
    q -> data[q -> rear] = item; // 값 대입
}

// 삭제 함수
element dequeue(QueueType* q) {
    if(is_empty(q)) // 큐가 공백 상태이면
        error("큐가 공백상태입니다.");

    q -> front = (q -> front + 1) % MAX_QUEUE_SIZE;
    return q -> data[q -> front];
}
// ***** 원형큐 코드의 끝

// main 함수
int main(void){
    QueueType queue;
    init_queue(&queue); // 큐 초기화

    srand(time(NULL)); // 첫째 random number을 정함 (시작점)

    for(int i = 0; i < 100; i++) {
        if(rand() % 5 == 0) { // 5로 나누어 떨어지면 "생산"
            enqueue(&queue, rand() % 100); // 두자리수로 만들어 저장 (상품 번호)
        }
        queue_print(&queue);

        if(rand() % 10 == 0) { // 10으로 나누어 떨어지면 "소비"
            int data = dequeue(&queue); // 큐에서 삭제
        }
        queue_print(&queue);
    }
    return 0;
}
