#include <stdio.h>
#include <stdlib.h>
/*
  [ 이중 연결 리스트 ]
  - doubly linked list
  - 하나의 노드가 선행 노드와 후속 노드에 대한 두 개의 링크를 가지는 리스트
  - 선행 노드를 찾기가 힘든 단순 연결 리스트의 문제점 해결
  - 공간을 많이 차지하고, 코드가 복잡한 단점
  - 헤드 노드(head node)
    : 데이터를 가지지 않고 단지 삽입, 삭제 코드를 간단하게 할 목적으로 만들어진 노드, 공백 상테에서는 헤드 노드만 존재
 */
typedef int element; // 리스트 항목의 정의 (정수 타입)
typedef struct DListNode { // 노드 타입을 구조체로 정의함
    element data;
    struct DListNode* llink; // 왼쪽 링크
    struct DListNode* rlink; // 오른쪽 링크
} DListNode; // 이중 연결 노드 타입

// 이중 연결 리스트를 초기화하는 함수
void init(DListNode* pHead) {
    // 양쪽 링크가 다 자기자신을 가리키도록 함
    pHead -> llink = pHead;
    pHead -> rlink = pHead;
}

// 출력 함수
void print_DList(DListNode* pHead) {
    DListNode* p;
    for(p = pHead -> rlink; p != pHead; p = p -> rlink) {
        printf("<-| |%d| |-> ", p -> data);
    }
    printf("\n");
}

// 삽입 함수 - 새로운 데이터를 노드 before의 오른쪽에 삽입함
void dInsert(DListNode* before, element data) {
    DListNode* newNode = (DListNode*) malloc(sizeof (DListNode));

    newNode -> data = data;
    newNode -> llink = before;
    newNode -> rlink = before -> rlink;

    before -> rlink -> llink = newNode;
    before -> rlink = newNode;
}

// 삭제 함수 - removed 노드를 삭제함
void dDelete(DListNode* head, DListNode* removed) {
    if(removed == head)
        return;

    removed -> llink -> rlink = removed -> rlink;
    removed -> rlink -> llink = removed -> llink;

    free(removed);
}

// main 함수
int main(void){
    DListNode* head = (DListNode*) malloc(sizeof (DListNode));
    init(head); // 초기화

    printf("*** 추가 단계 ***\n");
    for(int i = 0; i < 5; i++) {
        // 헤드 노드의 오른쪽에 삽입
        dInsert(head, i); // 리스트의 맨 앞에 삽입
        print_DList(head);
    }

    printf("*** 삭제 단계 ***\n");
    for(int i = 0; i < 5; i++) {
        print_DList(head);
        dDelete(head, head -> rlink);
    }
    free(head);

    return 0;
}