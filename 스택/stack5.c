#include <stdio.h>
#include <stdlib.h>
/*
   [ 스택을 함수의 매개변수로 전달 + 동적 배열 스택 ]
   - 스택을 하나의 구조체로 봄(StackType s)
   - 스택의 크기가 동적으로 할당됨
   - malloc(), realloc()을 호출하여 실행 시간에 메모리를 할당 받아 스택으로 사용함
 */
typedef int element;
typedef struct {
    element* data; // data는 포인터로 정의 -> 스택 배열을 가리킴
    int capacity; // 현재 스택의 크기
    int top;
} StackType; // 스택 구조체

// 스택 생성 함수
void init_stack(StackType* s){ // 포인터를 받아옴
    s -> top = -1; // top에는 아무것도 없는 상태
    s -> capacity = 1; // 크기 1
    s -> data = (element*) malloc(s -> capacity * sizeof(element));
}

// 스택 삭제 함수
void delete(StackType* s){
    free(s -> data); // 동적으로 받아온 배열의 공간 반환
}

// 공백 상태 검출 함수
int is_empty(StackType* s){
    return (s -> top == -1); // top이 -1이면 공백인 상태(true == 1)
}

// 포화 상태 검출 함수
int is_full(StackType* s){
    return (s -> top ==  s -> capacity - 1);
}

// 삽입 함수
void push(StackType* s, element item){
    if(is_full(s)){ // 스택이 포화 상태이면
        s -> capacity *= 2; // 크기를 2배로 확장
        s -> data = (element*) realloc(s -> data, s -> capacity * sizeof(element));
                                   //       포인터     ,      최종 길이
    }
    // 포화일 때 공간을 늘렸으니까 else문이 필요 없음
    s -> data[++(s -> top)] = item; // 스택 top 인덱스 하나 증가
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
    StackType s; // 스택 구조체 변수
    init_stack(&s);

    push(&s, 1);
    push(&s, 2);
    push(&s, 3);

    printf("%d\n", pop(&s));
    printf("%d\n", pop(&s));
    printf("%d\n", pop(&s));

    delete(&s); // 동적으로 받은 메모리 공간 반환

    return 0;
}