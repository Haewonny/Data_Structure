#include <stdio.h>
#include <stdlib.h>
/*
   [ 배열 + 전역 변수로 구현 ]
   - 1차원 배열 stack[]
   - top : 스택에서 가장 최근에 입력되었던 자료를 가리키는 변수
   - 가장 먼저 들어온 요소는 stack[0]에, 가장 최근에 들어온 요소는 stack[top]에 저장
   - 스택이 공백 상태이면 top은 -1 ( ∵ [0]일 때는 데이터가 하나 있는 상태 )
 */
#define MAX_STACK_SIZE 100 // 스택의 최대 크기
typedef int element; // 데이터의 자료형
element stack[MAX_STACK_SIZE]; // 1차원 배열
int top = -1; // 구조체를 안 써서 top 변수 사용

// 공백 상태 검출 함수
int is_empty() {
    return (top == -1); // top == -1이면 true(1)
}

// 포화 상태 검출 함수
int is_full() {
    return (top == (MAX_STACK_SIZE - 1)); // top == MAX_STACK_SIZE - 1이면 true(1)
}

// 삽입 함수
void push(element item) {
    if (is_full()) {
        fprintf(stderr, "스택 포화 에러\n");
        return;
    }
    else
        stack[++top] = item;
}

// 삭제 함수
element pop() {
    if (is_empty()) {
        fprintf(stderr, "스택 공백 에러\n");
        exit(1);
    }
    else
        return stack[top--];
}

// peek 함수 - 요소를 스택에서 삭제하지 않고 보기(read)만 하는 연산
element peek() {
    if (is_empty()) {
        fprintf(stderr, "스택 공백 에러\n");
        exit(1);
    }
    else
        return stack[top]; // top의 이동 없음
}

int main(void) {
    push(1);
    push(2);
    push(3);

    printf("%d\n", pop());
    printf("%d\n", pop());
    printf("%d\n", pop());

    return 0;

}