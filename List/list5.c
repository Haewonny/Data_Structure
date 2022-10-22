#include <stdio.h>
#include <stdlib.h>
/*
  [ 연결 리스트로 구현한 스택 ]
  - stack top의 위치를 저장하기 위한 구조체 필요
 */
typedef int element; // 리스트 항목의 정의 (정수 타입)
typedef struct StackNode { // 노드 타입
    element data;
    struct StackNode* link;
} StackNode;

typedef struct { // 헤더 타입
    StackNode* top;
} LinkedStackType;

// 초기화 함수
void init(LinkedStackType* s) {
    s -> top = NULL;
}

// 공백 상태 검출 함수
int is_empty(LinkedStackType* s) {
    return (s -> top == NULL);
}

// 삽입 함수
void push(LinkedStackType* s, element item) {
    StackNode* temp = (StackNode*) malloc(sizeof (StackNode)); // 노드 생성
    // **insert_first와 비슷
    temp -> data = item; // 값 넣기
    temp -> link = s -> top;
    s -> top = temp;
}

// 삭제 함수
element pop(LinkedStackType* s) {
    if(is_empty(s)) { // 비었다면 s -> top == NULL ==> 1(true)
        fprintf(stderr, "스택이 비어있음\n");
        exit(1);
    }
    else {
        StackNode* temp = s -> top;

        int data = temp -> data;
        s -> top = s -> top -> link;
        free(temp);

        return data;
    }
}

// 출력 함수
void print_stack(LinkedStackType* s) {
    for(StackNode* p = s -> top; p != NULL; p = p -> link)
        printf("%d -> ", p -> data); // p가 가리키는 data 출력
    printf("NULL \n");
}

// main 함수
int main(void){
    LinkedStackType s; // 스택 만들기
    init(&s); // 초기화

    push(&s, 1); print_stack(&s);
    push(&s, 2); print_stack(&s);
    push(&s, 3); print_stack(&s);

    pop(&s); print_stack(&s);
    pop(&s); print_stack(&s);
    pop(&s); print_stack(&s);

    return 0;
}