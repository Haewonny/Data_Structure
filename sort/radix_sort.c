#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 10
/*
  [ 기수 정렬 (radix sort) ]
  - 자릿수에 따라 버킷(bucket)에 넣었다가 꺼내면 정렬됨
  - 버킷은 큐로 구현
  - 버킷의 개수는 키의 표현 방법과 밀접한 관계
 */

// ***** 선형큐 코드 시작
#define MAX_QUEUE_SIZE 100 // 큐의 최대 크기
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
// ***** 선형큐 코드 끝

#define BUCKETS 10
#define DIGITS 4
// 기수 정렬 함수
void radix_sort(int list[], int n) {
    int i, b, d;
    int factor = 1; // n의 자리
    QueueType queues[BUCKETS]; // 큐 생성

    for(b = 0; b < BUCKETS; b++)
        init_queue(&queues[b]); // 큐들의 초기화

    for(d = 0; d < DIGITS; d++) { // 최대 4번
        for(i = 0; i < n; i++) // 데이터를 자릿수에 따라 큐에 입력
            enqueue(&queues[(list[i] / factor) % 10], list[i]); // **버킷 번호 알아내는 식 : (list[i] / factor) % 10**

        for(b = i = 0; b < BUCKETS; b++) { // 버킷에서 꺼내어 list로 합침
            while(!is_empty(&queues[b]))
                list[i++] = dequeue(&queues[b]);
        }
        factor *= 10; // 그 다음 자릿수로 감
    }
}

// main 함수
int main(void){
    int list[SIZE]; // 정렬할 배열

    srand((unsigned) time(NULL));
    for(int i = 0; i < SIZE; i++) // 난수 생성
        list[i] = rand() % 100;

    radix_sort(list, SIZE); // 기수 정렬 호출

    for(int i = 0; i < SIZE; i++) // 출력
        printf("%d ", list[i]);
    printf("\n");

    return 0;
}