#include <stdio.h>
#include <stdlib.h>
/*
  [ 레벨 순회 ]
  - 레벨 순회 (level order) : 각 노드를 레벨 순으로 검사하는 순회 방법
  - 큐를 사용하는 순회법
  - **알고리즘**
    1. root 노드를 큐에 넣음
    2. 큐에 노드가 더 이상 없을 때까지 큐에서 노드를 삭제하여 출력하고, 그 노드의 자식 노드들을 큐에 넣음
*/
#define MAX_QUEUE_SIZE 100

typedef struct TreeNode { // 트리 노드 타입
    int data;
    struct TreeNode* left, *right;
} TreeNode; // 트리 노드를 정의하는 구조체

// 큐에 들어가는 element 타입 -> 노드 포인터
typedef TreeNode * element; // 트리

// ***** 원형큐 코드의 시작
typedef struct { // 큐 타입
    element data[MAX_QUEUE_SIZE];
    int front, rear;
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

// 삽입 함수
void enqueue(QueueType* q, element item) {
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

// 레벨 순회 함수
void level_order(TreeNode* ptr) {
    QueueType q; // 큐 생성
    init_queue(&q); // 큐 초기화

    if(ptr == NULL)
        return;
    enqueue(&q, ptr); // root 큐에 넣기

    while(!is_empty(&q)) { // 큐가 비어있지 않은 동안
        ptr = dequeue(&q); // 하나씩 꺼내서
        printf(" [%d] ", ptr -> data); // 방문
        if(ptr -> left) // 왼쪽 child가 있으면
            enqueue(&q, ptr -> left); // 큐에 넣기
        if(ptr -> right) // 오른쪽 child가 있으면
            enqueue(&q, ptr -> right); // 큐에 넣기
    }
}

// 트리 만들기
TreeNode n1 = { 1, NULL, NULL };
TreeNode n2 = { 4, &n1, NULL };
TreeNode n3 = { 16, NULL, NULL };
TreeNode n4 = { 25, NULL, NULL };
TreeNode n5 = { 20, &n3, &n4 };
TreeNode n6 = { 15, &n2, &n5 };
//      15
//     /  \
//    4   20
//    /   / \
//   1   16  25
TreeNode* root = &n6;

int main(void){
    printf("레벨 순회 =");
    level_order(root);
    printf("\n");

    return 0;
}