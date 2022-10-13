#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
   [ 단어들을 저장하고 있는 연결리스트 ]
   - APPLE, KIWI, BANANA를 순서대로 리스트에 저장하는 프로그램 작성하기
   - 노드에 들어가는 데이터가 string
   - 리스트에 삽입 연산을 할 때마다 리스트 전체를 출력해야 함
 */
typedef struct {
    char name[100]; // 과일 이름을 저장할 배열
} element; // 배열을 구조체로 포장

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
        printf("%s -> ", p -> data.name);
    printf("NULL \n");
}

// main 함수
int main(void){
    ListNode* head = NULL; // 비어있는 리스트 생성
    element data;

    strcpy(data.name, "APPLE");
    head = insert_first(head, data);
    print_list(head);

    strcpy(data.name, "KIWI");
    head = insert_first(head, data);
    print_list(head);

    strcpy(data.name, "BANANA");
    head = insert_first(head, data);
    print_list(head);

    return 0;
}