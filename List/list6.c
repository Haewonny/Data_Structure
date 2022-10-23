#include <stdio.h>
#include <stdlib.h>
/*
  [ 연결 리스트로 구현한 큐 ]
  - front와 rear을 가리키기 위한 포인터 2개 필요
 */
typedef int element; // 리스트 항목의 정의 (정수 타입)
typedef struct QueueNode { // 노드 타입
    element data;
    struct QueueNode* link;
} QueueNode;

typedef struct { // 큐
    QueueNode* front, * rear;
} LinkedQueueType;

// 큐 초기화 함수
void init(LinkedQueueType* q) {
    q -> front = q -> rear = NULL;
}

// 공백 상태 검출 함수
int is_empty(LinkedQueueType* q) {
    return (q -> front == NULL);
}

// 삽입 함수 - rear 뒤에 삽입
void enqueue(LinkedQueueType* q, element data) {
    QueueNode* temp = (QueueNode*) malloc(sizeof (QueueNode));

    temp -> data = data;
    temp -> link = NULL;

    if(is_empty(q)) { // 큐가 공백이면
        q -> front = temp;
        q -> rear = temp;
    }
    else { // 안 비었으면 link 이어 붙이기
        q -> rear -> link = temp;
        q -> rear = temp; // rear 한 칸 이동
    }
}

// 삭제 함수 - front 위치에 있는 거 삭제
element dequeue(LinkedQueueType* q) {
    QueueNode* temp = q -> front;
    element data;
    if(is_empty(q)) {
        fprintf(stderr, "큐가 비어있음\n");
        exit(1);
    }
    else {
        data = temp -> data; // 데이터를 꺼냄
        q -> front = q -> front -> link; // front는 다음 노드로 이동
        if(q -> front == NULL) // 공백 상태
            q -> rear = NULL;

        free(temp);

        return data;
    }
}

// 출력 함수
void print_queue(LinkedQueueType* q) {
    QueueNode* p;
    for(p = q -> front; p != NULL; p = p -> link)
        printf("%d -> ", p -> data);
    printf("NULL\n");
}

// main 함수
int main(void){
    LinkedQueueType queue; // 큐 생성
    init(&queue); // 큐 초기화

    enqueue(&queue, 1); print_queue(&queue);
    enqueue(&queue, 2); print_queue(&queue);
    enqueue(&queue, 3); print_queue(&queue);

    dequeue(&queue); print_queue(&queue);
    dequeue(&queue); print_queue(&queue);
    dequeue(&queue); print_queue(&queue);

    return 0;
}