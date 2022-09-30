#include <stdio.h>
#include <stdlib.h>
/*
   [ 스택을 함수의 매개변수로 전달 + 동적 스택 ]
   - 스택을 하나의 구조체로 봄(StackType s)
   - 스택의 크기가 고정됨
   - StackType 구조체 변수 한 개를 동적으로 할당 받아서 스택 생성
   - stack3.c 에서의 s는 구조체 변수, stack4.c 에서의 s는 구조체 변수를 가리키는 포인터
 */
#define MAX_STACK_SIZE 100 // 스택의 최대 크기

typedef int element;
typedef struct {
    element data[MAX_STACK_SIZE];
    int top;
} StackType; // 스택 구조체

// 스택 초기화 함수
void init_stack(StackType* s){ // 포인터를 받아옴
    s -> top = -1; // top에는 아무것도 없는 상태
    // ** 포인터 -> 멤버
}

// 공백 상태 검출 함수
int is_empty(StackType* s){
    return (s -> top == -1); // top이 -1이면 공백인 상태(true == 1)
}

// 포화 상태 검출 함수
int is_full(StackType* s){
    return (s -> top == (MAX_STACK_SIZE - 1)); // top이 MAX_STACK_SIZE - 1이면 포화 상태(true == 1)
}

// 삽입 함수
void push(StackType* s, element item){
    if(is_full(s)){ // 스택이 포화 상태이면
        fprintf(stderr, "스택 포화 에러\n");
        return;
    }
    else
        s -> data[++(s -> top)] = item; // 스택 top 인덱스 하나 증가

    /*
      [ top이 가리키는 곳에 대입하고 싶은 경우 ]
       s -> data [s -> top]
       ---------  --------
          배열        위치
    */
}

// 삭제 함수
element pop(StackType* s){ // 반환값이 스택 요소(구조체)
    if(is_empty(s)){ // 스택이 공백 상태이면
        fprintf(stderr, "스택 공백 에러\n");
        exit(1);
    }
    else
        return s -> data[(s -> top)--];
}

// peek 함수
element peek(StackType* s){
    if(is_empty(s)){ // 스택이 공백 상태이면
        fprintf(stderr, "스택 공백 에러\n");
        exit(1);
    }
    else
        return s -> data[(s -> top)]; // top 위치 변화 없음
}

// main 함수
int main(void){
    StackType* s; // 구조체 변수를 가리키는 포인터

    s = (StackType*) malloc(sizeof(StackType)); // 구조체 변수 하나 크기만큼 스택 생성

    // **s는 포인터라 &s로 전달 안 해도 됨**
    init_stack(s); // 스택의 초기화

    push(s, 1);
    push(s, 2);
    push(s, 3);

    printf("%d\n", pop(s));
    printf("%d\n", pop(s));
    printf("%d\n", pop(s));

    free(s); // 스택 공간 반환

    return 0;
}