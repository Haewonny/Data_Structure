#include <stdio.h>
#include <stdlib.h>
/*
  [ 선형큐 ]
  - 배열을 선형으로 사용하여 큐를 구현
  - enqueue(item) : 항목을 큐에 넣는 것이므로 item을 명시함
  - dequeue() : 항목을 큐의 정해진 위치에서 삭제하여 반환하므로 파라미터가 없음
 */
#define MAX_QUEUE_SIZE 5 // 큐의 최대 크기
typedef int element; // 큐의 요소 타입 (정수)
typedef struct { // 큐 타입
    int front;
    int rear;
    element data[MAX_QUEUE_SIZE]; // 데이터 배열
} QueueType;

// 에러 함수 -> 오류 메시지 출력
void error(char* message) {
    fprintf(stderr, "%s\n", message);
    exit(1); // 종료
}

// 큐 초기화 - 초기 상태는 front, rear 값이 -1
void init_queue(QueueType* q) {
    q -> front = -1;
    q-> rear = -1;
}

// 큐의 출력
void queue_print(QueueType* q) {
    // 0부터 'MAX_QUEUE_SIZE - 1'까지 출력
    for(int i = 0; i < MAX_QUEUE_SIZE; i++){
        if(i <= q -> front || i > q -> rear) // front와 rear 사이를 벗어나면
            printf("   | ");
        else
            printf("%d | ", q -> data[i]);
    }
    printf("\n");
}

// 포화 상태 검출 함수 - 큐에 빈 공간이 없나?
// 큐의 문제점 => 앞이 비어있어도 끝까지 다 차면 full로 인식함
int is_full(QueueType* q) {
    if(q -> rear == MAX_QUEUE_SIZE - 1) // rear가 가리키는 곳이 배열의 마지막 원소임
        return 1;
    else
        return 0;
}

// 공백 상태 검출 함수 - 큐가 비었는가?
int is_empty(QueueType* q) {
    if(q -> front == q -> rear)
        return 1;
    else
        return 0;
}

// 삽입 함수
void enqueue(QueueType* q, int item) {
    if(is_full(q)){ // 큐가 포화 상태이면
        error("큐가 포화상태입니다.");
        return; // void라서
    }
    q -> data[++(q -> rear)] = item; // rear가 가리키는 곳을 오른쪽으로 한 칸 옮기고 item 값 대입
}

// 삭제 함수
int dequeue(QueueType* q) {
    if(is_empty(q)){ // 큐가 공백 상태이면
        error("큐가 공백상태입니다.");
        return -1;
    }
    int item = q -> data[++(q -> front)]; // front는 빠져나간 곳(빈 곳)을 가리키게 됨
    return item;
}

int main(void){
    int item = 0;
    QueueType q; // 큐 생성
    init_queue(&q); // 큐 초기화

    // 큐에 삽입
    enqueue(&q, 10); queue_print(&q);
    enqueue(&q, 20); queue_print(&q);
    enqueue(&q, 30); queue_print(&q);

    // 큐에서 삭제
    item = dequeue(&q); queue_print(&q);
    item = dequeue(&q); queue_print(&q);
    item = dequeue(&q); queue_print(&q);

    return 0;
}
