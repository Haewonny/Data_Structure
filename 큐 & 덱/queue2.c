#include <stdio.h>
#include <stdlib.h>
/*
  [ 원형큐 ]
  - 선형큐의 문제점을 해결하기 위해서 사용
  - 공백상태 vs 포화상태
     1) 공백상태 : front == rear
     2) 포화상태 : front와 rear가 한 칸 차이 **front == (rear + 1 ) % MAX_QUEUE_SIZE**
 */
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

int main(void){
    QueueType queue;
    int element; // 변수

    init_queue(&queue); // 큐 초기화

    printf("-- 데이터 추가 단계 --\n");
    while(!is_full(&queue)) { // 큐가 다 차기 전까지
        printf("정수를 입력하시오 > ");
        scanf("%d", &element);
        enqueue(&queue, element);
        queue_print(&queue);
    }
    printf("큐가 포화상태입니다.\n\n");

    printf("-- 데이터 삭제 단계 --\n");
    while(!is_empty(&queue)) { // 큐가 공백이 되기 전까지
        element = dequeue(&queue);
        printf("꺼내진 정수 : %d \n", element);
        queue_print(&queue);
    }
    printf("큐는 공백상태입니다.\n");

    return 0;
}
