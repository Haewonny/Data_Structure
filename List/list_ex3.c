#include <stdio.h>
#include <stdlib.h>
/*
   [ 2개의 리스트를 합하는 함수 ]
   - 리스트 2개를 생성한 후 두 리스트를 합치기
   - head1이 가리키는 리스트의 마지막 노드를 찾아가서 그곳을 어떤 포인터 p가 가리키도록 함
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

// 리스트 합치는 함수
ListNode* concat_list(ListNode* head1, ListNode* head2) {
    if(head1 == NULL) // 이어붙일 것이 없음
        return head2;
    else if(head2 == NULL)
        return head1;
    else{ // 두 리스트가 다 비어있지 않을 때
        ListNode* p;
        p = head1; // 포인터 p가 첫번째 리스트의 첫번째 노드를 가리킴
        while (p -> link != NULL)
            p = p -> link; // 다음 노드로 이동

        // p -> link == NULL이면 (head의 끝)
        p -> link = head2;
        return head1;
    }
}

// main 함수
int main(void){
    ListNode* head1 = NULL; // 비어있는 리스트1 생성
    ListNode* head2 = NULL; // 비어있는 리스트2 생성

    printf("head1 리스트 생성 과정\n");
    head1 = insert_first(head1, 30);
    print_list(head1);
    head1 = insert_first(head1, 20);
    print_list(head1);
    head1 = insert_first(head1, 10);
    print_list(head1);

    printf("\nhead2 리스트 생성 과정\n");
    head2 = insert_first(head2, 60);
    print_list(head2);
    head2 = insert_first(head2, 50);
    print_list(head2);
    head2 = insert_first(head2, 40);
    print_list(head2);

    printf("\n합쳐진 리스트 head1\n");
    head1 = concat_list(head1, head2);
    print_list(head1);

    return 0;
}