#include <stdio.h>
#include <stdlib.h>
/*
  [ 원형 연결 리스트 ]
  - circular linked list
  - 마지막 노드의 링크가 첫 번째 노드를 가리키는 리스트
  - 한 노드에서 다른 모든 노드로의 접근이 가능
  - 헤드포인터가 마지막 노드를 가리키도록 구성하면 리스트의 처음이나 마지막에 노드를 삽입하는 연산이 단순 연결 리스트에 비하여 용이함
 */
typedef int element; // 리스트 항목의 정의 (정수 타입)
typedef struct ListNode { // 노드 타입을 구조체로 정의함
    element data;
    struct ListNode* link; // 자기 참조 구조체 - ListNode 타입의 노드를 가리키는 포인터
} ListNode;

// 삽입 함수 1 - 리스트의 시작 부분에 항목을 삽입하는 함수
ListNode* insert_first(ListNode* head, element data) {
    ListNode* node = (ListNode*) malloc(sizeof(ListNode));
    node -> data = data;
    // link 작업
    if(head == NULL) { // 리스트가 비어 있음
        head = node;
        node -> link = head;
    }
    else {
        node -> link = head -> link;
        head -> link = node;
    }
    return head;
}

// 삽입 함수 2 - 리스트의 마지막 부분에 항목을 삽입하는 함수
ListNode* insert_last(ListNode* head, element data) {
    ListNode* node = (ListNode*) malloc(sizeof (ListNode));
    node -> data = data;
    if(head == NULL) {
        head = node;
        node -> link = head;
    }
    else {
        node -> link = head -> link;
        head -> link = node;
        head = node; // **insert_first와 다른 부분
    }
    return head;
}

// 리스트 출력 함수 - 리스트를 방문하여 모든 항목을 출력하는 함수
void print_list(ListNode* head) {
   ListNode* p;

   if(head == NULL) // 리스트가 비었다면
       return;
   p = head -> link; // 첫째 노드(출력의 시작점)
   do {
       printf("%d -> ", p -> data);
       p = p -> link; // 옆으로 이동
   } while(p != head);

   printf("%d -> ", p -> data); // 마지막 노드 출력 (p -> head)
}

// main 함수
int main(void){
    ListNode* head = NULL; // 비어있는 리스트 생성(초기화)

    head = insert_last(head, 20);
    head = insert_last(head, 30);
    head = insert_last(head, 40);
    head = insert_first(head, 10);

    print_list(head);

    return 0;
}