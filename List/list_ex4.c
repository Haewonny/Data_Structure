#include <stdio.h>
#include <stdlib.h>
/*
   [ 리스트를 역순으로 만들기 ]
   - 리스트의 모든 링크를 거꾸로 바꾸어, 리스트 전체가 역순으로 되도록 하기
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

// 출력 함수
void print_list(ListNode* head) {
    for(ListNode* p = head; p != NULL; p = p -> link) // 포인터 p가 노드를 하나씩 가리키면서 출력함
        printf("%d -> ", p -> data);
    printf("NULL \n");
}

// 리스트를 역순으로 만드는 함수
ListNode* reverse(ListNode* head) {
    // 순회 포인터로 p, q, r을 사용함
    ListNode* p, * q, * r;

    p = head; // p를 역순으로 만들 리스트
    q = NULL; // q를 역순으로 만들 노드
    while(p != NULL) {
        r = q; // r은 역순으로 된 리스트
               // r은 q, q는 p를 차례로 따라감
        q = p;
        p = p -> link;
        q -> link = r; // q의 링크 방향을 바꿈
    }
    return q;
}

// main 함수
int main(void){
    ListNode* head = NULL; // 비어있는 리스트 생성

    printf("head 리스트 생성 과정\n");
    head = insert_first(head, 40);
    print_list(head);
    head = insert_first(head, 30);
    print_list(head);
    head = insert_first(head, 20);
    print_list(head);
    head = insert_first(head, 10);
    print_list(head);

    printf("\n역순으로 된 리스트\n");
    head = reverse(head);
    print_list(head);

    return 0;
}