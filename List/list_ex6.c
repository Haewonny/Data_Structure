#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
  [ 멀티 플레이어 게임 ]
  - 원형 연결 리스트를 이용하여 플레이어의 현재 차례를 출력해 주는 프로그램 작성
 */
typedef char element[100]; // 노드의 데이터 타입 - element는 크기가 100인 문자 배열의 이름
typedef struct ListNode { // 노드 타입을 구조체로 정의함
    element data; // 문자 배열
    struct ListNode* link; // 자기 참조 구조체 - ListNode 타입의 노드를 가리키는 포인터
} ListNode;

// 삽입 함수
ListNode* insert_first(ListNode* head, element data) {
    ListNode* node = (ListNode*) malloc(sizeof(ListNode));
    strcpy(node -> data, data); // **strcpy 이용해서 값 넣기**
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

// main 함수
int main(void){
    ListNode* head = NULL; // 비어있는 리스트 생성(초기화)

    head = insert_first(head, "KIM"); // KIM
    head = insert_first(head, "PARK"); // PARK -> KIM
    head = insert_first(head, "CHOI"); // CHOI -> PARK -> KIM

    ListNode* p = head;

    for(int i = 0; i < 10; i++) {
        printf("현재 차례 = %s\n", p -> data);
        p = p -> link; // 옆으로 이동
    }
    return 0;
}