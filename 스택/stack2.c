#include <stdio.h>
#include <stdlib.h>
/*
   [ 배열 + 전역 변수로 구현 + **스택의 요소가 구조체** ]
   - 1차원 배열 stack[]
   - top : 스택에서 가장 최근에 입력되었던 자료를 가리키는 변수
   - 가장 먼저 들어온 요소는 stack[0]에, 가장 최근에 들어온 요소는 stack[top]에 저장
   - 스택이 공백 상태이면 top은 -1 ( ∵ [0]일 때는 데이터가 하나 있는 상태 )
   - element의 타입이 구조체
 */
#define MAX_STACK_SIZE 100 // 스택의 최대 크기
#define MAX_STRING 100 // 문자열의 최대 크기
typedef struct { // 스택 요소 (학생 정보)
    int student_no; // 학생 번호
    char name[MAX_STRING]; // 학생 이름
    char address[MAX_STRING]; // 학생 주소
} element;

element stack[MAX_STACK_SIZE]; // 스택 : 1차원 배열
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
void push(element item) { // item은 구조체 변수
    if (is_full()) {
        fprintf(stderr, "스택 포화 에러\n");
        return;
    }
    else
        stack[++top] = item; // 구조체 변수 안에 있는 거(학생 번호, 학생 이름, 학생 주소) 한번에 다 대입
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
    element ie = { 2171040, "이해원", "서울" }; // push할 요소
    element oe; // pop할 요소

    push(ie);
    oe = pop();

    printf("학번 : %d\n", oe.student_no);
    printf("이름 : %s\n", oe.name);
    printf("이름 : %s\n", oe.address);

    return 0;

}