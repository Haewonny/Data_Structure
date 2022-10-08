#include <stdio.h>
#include <stdlib.h>
/*
  [ 덱 ]
  - double-ended queue의 줄임말
  - 큐의 전단(front)과 후단(rear)에서 모두 삽입과 삭제가 가능한 큐
  - add_front()와 add_rear()가 추가됨
 */
#define MAX_DEQUE_SIZE 5 // 덱의 최대 크기
typedef int element; // 덱의 요소 타입 (정수)
typedef struct { // 덱 타입
    int front;
    int rear;
    element data[MAX_DEQUE_SIZE]; // 데이터 배열
} DequeType;

// 오 함수 -> 오류 메시지 출력
void error(char* message) {
    fprintf(stderr, "%s\n", message);
    exit(1); // 종료
}

// 큐 초기화 - 초기 상태는 front, rear 값이 0
void init_deque(DequeType* q) {
    q -> front = 0;
    q-> rear = 0;
}

// 포화 상태 검출 함수
int is_full(DequeType * q) {
    return ((q -> rear + 1) % MAX_DEQUE_SIZE == q -> front);
}

// 공백 상태 검출 함수
int is_empty(DequeType * q) {
    return (q -> front == q -> rear);
}

// 덱의 출력
void deque_print(DequeType * q) {
    printf("DEQUE(front = %d rear = %d) = ", q -> front, q -> rear);
    if(!is_empty(q)) {
        int i = q -> front;
        do {
            i = (i + 1) % MAX_DEQUE_SIZE;
            printf("%d | ", q -> data[i]);
            if(i == q -> rear)
                break;
        } while(i != q -> front);
    }
    printf("\n");
}

// rear 삽입 함수 - enque와 같음
void add_rear(DequeType* q, element item) {
    if(is_full(q))
        error("덱이 포화상태입니다.");
    q -> rear = (q -> rear + 1) % MAX_DEQUE_SIZE;
    q -> data[q -> rear] = item;
}

// front 삭제 함수 - dequeue와 같음
element delete_front(DequeType* q) {
    if(is_empty(q))
        error("덱이 공백상태입니다.");
    q -> front = (q -> front + 1) % MAX_DEQUE_SIZE;
    return q -> data[q -> front];
}

// front 데이터 확인 함수
element get_front(DequeType* q) {
    if(is_empty(q))
        error("덱이 공백상태입니다.");
    return q -> data[(q -> front + 1) % MAX_DEQUE_SIZE]; // front 위치 바꾸지 않고 return
}

// front 삽입 함수 **
void add_front(DequeType* q, element val) {
    if(is_full(q))
        error("덱이 포화상태입니다.");
    q -> data[q -> front] = val; // 값 넣고
    q -> front = (q -> front - 1 + MAX_DEQUE_SIZE) % MAX_DEQUE_SIZE; // front - 1
}

// rear 삭제 함수 **
element delete_rear(DequeType* q) {
    int prev = q -> rear;
    if(is_empty(q))
        error("덱이 공백상태입니다.");
    q -> rear = (q -> rear - 1 + MAX_DEQUE_SIZE) % MAX_DEQUE_SIZE; // rear - 1
    return q -> data[prev]; // 삭제한 값 return
}

// rear 데이터 확인 함수
element get_rear(DequeType* q) {
    if(is_empty(q))
        error("덱이 공백상태입니다.");
    return q -> data[q -> rear];

}

// main 함수
int main(void){
    DequeType dq; // 덱 생성
    init_deque(&dq); // 덱 초기화

    for(int i = 0; i < 3; i++) {
        add_front(&dq, i);
        deque_print(&dq);
    }

    for(int i = 0; i < 3; i++) {
        delete_rear(&dq);
        deque_print(&dq);
    }

    return 0;
}
