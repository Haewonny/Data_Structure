#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
   [ 특정한 값을 탐색하는 함수 ]
   - 리스트를 만들어서 10, 20, 30을 순서대로 리스트의 맨 앞에 삽입함
   - 리스트에서 특정 값을 탐색함
 */
typedef int element; // 리스트 항목의 정의 (정수 타입)

typedef struct ListNode { // 노드 타입을 구조체로 정의함
    element data;
    struct ListNode* link; // 자기 참조 구조체 - ListNode 타입의 노드를 가리키는 포인터
} ListNode;

// 오류 처리 함수
void error(char* message) {
    fprintf(stderr, "%s\n", message);
    exit(1);
}

// 삽입 함수 - 리스트 맨 앞에 삽입
ListNode* insert_first(ListNode* head, element value) {
    ListNode* p = (ListNode*) malloc(sizeof (ListNode)); // 노드 생성
    p -> data = value; // 노드에 값 대입
    p -> link = head; // 리스트의 맨 앞에 삽입
    head = p; // 헤드 포인터 변경

    return head;
}

// 특정 값 탐색 함수
ListNode* search_list(ListNode* head, element x) {
    ListNode* p = head; // 포인터 p는 리스트 안의 항목들을 앞에서부터 가리킴
    while(p != NULL) {
        if(p -> data == x)
            return p;
        p = p -> link; // p를 한칸씩 뒤로 이동
    }
    return NULL; // 탐색 실패
}

// 출력 함수
void print_list(ListNode* head) {
    for(ListNode* p = head; p != NULL; p = p -> link) // 포인터 p가 노드를 하나씩 가리키면서 출력함
        printf("%d -> ", p -> data);
    printf("NULL \n");
}

// main 함수
int main(void){
    ListNode* head = NULL; // 비어있는 리스트 생성

    head = insert_first(head, 10);
    print_list(head);
    head = insert_first(head, 20);
    print_list(head);
    head = insert_first(head, 30);
    print_list(head);

    if(search_list(head, 10) != NULL) // return 값이 NULL인지 아닌지에 따라서 탐색 유무 결정
        printf("리스트에서 10을 찾았습니다.\n");
    else
        printf("리스트에서 10을 찾지 못했습니다.\n");

    return 0;
}