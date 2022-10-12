#include <stdio.h>
#include <stdlib.h>
/*
  [ 연결 리스트로 구현된 리스트 ]
  - 동적 메모리 할당을 통해 연결 리스트(linked list)를 만들어 리스트를 구현함
  - 리스트의 항목을 노드(node)라고 하는 곳에 분산하여 저장함
  - 특징
    1) 크기에 제한을 받지 않음
    2) 리스트의 가운데에서 삽입과 삭제가 수월하게 이루어짐
    3) 구현이 복잡함
    4) 임의의 항목 (i번째 항목)을 검색할 때, 배열을 사용하는 경우보다 검색 시간이 많이 걸림
 */
typedef int element; // 리스트 항목의 정의 (정수 타입)
typedef struct ListNode { // 노드 타입을 구조체로 정의함
    element data;
    struct ListNode* link; // 자기 참조 구조체 - ListNode 타입의 노드를 가리키는 포인터
} ListNode;

// 삽입 함수 1 - 리스트의 시작 부분에 항목을 삽입하는 함수
ListNode* insert_first(ListNode* head, int value) {
    ListNode* p = (ListNode*) malloc(sizeof (ListNode));
    p -> data = value;
    p -> link = head; // 리스트의 맨 앞에 있는 노드를 가리키도록
    head = p; // head는 새로 삽입된 노드를 가리키도록

    return head;
}

// 삽입 함수 2 - 리스트의 중간 부분(pre 뒤)에 항목을 삽입하는 함수
ListNode* insert(ListNode* head, ListNode* pre, element value) {
    ListNode* p = (ListNode*) malloc(sizeof(ListNode)); // 노드 하나 동적할당 받음
    p -> data = value;
    p -> link = pre -> link;
    pre -> link = p;

    return head;
}

// 삭제 함수 1 - 리스트의 첫 번째 항목을 삭제하는 함수
ListNode* delete_first(ListNode* head) {
    ListNode* removed; // 삭제할 노드를 가리키는 포인터
    if(head == NULL) // head가 가리키고 있는 리스트가 비어있는지 확인
        return NULL;
    removed = head;
    head = removed -> link; // head가 removed 포인터가 가리키던 곳을 가리키도록
    free(removed);

    return head;
}

// 삭제 함수 2 - 리스트의 중간 항목(pre 뒤)을 삭제하는 함수
ListNode* delete(ListNode* head, ListNode* pre) {
    ListNode* removed;
    removed = pre -> link;
    pre -> link = removed -> link;
    free(removed);

    return head;
}

// 출력 함수 - 리스트를 방문하여 모든 항목을 출력하는 함수
void print_list(ListNode* head) {
    for(ListNode* p = head; p != NULL; p = p -> link) // 포인터 p가 노드를 하나씩 가리키면서 출력함
        printf("%d -> ", p -> data);
    printf("NULL \n");
}

// main 함수
int main(void){
    ListNode* head = NULL; // 비어있는 리스트 생성

    for(int i = 0; i < 5; i++) {
        head = insert_first(head, i);
        print_list(head);
    }

    for(int i = 0; i < 5; i++) {
        head = delete_first(head);
        print_list(head);
    }

    return 0;
}